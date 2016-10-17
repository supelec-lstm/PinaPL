//
//  neuronNetwork.cpp
//  PinaPL
//

#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>

#include "neuronNetwork.hpp"


using namespace std;

// Initialization

NeuronNetwork::NeuronNetwork(int nbin, int nbout, int nbtot){

    // Main information

    inputCount = nbin;
    outputCount = nbout;
    neuronCount = nbtot;

    // Input/Output vector

    output = new double[inputCount + neuronCount];

    // Vector and matrice defining the network

    relation = static_cast<bool**>(malloc(neuronCount * sizeof(bool*)));
    for(int i = 0; i < neuronCount; i++){
        relation[i] = new bool[inputCount + neuronCount];
    }

    weight = static_cast<double**>(malloc(neuronCount * sizeof(double*)));
    for(int i = 0; i < neuronCount; i++){
        weight[i] = new double[inputCount + neuronCount];
    }

    bias = new double[neuronCount];
    functions = new ActivationFunctionMain[neuronCount];

    // Reset before running

    reset();
}

void NeuronNetwork::reset(){
    for(int i = 0; i < inputCount + neuronCount; i++){
        output[i] = 0;
    }
}

// We define here matrices and vectors which permit to do less calculation during the running

void NeuronNetwork::init(){

    initNextNode();
    initPreviousNode();
    initNextNeighbor();
}

void NeuronNetwork::initNextNode(){
    nextNode = static_cast<int**>(malloc(neuronCount * sizeof(int*)));
    nextCount = new int[neuronCount];

    for(int i = 0; i < neuronCount; i++){
        nextCount[i] = 0;
    }
    int k;
    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < neuronCount; j++){
            if(relation[j][i + inputCount]){
                nextCount[i]++;  
            }
        }
        nextNode[i] = new int(nextCount[i]);
        k = 0;
        for(int j = 0; j < neuronCount; j++){
            if(relation[j][i + inputCount]){
                nextNode[i][k] = j;
                k++;
            }
        }
    }
}

void NeuronNetwork::initPreviousNode(){
    previousNode = static_cast<int**>(malloc(neuronCount * sizeof(int*)));
    previousCount = new int[neuronCount];

    int n = inputCount + neuronCount;

    for(int i = 0; i < neuronCount; i++){
        previousCount[i] = 0;
    }
    int k;
    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < n; j++){
            if(relation[i][j]){
                previousCount[i]++;  
            }
        }
        previousNode[i] = new int(previousCount[i]);
        k = 0;
        for(int j = 0; j < n; j++){
            if(relation[i][j]){
                previousNode[i][k] = j;
                k++;
            }
        }
    }
}

void NeuronNetwork::initNextNeighbor(){
    vector<int*> result;
    vector<int> resultCount;
    bool* neighbor = new bool[neuronCount];
    int n = 0;
    for(int i = 0; i < neuronCount; i++){
        neighbor[i] = false;
    }
    for(int i = 0; i < neuronCount; i++){
        int j = 0;
        while(!relation[i][j] && j < inputCount){
            j++;
        }
        if(j != inputCount){
            n++;
            neighbor[i] = true;
        }
    }

    while(n != 0){
        int* v = new int[n];
        int k = 0;
        for(int i = 0; i < neuronCount; i++){
            if(neighbor[i]){
                v[k] = i;
                k++;
            }
        }
        result.push_back(v);
        resultCount.push_back(n);

        n = newNode(neighbor);
    }

    nextNeighborTurnCount = result.size();
    nextNeighbor = static_cast<int**>(malloc(nextNeighborTurnCount * sizeof(int*)));
    nextNeighborCount = new int[nextNeighborTurnCount];

    for(int i = 0; i < neuronCount; i++){
        nextNeighbor[i] = result[i];
        nextNeighborCount[i] = resultCount[i];
    }
}


int NeuronNetwork::newNode(bool* voisin){
    bool* result = new bool[neuronCount];
    bool isEmpty = true;
    for(int i = 0; i < neuronCount; i++){
        result[i] = false;
    }
    int n = 0;
    for(int i = 0; i < neuronCount; i++){
        if(voisin[i]){
            for(int j = 0; j < nextCount[i]; j++){
                if(!result[nextNode[i][j]]){
                    n++;
                    result[nextNode[i][j]] = true;
                }
                
            }
        }
    }
    for(int i = 0; i < neuronCount; i++){
        voisin[i] = result[i];
    }
    return n;
}

// Getters and setters

void NeuronNetwork::setRelation(vector<vector<bool> > relationArg){
    int n = neuronCount + inputCount;
    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < n; j++){
            relation[i][j] = relationArg[i][j];
        }
    }
}

void NeuronNetwork::setWeight(vector<vector<double> > weightArg){
    int n = neuronCount + inputCount;
    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < n; j++){
            weight[i][j] = weightArg[i][j];
        }
    }
}

void NeuronNetwork::setBias(vector<double> biasArg){
    for(int i = 0; i < neuronCount; i++){
        bias[i] = biasArg[i];
    }
}

void NeuronNetwork::setActivation(vector<ActivationFunctionMain> functionsArg){
    for(int i = 0; i < neuronCount; i++){
        functions[i] = functionsArg[i];
    }
}

void NeuronNetwork::setInput(double* inputArg){
    for(int i = 0; i < inputCount; i++){
        output[i] = inputArg[i];
    }
}

double* NeuronNetwork::getOutput(){
    double* result = new double[outputCount];
    int i = 0, j = neuronCount - outputCount;
    while(i < outputCount){
        result[i] = output[j];
        i++;
        j++;
    }
    return result;
}

// Calculate from the input

void NeuronNetwork::calculate(){
    reset();
    for(int i = 0; i < nextNeighborTurnCount; i++){
        calculateOutput(nextNeighbor[i], nextNeighborCount[i]);
    }
}

void NeuronNetwork::calculateOutput(int* neighbor, int neighborCount){
    double* comp = new double[neighborCount];
    for(int i = 0; i < neighborCount; i++){
        int k = neighbor[i];
        int n = previousCount[k];
        double s = 0;
        for(int j = 0; j < n; j++){
            s += weight[k][previousNode[k][j]] * output[j];
        }
        comp[i] = s + bias[k];
    }
    for(int i = 0; i < neighborCount; i++){
        output[neighbor[i]] = (functions[i])(comp[i]);
    }
}