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

NeuronNetwork::NeuronNetwork(int nbin, int nbout, int nbtot, double learning){

    // Main information

    inputCount = nbin;
    outputCount = nbout;
    neuronCount = nbtot;
    learningRate = learning;

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

    // Learning

    gradient = new double[neuronCount];

    weightDifference = static_cast<double**>(malloc(neuronCount * sizeof(double*)));
    for(int i = 0; i < neuronCount; i++){
        weightDifference[i] = new double[inputCount + neuronCount];
    }

    functionsDerivative = new ActivationFunctionDerivative[neuronCount];

    // Reset before running

    reset();
}

/*NeuronNetwork::~NeuronNetwork(){
    delete(relation);
    delete(weight);
    delete(bias);
    delete(functions);

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
    delete(functionsDerivative);
}*/

void NeuronNetwork::reset(){
    resetOutput();
    resetBackPropagation();
}

void NeuronNetwork::resetOutput(){
    int n = inputCount + neuronCount;
    for(int i = 0; i < n; i++){
        output[i] = 0;
    }
}

void NeuronNetwork::resetBackPropagation(){
    int n = inputCount + neuronCount;
    for(int i = 0; i < neuronCount; i++){
        gradient[i] = 0;
        for(int j = 0; j < n; j++){
            weightDifference[i][j] = 0;
        }
    }
}

// We define here matrices and vectors which permit to do less calculation during the running

void NeuronNetwork::init(){

    initNextNode();
    initPreviousNode();
    initNextNeighbor();
    initPreviousNeighbor();
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
        cout << "1" << endl;
        cout << nextCount[i] << endl;
        int* v = new int(nextCount[i]);
        cout << "2" << endl;
        nextNode[i] = v;
        cout << "3" << endl;
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

        n = newNextNeighbor(neighbor);
    }

    nextNeighborTurnCount = result.size();
    nextNeighbor = static_cast<int**>(malloc(nextNeighborTurnCount * sizeof(int*)));
    nextNeighborCount = new int[nextNeighborTurnCount];

    for(int i = 0; i < neuronCount; i++){
        nextNeighbor[i] = result[i];
        nextNeighborCount[i] = resultCount[i];
    }
}

void NeuronNetwork::initPreviousNeighbor(){
    vector<int*> result;
    vector<int> resultCount;
    bool* neighbor = new bool[neuronCount];
    int n = outputCount;
    for(int i = 0; i < neuronCount; i++){
        neighbor[i] = false;
    }
    for(int i = neuronCount - outputCount; i < neuronCount; i++){
        neighbor[i] = true;
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

        n = newPreviousNeighbor(neighbor);
    }

    previousNeighborTurnCount = result.size();
    previousNeighbor = static_cast<int**>(malloc(previousNeighborTurnCount * sizeof(int*)));
    previousNeighborCount = new int[previousNeighborTurnCount];

    for(int i = 0; i < previousNeighborTurnCount; i++){
        previousNeighbor[i] = result[i];
        previousNeighborCount[i] = resultCount[i];
    }
}

int NeuronNetwork::newNextNeighbor(bool* voisin){
    bool* result = new bool[neuronCount];
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

int NeuronNetwork::newPreviousNeighbor(bool* voisin){
    bool* result = new bool[neuronCount];
    for(int i = 0; i < neuronCount; i++){
        result[i] = false;
    }
    int n = 0;
    for(int i = 0; i < neuronCount; i++){
        if(voisin[i]){
            for(int j = 0; j < previousCount[i]; j++){
                int k = previousNode[i][j] - inputCount;
                if(k >= 0 && !result[k]){
                    n++;
                    result[k] = true;
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

void NeuronNetwork::setActivationDerivate(vector<ActivationFunctionDerivative> functionsArg){
    for(int i = 0; i < neuronCount; i++){
        functionsDerivative[i] = functionsArg[i];
    }
}

void NeuronNetwork::setInput(double* inputArg){
    for(int i = 0; i < inputCount; i++){
        output[i] = inputArg[i];
    }
}

double* NeuronNetwork::getOutput(){
    double* result = new double[outputCount];
    int i = 0, j = neuronCount + inputCount - outputCount;
    while(i < outputCount){
        result[i] = output[j];
        i++;
        j++;
    }
    return result;
}

// Calculate from the input

void NeuronNetwork::calculate(){
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
            int a = previousNode[k][j];
            s += weight[k][a] * output[a];
        }
        comp[i] = s + bias[k];
    }
    for(int i = 0; i < neighborCount; i++){
        output[neighbor[i] + inputCount] = (functions[i])(comp[i]);
    }
}

// Make a learning

void NeuronNetwork::batchLearning(double** input, double** output, int nbreData, int nbreLearning){
    for(int k = 0; k < nbreLearning; k++){
        reset();
        for(int i = 0; i < nbreData; i++){
            learn(input[i], output[i]);
        }
        applyWeight();
    }
}

void NeuronNetwork::stochasticLearning(double** input, double** output, int nbreData, int nbreLearning){
    for(int k = 0; k < nbreLearning; k++){
        reset();
        for(int i = 0; i < nbreData; i++){
            learn(input[i], output[i]);
            applyWeight();
        }
    }
}

void NeuronNetwork::learn(double* input, double* outputTheorical){
    resetOutput();
    setInput(input);
    calculate();
    calculateOutputGradient(outputTheorical);
    for(int i = 1; i < previousNeighborTurnCount; i++){
        calculateGradient(previousNeighbor[i], previousNeighborCount[i]);
    }
    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < previousCount[i]; j++){
            int k = previousNode[i][j];
            weightDifference[i][k] += gradient[i] * output[k];
        }
    }
}

void NeuronNetwork::calculateOutputGradient(double* outputTheorical){
    int i = 0;
    int j = neuronCount + inputCount - outputCount;
    int k = neuronCount - outputCount;
    while(i < outputCount){
        double e = outputTheorical[i] - output[j];
        gradient[k] = e * (functionsDerivative[k])(output[j]);
        i++;
        j++;
        k++;
    }
}

void NeuronNetwork::calculateGradient(int* neighbor, int neighborCount){
    double* error = new double[neighborCount];
    for(int i = 0; i < neighborCount; i++){
        int k = neighbor[i];
        int n = nextCount[k];
        int b = k + inputCount;
        double s = 0;
        for(int j = 0; j < n; j++){
            int a = nextNode[k][j];
            s += weight[a][b] * gradient[a];
        }
        error[i] = s;
    }
    for(int i = 0; i < neighborCount; i++){
        gradient[neighbor[i]] = (functionsDerivative[i])(output[neighbor[i] + inputCount]) * error[i];
    }
}

void NeuronNetwork::applyWeight(){
    int n = neuronCount + inputCount;
    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < n; j++){
            weight[i][j] += learningRate * weightDifference[i][j];
        }
    }
    resetBackPropagation();
}