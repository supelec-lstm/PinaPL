//
//  neuronNetwork.cpp
//  PinaPL
//

#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <math.h>

#include "neuronNetwork.hpp"
#include "mathFunctions.hpp"

#define NLOG
#define FILE_NAME "neuronNetwork.cpp\t"
#include "../log.hpp"

using namespace std;

// Initialization

NeuronNetwork::NeuronNetwork(int nbin, int nbout, int nbtot, double learning){
    PRINT_BEGIN_FUNCTION("Instantiation d'un nouveau réseau")
    // Main information

    inputCount = nbin;
    outputCount = nbout;
    neuronCount = nbtot;  // correspond à "nbreTotalNeuron" dans l'instantiation dans mnist.cpp
    putCount = nbtot + nbin + 1;

    learningRate = learning;

    // Input/Output vector

    put = new double[putCount];
    input = put + 1;
    neurons = put + inputCount + 1;
    output = put + inputCount + neuronCount + 1 - outputCount;
    put[0] = 1;

    // Vector and matrice defining the network

    relation = new bool*[neuronCount];
    relationOutput = new bool*[neuronCount];
    for(int i = 0; i < neuronCount; i++){
        relation[i] = new bool[putCount];
        relationOutput[i] = relation[i] + inputCount + 1;
        relation[i][0] = true;
    }

    weight = new double*[neuronCount];
    weightOutput = new double*[neuronCount];
    for(int i = 0; i < neuronCount; i++){
        weight[i] = new double[putCount];
        weightOutput[i] = weight[i] + inputCount + 1;
        weight[i][0] = 0;
    }

    activationFunctions = new ActivationFunctionMain[neuronCount];

    // Learning

    gradient = new double[neuronCount];

    weightDifference = new double*[neuronCount];
    for(int i = 0; i < neuronCount; i++){
        weightDifference[i] = new double[putCount];
    }

    derivativeActivationFunctions = new ActivationFunctionDerivative[neuronCount];

    // Reset before running

    reset();
    PRINT_END_FUNCTION()
}

NeuronNetwork::~NeuronNetwork(){
    PRINT_BEGIN_FUNCTION("Déallocation du réseau")
    delete(relation);
    delete(relationOutput);
    delete(weight);
    delete(weightOutput);
    delete(activationFunctions);

    delete(nextNode);
    delete(nextCount);
    delete(nextNeighbor);
    delete(nextNeighborCount);

    delete(previousCount);
    delete(previousNode);
    delete(previousNeighbor);
    delete(previousNeighborCount);

    delete(gradient);
    delete(weightDifference);
    delete(derivativeActivationFunctions);
    PRINT_END_FUNCTION()
}

void NeuronNetwork::reset(){
    PRINT_BEGIN_FUNCTION("Reset des paramètres de calcul du réseau")
    resetOutput();
    resetBackPropagation();
    resetGradient();
    PRINT_END_FUNCTION()
}

