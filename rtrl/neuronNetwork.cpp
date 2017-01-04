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
    neuronCount = nbtot;
    putCount = nbin + nbtot;
    learningRate = learning;

    // Input/Output vector

    put = new double[inputCount + neuronCount];
    neurons = put + inputCount;
    output = neurons + neuronCount - outputCount;

    // Vector and matrice defining the network

    weight = new double*[neuronCount];
    weightOutput = new double*[neuronCount];
    for(int i = 0; i < neuronCount; i++){
        weight[i] = new double[putCount];
        weightOutput[i] = weight[i] + inputCount;
    }

    activationFunctions = new ActivationFunctionMain[neuronCount];

    // Learning

    gradient = new double**[neuronCount];
    weightDifference = new double*[neuronCount];
    for(int i = 0; i < neuronCount; i++){
        weightDifference[i] = new double[putCount];
        gradient[i] = new double*[putCount];
        for(int j = 0; j < putCount; j++){
            gradient[i][j] = new double[neuronCount];
        }
    }

    derivativeActivationFunctions = new ActivationFunctionDerivative[neuronCount];

    // Reset before running

    reset();
    PRINT_END_FUNCTION()
}

NeuronNetwork::~NeuronNetwork(){
    delete(weight);
    delete(activationFunctions);

    delete(gradient);
    delete(weightDifference);
    delete(derivativeActivationFunctions);
}

void NeuronNetwork::reset(){
    PRINT_BEGIN_FUNCTION("Reset des paramètres de calcul du réseau")
    resetOutput();
    resetBackPropagation();
    resetGradient();
    PRINT_END_FUNCTION()
}

void NeuronNetwork::resetInput(){
    PRINT_BEGIN_FUNCTION("Reset des entrée")
    for(int i = 0; i < inputCount; i++){
        put[i] = 0;
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::resetOutput(){
    PRINT_BEGIN_FUNCTION("Reset des sorties")
    for(int i = 0; i < putCount; i++){
        put[i] = 0;
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::resetBackPropagation(){
    PRINT_BEGIN_FUNCTION("Reset des paramètres de backpropagation")
    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < putCount; j++){
            weightDifference[i][j] = 0;
        }
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::resetGradient(){
    PRINT_BEGIN_FUNCTION("Reset du gradient")
    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < putCount; j++){
            for(int k = 0; k < neuronCount; k++){
                gradient[i][j][k] = 0;
            }
        }
    }
    PRINT_END_FUNCTION()
}

// Getters and setters

void NeuronNetwork::setWeight(vector<vector<double> > weightArg){
    PRINT_BEGIN_FUNCTION("Paramétrage des poids à partir d'un tableau de poids")
    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < putCount; j++){
            weight[i][j] = weightArg[i][j];
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

void NeuronNetwork::setInput(int& inputArg){
    PRINT_BEGIN_FUNCTION("Paramétrage de l'entrée")
    resetInput();
    put[inputArg] = 1;
    PRINT_END_FUNCTION()
}

double* NeuronNetwork::getOutput(){
    return output;
}

// Calculate from the input

void NeuronNetwork::calculate(){
    PRINT_BEGIN_FUNCTION("Calcul de la sortie, à partir de l'entrée")
    double* comp = new double[neuronCount];
    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < putCount; j++){
            comp[i] += weight[i][j] * put[j];
        }
    }
    for(int i = 0; i < neuronCount; i++){
        neurons[i] = (activationFunctions[i])(comp[i]);
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::calculateGradient(int& outputData){
    PRINT_BEGIN_FUNCTION("Calcul du gradient")

    //Calcul des dérivées
    double* derivative = new double[neuronCount];
    for(int i = 0; i < neuronCount; i++){
        derivative[i] = (derivativeActivationFunctions[i])(neurons[i]);
    }

    //Calcul des erreurs
    double* error = new double[outputCount];
    for(int i = 0; i < outputCount; i++){
        error[i] = (i == outputData ? 1 : 0) - output[i];
    }

    int n = neuronCount - outputCount;

    // Calcul des différences de poids
    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < putCount; j++){
            double* inter = new double[neuronCount];
            for(int k = 0; k < neuronCount; k++){
                for(int l = 0; l < neuronCount; l++){
                    inter[k] += weight[k][l] * gradient[i][j][l];
                }
                if(k == i){
                    inter[k] += put[j];
                }
            }
            for(int k = 0; k < neuronCount; k++){
                gradient[i][j][k] = derivative[k] * inter[k];
            }
            for(int k = 0; k < outputCount; k++){
                weightDifference[i][j] += error[k] * gradient[i][j][n+k];
            }
        }
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

// Make a learning

void NeuronNetwork::learn(int& inputData, int& outputData){
    PRINT_BEGIN_FUNCTION("Apprentissage")
    setInput(inputData);
    calculate();
    calculateGradient(outputData);
    PRINT_END_FUNCTION()
}

void NeuronNetwork::batchLearning(int* inputData, int n){
    PRINT_BEGIN_FUNCTION("Apprentissage des mots par batch")
    for(int i = 0; i < n-1; i++){
        learn(inputData[i], inputData[i+1]);
    }
    applyWeight();
    PRINT_END_FUNCTION()
}

void NeuronNetwork::stochasticLearning(int* inputData, int n){
    PRINT_BEGIN_FUNCTION("Apprentissage des mots en stochastique")
    for(int i = 0; i < n-1; i++){
        learn(inputData[i], inputData[i+1]);
        applyWeight();
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::completeBatchLearning(int** inputData, int* inputDataCount, int n){
    PRINT_BEGIN_FUNCTION("Apprentissage par batch")
    reset();
    for(int i = 0; i < n; i++){
        batchLearning(inputData[i], inputDataCount[i]);
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::completeStochasticLearning(int** inputData, int* inputDataCount, int n){
    PRINT_BEGIN_FUNCTION("Apprentissage stochastique")
    reset();
    for(int i = 0; i < n; i++){
        batchLearning(inputData[i], inputDataCount[i]);
    }
    PRINT_END_FUNCTION()
}
