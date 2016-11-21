//
//  neuronNetwork.cpp
//  PinaPL
//

#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>

#include "neuronNetwork.hpp"

#define NLOG

#ifdef LOG
#define PRINT_LOG(title) cout << "neuronNetwork.cpp     " << title << endl;
#else
#define PRINT_LOG(title)
#endif

using namespace std;

// Initialization

NeuronNetwork::NeuronNetwork(int nbin, int nbout, int nbtot, double learning){
    PRINT_LOG("Instantiation d'un nouveau réseau")
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

    bias = new double[neuronCount];
    functions = new ActivationFunctionMain[neuronCount];

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

    biasDifference = new double[neuronCount];

    functionsDerivative = new ActivationFunctionDerivative[neuronCount];

    // Reset before running

    reset();
}

NeuronNetwork::~NeuronNetwork(){
    delete(weight);
    delete(bias);
    delete(functions);

    delete(gradient);
    delete(weightDifference);
    delete(functionsDerivative);
}

void NeuronNetwork::reset(){
    PRINT_LOG("Reset des paramètres de calcul du réseau")
    PRINT_LOG("vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv")
    resetOutput();
    resetBackPropagation();
    resetGradient();
    PRINT_LOG("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^")
}

void NeuronNetwork::resetInput(){
    PRINT_LOG("Reset des entrée")
    for(int i = 0; i < inputCount; i++){
        put[i] = 0;
    }
}

void NeuronNetwork::resetOutput(){
    PRINT_LOG("Reset des sorties")
    for(int i = 0; i < putCount; i++){
        put[i] = 0;
    }
}

void NeuronNetwork::resetBackPropagation(){
    PRINT_LOG("Reset des paramètres de backpropagation")
    for(int i = 0; i < neuronCount; i++){
        biasDifference[i] = 0;
        for(int j = 0; j < putCount; j++){
            weightDifference[i][j] = 0;
        }
    }
}

void NeuronNetwork::resetGradient(){
    PRINT_LOG("Reset du gradient")
    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < putCount; j++){
            for(int k = 0; k < neuronCount; k++){
                gradient[i][j][k] = 0;
            }
        }
    }
}

// We define here matrices and vectors which permit to do less calculation during the running

void NeuronNetwork::init(){
    PRINT_LOG("Initialisation des tableaux de calcul")
    PRINT_LOG("vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv")
    PRINT_LOG("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^")
}

// Getters and setters

void NeuronNetwork::setWeight(vector<vector<double> > weightArg){
    PRINT_LOG("Paramétrage des poids à partir d'un tableau de poids")
    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < putCount; j++){
            weight[i][j] = weightArg[i][j];
        }
    }
}

void NeuronNetwork::setBias(vector<double> biasArg){
    PRINT_LOG("Paramétrage des biais")
    for(int i = 0; i < neuronCount; i++){
        bias[i] = biasArg[i];
    }
}

void NeuronNetwork::setActivation(vector<ActivationFunctionMain> functionsArg){
    PRINT_LOG("Paramétrage des fonctions d'activation")
    for(int i = 0; i < neuronCount; i++){
        functions[i] = functionsArg[i];
    }
}

void NeuronNetwork::setActivationDerivate(vector<ActivationFunctionDerivative> functionsArg){
    PRINT_LOG("Paramétrage des dérivées des fonctions d'activation")
    for(int i = 0; i < neuronCount; i++){
        functionsDerivative[i] = functionsArg[i];
    }
}

void NeuronNetwork::setInput(int& inputArg){
    PRINT_LOG("Paramétrage de l'entrée")
    resetInput();
    put[inputArg] = 1;
}

double* NeuronNetwork::getOutput(){
    return output;
}

// Calculate from the input

void NeuronNetwork::calculate(){
    PRINT_LOG("Calcul de la sortie, à partir de l'entrée")
    PRINT_LOG("vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv")
    double* comp = new double[neuronCount];
    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < putCount; j++){
            comp[i] += weight[i][j] * put[j];
        }
        comp[i] += bias[i];
    }
    for(int i = 0; i < neuronCount; i++){
        neurons[i] = (functions[i])(comp[i]);
    }
    PRINT_LOG("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^")
}

void NeuronNetwork::calculateGradient(int& outputData){
    PRINT_LOG("Calcul du gradient")

    //Calcul des dérivées
    double* derivative = new double[neuronCount];
    for(int i = 0; i < neuronCount; i++){
        derivative[i] = (functionsDerivative[i])(neurons[i]);
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

    //Calcul des différences de biais
    for(int i = 0; i < neuronCount; i++){
        double* inter = new double[neuronCount];
        for(int k = 0; k < neuronCount; k++){
            for(int l = 0; l < neuronCount; l++){
                inter[k] += weight[k][l] * biasGradient[i][l];
            }
            if(k == i){
                inter[k] += 1;
            }
        }
        for(int k = 0; k < neuronCount; k++){
            biasGradient[i][k] = derivative[k] * inter[k];
        }
        for(int k = 0; k < outputCount; k++){
            biasDifference[i] += error[k] * biasGradient[i][n+k];
        }
    }
}

void NeuronNetwork::applyWeight(){
    PRINT_LOG("Paramétrage des poids & du biais à partir de la différence des poids et du learning rate")
    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < putCount; j++){
            weight[i][j] += learningRate * weightDifference[i][j];
        }
        bias[i] += learningRate * biasDifference[i];
    }
    resetBackPropagation();
}

// Make a learning

void NeuronNetwork::learn(int& inputData, int& outputData){
    PRINT_LOG("Apprentissage")
    PRINT_LOG("vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv")
    setInput(inputData);
    calculate();
    calculateGradient(outputData);
}

void NeuronNetwork::batchLearning(int* inputData, int n){
    PRINT_LOG("Apprentissage par batch")
    PRINT_LOG("vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv")
    reset();
    for(int i = 0; i < n-1; i++){
        learn(inputData[i], inputData[i+1]);
    }
    applyWeight();
    PRINT_LOG("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^")
}

void NeuronNetwork::stochasticLearning(int* inputData, int n){
    PRINT_LOG("Apprentissage stochastique")
    PRINT_LOG("vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv")
    reset();
    for(int i = 0; i < n-1; i++){
        learn(inputData[i], inputData[i+1]);
        applyWeight();
    }
    PRINT_LOG("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^")
}

void NeuronNetwork::completeBatchLearning(int** inputData, int* inputDataCount, int n){
    reset();
    for(int i = 0; i < n; i++){
        batchLearning(inputData[i], inputDataCount[i]);
    }
}

void NeuronNetwork::completeStochasticLearning(int** inputData, int* inputDataCount, int n){
    reset();
    for(int i = 0; i < n; i++){
        batchLearning(inputData[i], inputDataCount[i]);
    }
}
