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

NeuronNetwork::NeuronNetwork(int nbin, int nbout, int nbtot, int nbfold, double learning){
    PRINT_BEGIN_FUNCTION("New network instantiation")
    // Main information

    inputCount = nbin;
    outputCount = nbout;
    neuronCount = nbtot;
    putCount = nbtot + nbin + 1;
    foldCount = nbfold;

    learningRate = learning;

    // Input/Output vector

    put = new double*[foldCount];
    input = new double*[foldCount];
    neurons = new double*[foldCount];
    output = new double*[foldCount];
    for(int i = 0; i < foldCount; i++){
        put[i] = new double[putCount];
        input[i] = put[i] + 1;
        neurons[i] = put[i] + inputCount + 1;
        output[i] = put[i] + inputCount + neuronCount + 1 - outputCount;
        put[i][0] = 1;
    }

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

    gradient = new double*[foldCount];
    for(int i = 0; i < foldCount; i++){
        gradient[i] = new double[neuronCount];
    }

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
    PRINT_BEGIN_FUNCTION("Network unallocation")
    delete(relation);
    delete(relationOutput);
    delete(weight);
    delete(weightOutput);
    delete(activationFunctions);

    delete(nextNode);
    delete(nextCount);

    delete(previousCount);
    delete(previousNode);

    delete(gradient);
    delete(weightDifference);
    delete(derivativeActivationFunctions);
    PRINT_END_FUNCTION()
}

void NeuronNetwork::reset(){
    PRINT_BEGIN_FUNCTION("Network calculus parameters reset")
    resetOutput();
    resetBackPropagation();
    resetGradient();
    PRINT_END_FUNCTION()
}

