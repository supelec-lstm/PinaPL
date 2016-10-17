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
    inputCount = nbin;
    outputCount = nbout;
    neuronCount = nbtot;

    output = new double[nbin + nbtot];

    reset();
}

void NeuronNetwork::reset(){
    for(int i = 0; i < inputCount + neuronCount; i++){
        output[i] = 0;
    }
}

void NeuronNetwork::setRelation(bool** relationArg){
    relation = relationArg;
}

void NeuronNetwork::setWeight(double** weightArg){
    weight = weightArg;
}

void NeuronNetwork::setBiais(double* biaisArg){
    biais = biaisArg;
}

void NeuronNetwork::setActivation(ActivationFunctionMain* functionsArg){
    functions = functionsArg;
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

void NeuronNetwork::calculate(){
    bool* voisin = new bool[neuronCount];
    for(int i = 0; i < neuronCount; i++){
        voisin[i] = firstNode[i];
    }

    do{
        calculateOutput(voisin);
    }while(newNode(voisin));
}

void NeuronNetwork::calculateOutput(bool* voisin){
    double* comp = new double[neuronCount];
    for(int i = 0; i < neuronCount; i++){
        if(voisin[i]){
            int n = previousCount[i];
            double s = 0;
            for(int j = 0; j < n; j++){
                s += weight[i][previousNode[i][j]];
            }
            comp[i] = s;
        }
    }
    for(int i = 0; i < neuronCount; i++){
        if(voisin[i]){
            output[i] = (functions[i])(comp[i]);
        }
    }
}

bool NeuronNetwork::newNode(bool* voisin){
    bool* result = new bool[neuronCount];
    bool isEmpty = true;
    for(int i = 0; i < neuronCount; i++){
        result[i] = false;
    }
    for(int i = 0; i < neuronCount; i++){
        if(voisin[i]){
            int n = nextCount[i];
            isEmpty = isEmpty && (n == 0);
            for(int j = 0; j < n; j++){
                result[nextNode[i][j]] = true;
            }
        }
    }
    for(int i = 0; i < neuronCount; i++){
        voisin[i] = result[i];
    }
    return isEmpty;
}