void NeuronNetwork::resetOutput(){
    PRINT_BEGIN_FUNCTION("Reset des entrées/sorties du réseau")
    for(int i = 1; i < putCount; i++){
        put[i] = 0.0;
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::resetBackPropagation(){
    PRINT_BEGIN_FUNCTION("Reset des paramètres de backpropagation")
    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < putCount; j++){
            weightDifference[i][j] = 0.0;
        }
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::resetGradient(){
    PRINT_BEGIN_FUNCTION("Reset du gradient")
    for(int i = 0; i < neuronCount; i++){
        gradient[i] = 0.0;
    }
    PRINT_END_FUNCTION()
}

// We define here matrices and vectors which permit to do less calculation during the running

void NeuronNetwork::init(){
    PRINT_BEGIN_FUNCTION("Initialisation des tableaux de calcul")
    initNextNode();
    initPreviousNode();
    initNextNeighbor();
    initPreviousNeighbor();
    PRINT_END_FUNCTION()
}

void NeuronNetwork::initNextNode(){
    PRINT_BEGIN_FUNCTION("Initialisation du tableau des prochains noeuds")
    nextNode = new int*[neuronCount];
    nextCount = new int[neuronCount];

    for(int i = 0; i < neuronCount; i++){
        nextCount[i] = 0;
    }
    int k;
    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < neuronCount; j++){
            if(relationOutput[j][i]){
                nextCount[i]++;
            }
        };
        nextNode[i] = new int[nextCount[i]];
        k = 0;
        for(int j = 0; j < neuronCount; j++){
            if(relationOutput[j][i]){
                nextNode[i][k] = j;
                k++;
            }
        }
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::initPreviousNode(){
    PRINT_BEGIN_FUNCTION("Initialisation du tableau de précèdents noeuds")
    previousNode = new int*[neuronCount];
    previousCount = new int[neuronCount];

    for(int i = 0; i < neuronCount; i++){
        previousCount[i] = 0;
    }
    int k;
    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < putCount; j++){
            if(relation[i][j]){
                previousCount[i]++;
            }
        }
        previousNode[i] = new int[previousCount[i]];
        k = 0;
        for(int j = 0; j < putCount; j++){
            if(relation[i][j]){
                previousNode[i][k] = j;
                k++;
            }
        }
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::initNextNeighbor(){
    PRINT_BEGIN_FUNCTION("Initialisation du tableau de prochains voisins")
    int* result = new int[neuronCount];
    for(int i = 0; i < neuronCount; i++){
        result[i] = 0;
    }
    int n = neuronCount;
    nextNeighborTurnCount = 0;
    while(n != 0){
        n = 0;
        for(int i = 0; i < neuronCount; i++){
            if(result[i] == nextNeighborTurnCount){
                for(int k = 0; k < nextCount[i]; k++){
                    result[nextNode[i][k]] = nextNeighborTurnCount+1;
                }
                n += nextCount[i];
            }
        }
        nextNeighborTurnCount++;
    }

    nextNeighbor = new int*[nextNeighborTurnCount];
    nextNeighborCount = new int[nextNeighborTurnCount];
    for(int i = 0; i < nextNeighborTurnCount; i++){
        nextNeighborCount[i] = 0;
    }
    for(int i = 0; i < neuronCount; i++){
        nextNeighborCount[result[i]] ++;
    }
    int k;
    for(int i = 0; i < nextNeighborTurnCount; i++){
        nextNeighbor[i] = new int[nextNeighborCount[i]];
        k = 0;
        for(int j = 0; j < neuronCount; j++){
            if(result[j] == i){
                nextNeighbor[i][k] = j;
                k++;
            }
        }
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::initPreviousNeighbor(){
    PRINT_BEGIN_FUNCTION("Initialisation du tableau de précèdents voisins")
    int* result = new int[neuronCount];
    for(int i = 0; i < neuronCount; i++){
        result[i] = -1;
    }
    for(int i = 0; i < outputCount; i++){
        result[neuronCount - outputCount + i] = 0;
    }
    int n = neuronCount;
    previousNeighborTurnCount = 0;
    while(n != 0){
        n = 0;
        for(int i = 0; i < neuronCount; i++){
            if(result[i] == previousNeighborTurnCount){
                for(int k = 0; k < previousCount[i]; k++){
                    if(previousNode[i][k] >= inputCount+1){
                        result[previousNode[i][k] - inputCount-1] = previousNeighborTurnCount+1;
                        n++;
                    }
                }
            }
        }
        previousNeighborTurnCount++;
    }

    previousNeighbor = new int*[previousNeighborTurnCount];
    previousNeighborCount = new int[previousNeighborTurnCount];
    for(int i = 0; i < previousNeighborTurnCount; i++){
        previousNeighborCount[i] = 0;
    }
    for(int i = 0; i < neuronCount; i++){
        previousNeighborCount[result[i]] ++;
    }
    int k;
    for(int i = 0; i < previousNeighborTurnCount; i++){
        previousNeighbor[i] = new int[previousNeighborCount[i]];
        k = 0;
        for(int j = 0; j < neuronCount; j++){
            if(result[j] == i){
                previousNeighbor[i][k] = j;
                k++;
            }
        }
    }
    PRINT_END_FUNCTION()
}

// Getters and setters

void NeuronNetwork::setRelation(vector<vector<bool> > relationArg){
    PRINT_BEGIN_FUNCTION("Paramétrage des relations")
    for(int i = 0; i < neuronCount; i++){
        for(int j = 1; j < putCount; j++){
            relation[i][j] = relationArg[i][j-1];
        }
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::setWeight(vector<vector<double> > weightArg){
    PRINT_BEGIN_FUNCTION("Paramétrage des poids à partir d'un tableau de poids")
    for(int i = 0; i < neuronCount; i++){
        for(int j = 1; j < putCount; j++){
            weight[i][j] = weightArg[i][j-1];
        }
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::setFunctions(vector<activationFunctionType> functions){
    PRINT_BEGIN_FUNCTION("Paramétrage des fonctions à partir d'un tableau de fonctions")
    for(int i = 0; i < neuronCount; i++){
        switch(functions[i]){
            case SIGMOID:
                activationFunctions[i] = sigmoid;
                derivativeActivationFunctions[i] = sigmoidDerivate;
                break;

            case ARCTAN:
                activationFunctions[i] = arctan;
                derivativeActivationFunctions[i] = arctanDerivate;
                break;

            case TANH:
                activationFunctions[i] = tanh;
                derivativeActivationFunctions[i] = tanhDerivate;
                break;

            case RELU:
                activationFunctions[i] = relu;
                derivativeActivationFunctions[i] = reluDerivate;
                break;
        }
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::setInput(double* inputArg){
    PRINT_BEGIN_FUNCTION("Paramétrage de l'entrée")
    for(int i = 0; i < inputCount; i++){
        input[i] = inputArg[i];
    }
    PRINT_END_FUNCTION()
}

double* NeuronNetwork::getOutput(){
    PRINT_BEGIN_FUNCTION("Obtention de la sortie")
    PRINT_END_FUNCTION()
    return output;
}

// Calculate from the input

void NeuronNetwork::calculate(){
    PRINT_BEGIN_FUNCTION("Calcul de la sortie, à partir de l'entrée")
    for(int i = 0; i < nextNeighborTurnCount; i++){
        calculateOutput(nextNeighbor[i], nextNeighborCount[i]);
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::calculateOutput(int* neighbor, int neighborCount){
    PRINT_BEGIN_FUNCTION("Une étape du calcul des sorties")
    for(int i = 0; i < neighborCount; i++){
        int k = neighbor[i];
        int n = previousCount[k];
        double s = 0;
        for(int j = 0; j < n; j++){
            int a = previousNode[k][j];
            s += weight[k][a] * put[a];
        }
        neurons[k] = (activationFunctions[k])(s);
    }
    PRINT_END_FUNCTION()
}

// Make a learning

void NeuronNetwork::learn(double* inputData, double* outputData){
    PRINT_BEGIN_FUNCTION("Apprentissage")
    resetOutput();
    resetGradient();
    setInput(inputData);
    calculate();
    calculateOutputGradient(outputData);
    for(int i = 1; i < previousNeighborTurnCount; i++){
        calculateGradient(previousNeighbor[i], previousNeighborCount[i]);
    }
    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < previousCount[i]; j++){
            int k = previousNode[i][j];
            weightDifference[i][k] += gradient[i] * put[k];
        }
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::calculateOutputGradient(double* outputData){
    PRINT_BEGIN_FUNCTION("Calcul du gradient de sortie")
    int n = neuronCount - outputCount;
    for(int i = 0; i < outputCount; i++){
        double e = outputData[i] - output[i];
        gradient[n + i] = e * (derivativeActivationFunctions[n + i])(output[i]);
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::calculateGradient(int* neighbor, int neighborCount){
    PRINT_BEGIN_FUNCTION("Calcul du gradient")
    for(int i = 0; i < neighborCount; i++){
        int k = neighbor[i];
        int n = nextCount[k];
        double s = 0;
        for(int j = 0; j < n; j++){
            int a = nextNode[k][j];
            s += weightOutput[a][k] * gradient[a];
        }
        gradient[k] = (derivativeActivationFunctions[k])(neurons[k]) * s;
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::applyWeight(){
    PRINT_BEGIN_FUNCTION("Paramétrage des poids à partir de la différence des poids et du learning rate")

    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < putCount; j++){
            weight[i][j] += learningRate * weightDifference[i][j];
        }
    }
    resetBackPropagation();
    PRINT_END_FUNCTION()
}

void NeuronNetwork::batchLearning(double** inputData, int inputSize, double** outputData, int batchSize, int nbreLearning){
    PRINT_BEGIN_FUNCTION("Apprentissage par batch")

    int maximumLearnings = (int)floor(inputSize / batchSize);

    for(int k = 0; k < maximumLearnings; k++){
        reset();
        for(int i = 0; i < nbreLearning; i++){
            for(int j = 0; j < batchSize; j++){
                learn(inputData[j+k*batchSize], outputData[j+k*batchSize]);
            }
            applyWeight();
        }
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::stochasticLearning(double** inputData, int inputSize, double** outputData, int nbreLearning){
    PRINT_BEGIN_FUNCTION("Apprentissage stochastique")
    PRINT_LOG(nextNeighborTurnCount);
    for(int k = 0; k < nbreLearning; k++){
        reset();
        for(int i = 0; i < inputSize; i++){
            learn(inputData[i], outputData[i]);
            applyWeight();
        }
    }
    PRINT_END_FUNCTION()
}