void NeuronNetwork::resetInput(){
    PRINT_BEGIN_FUNCTION("Network input")
    for(int j = 0; j < foldCount; j++){
        for(int i = 0; i < inputCount; i++){
            input[j][i] = 0.0;
        }
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::resetInput(int j){
    PRINT_BEGIN_FUNCTION("Network input")
    for(int i = 0; i < inputCount; i++){
        input[j][i] = 0.0;
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::resetOutput(){
    PRINT_BEGIN_FUNCTION("Network input & output reset")
    for(int j = 0; j < foldCount; j++){
        for(int i = 1; i < putCount; i++){
            put[j][i] = 0.0;
        }
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::resetBackPropagation(){
    PRINT_BEGIN_FUNCTION("Backpropagation parameters reset")
    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < putCount; j++){
            weightDifference[i][j] = 0.0;
        }
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::resetGradient(){
    PRINT_BEGIN_FUNCTION("Gradient reset")
    for(int j = 0; j < foldCount; j++){
        for(int i = 0; i < neuronCount; i++){
            gradient[j][i] = 0.0;
        }
    }
    PRINT_END_FUNCTION()
}

// We define here matrices and vectors which permit to do less calculation during the running

void NeuronNetwork::init(){
    PRINT_BEGIN_FUNCTION("Calculus arrays initialization")
    initNextNode();
    initPreviousNode();
    PRINT_END_FUNCTION()
}

void NeuronNetwork::initNextNode(){
    PRINT_BEGIN_FUNCTION("Next nodes array initialization")
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
    PRINT_BEGIN_FUNCTION("Previous nodes array initialization")
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


// Getters and setters

void NeuronNetwork::setRelation(vector<vector<bool> > relationArg){
    PRINT_BEGIN_FUNCTION("Setting relations")
    for(int i = 0; i < neuronCount; i++){
        for(int j = 1; j < putCount; j++){
            relation[i][j] = relationArg[i][j-1];
        }
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::setWeight(vector<vector<double> > weightArg){
    PRINT_BEGIN_FUNCTION("Setting weights from an array")
    for(int i = 0; i < neuronCount; i++){
        for(int j = 1; j < putCount; j++){
            weight[i][j] = weightArg[i][j-1];
        }
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::setFunctions(vector<activationFunctionType> functions){
    PRINT_BEGIN_FUNCTION("Setting functions from an array")
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

void NeuronNetwork::setInput(int inputArg, int j){
    PRINT_BEGIN_FUNCTION("Setting input")
    resetInput(j);
    for(int i = 0; i < inputCount; i++){
        input[j][inputArg] = 1;
    }
    PRINT_END_FUNCTION()
}

double** NeuronNetwork::getOutput(){
    PRINT_BEGIN_FUNCTION("Obtaining output")
    PRINT_END_FUNCTION()
    return output;
}

double* NeuronNetwork::getOutputFold(int j) {
	PRINT_BEGIN_FUNCTION("Obtaining output")
	PRINT_END_FUNCTION()
	return output[j];
}

// Calculate from the input

void NeuronNetwork::calculate(int fold){
    PRINT_BEGIN_FUNCTION("Output computing")
    if(fold != 0){
        for(int i = 0; i < neuronCount; i++){
            for(int j = 0; j < previousCount[i]; j++){
                int a = previousNode[i][j];
                if(a <= inputCount){
                    put[fold][i] += weight[i][a]*put[fold][a];
                }
                else{
                    put[fold][i] += weight[i][a]*put[fold-1][a];
                }
            }
        }
    }
    else{
        for(int i = 0; i < neuronCount; i++){
			int n = previousCount[i];
            for(int j = 0; j < n; j++){
                int a = previousNode[i][j];
                if(a <= inputCount){
                    put[fold][i] += weight[i][a]*put[fold][a];
                }
            }
        }
    }
    PRINT_END_FUNCTION()
}

// Make a learning

void NeuronNetwork::calculateOutputGradient(int outputData, int fold){
    PRINT_BEGIN_FUNCTION("Output gradient computation")
    int n = neuronCount - outputCount;
    for(int i = 0; i < outputCount; i++){
        gradient[fold][n + i] = -output[fold][i];
    }
    gradient[fold][n + outputData] += 1;
    PRINT_END_FUNCTION()
}

void NeuronNetwork::calculateGradient(int fold){
    PRINT_BEGIN_FUNCTION("Gradient computation")
    if(fold < foldCount - 1){
        for(int i = 0; i < neuronCount; i++){
            int n = nextCount[i];
            double s = 0;
            for(int j = 0; j < n; j++){
                int a = nextNode[i][j];
                s += weightOutput[a][i] * gradient[fold+1][a];
            }
            gradient[fold][i] = (derivativeActivationFunctions[i])(neurons[fold][i]) * (gradient[fold][i] + s);
        }
    }
    else{
        for(int i = 0; i < neuronCount; i++){
            gradient[fold][i] = (derivativeActivationFunctions[i])(neurons[fold][i]) * gradient[fold][i];
        }
    }
	if (fold != 0) {
		for (int i = 0; i < neuronCount; i++) {
			int n = previousCount[i];
			for (int j = 0; j < n; j++) {
				int a = previousNode[i][j];
				if (a <= inputCount) {
					weightDifference[i][a] += gradient[fold][i] * put[fold][a];
				}
				else {
					weightDifference[i][a] += gradient[fold][i] * put[fold-1][a];
				}
			}
		}
	}
	else {
		for (int i = 0; i < neuronCount; i++) {
			int n = previousCount[i];
			for (int j = 0; j < n; j++) {
				int a = previousNode[i][j];
				if (a <= inputCount) {
					weightDifference[i][a] += gradient[fold][i] * put[fold][a];
				}
			}
		}
	}
    PRINT_END_FUNCTION()
}

void NeuronNetwork::applyWeight(){
    PRINT_BEGIN_FUNCTION("Setting weights from weight differences and learning rate")

    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < putCount; j++){
            weight[i][j] += learningRate * weightDifference[i][j];
        }
    }
    resetBackPropagation();
    PRINT_END_FUNCTION()
}

void NeuronNetwork::learn(int* inputData, int inputSize){
    PRINT_BEGIN_FUNCTION("Learning of a word")
    int j = 0;
    int k = 0;
    for(int i = 0; i < inputSize-1; i++){
        setInput(inputData[i], j);
        calculate(j);
        if(j == foldCount-1){
            while(j > 0){
                calculateOutputGradient(inputData[i - foldCount + j + 1], i - foldCount + j);
                calculateGradient(i - foldCount + j);
                j--;
            }
        }
        else{
            j++;
        }
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::batchLearning(int** inputData, int* inputSize, int nbreInput, int batchSize, int nbreLearning){
    PRINT_BEGIN_FUNCTION("Batch learning")

    int maximumLearnings = (int)floor(nbreInput / batchSize);

    for(int k = 0; k < maximumLearnings; k++){
        for(int i = 0; i < nbreLearning; i++){
            for(int j = 0; j < batchSize; j++){
                learn(inputData[j+k*batchSize], inputSize[j+k*batchSize]);
            }
            applyWeight();
        }
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::stochasticLearning(int** inputData, int* inputSize, int nbreInput, int nbreLearning){
    PRINT_BEGIN_FUNCTION("Stochastic learning")
    PRINT_LOG(nextNeighborTurnCount);
    for(int k = 0; k < nbreLearning; k++){
        for(int i = 0; i < nbreLearning; i++){
            learn(inputData[i], inputSize[i]);
            applyWeight();
        }
    }
    PRINT_END_FUNCTION()
}
