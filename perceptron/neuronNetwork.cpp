//
//  neuronNetwork.cpp
//  PinaPL
//

#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>

#include "neuronNetwork.hpp"

#define LOG

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
    learningRate = learning;

    // Input/Output vector

    output = new double[inputCount + neuronCount];

    // Vector and matrice defining the network

    relation = new bool*[neuronCount];
    for(int i = 0; i < neuronCount; i++){
        relation[i] = new bool[inputCount + neuronCount];
    }

    weight = new double*[neuronCount];
    for(int i = 0; i < neuronCount; i++){
        weight[i] = new double[inputCount + neuronCount];
    }

    bias = new double[neuronCount];
    functions = new ActivationFunctionMain[neuronCount];

    // Learning

    gradient = new double[neuronCount];

    weightDifference = new double*[neuronCount];
    for(int i = 0; i < neuronCount; i++){
        weightDifference[i] = new double[inputCount + neuronCount];
    }

    biasDifference = new double[neuronCount];

    functionsDerivative = new ActivationFunctionDerivative[neuronCount];

    // Reset before running

    reset();
}

NeuronNetwork::~NeuronNetwork(){
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
}

void NeuronNetwork::reset(){
    PRINT_LOG("Reset des paramètres de calcul du réseau")
    PRINT_LOG("vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv")
    resetOutput();
    resetBackPropagation();
    resetGradient();
    PRINT_LOG("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^")
}

void NeuronNetwork::resetOutput(){
    PRINT_LOG("Reset des sorties")
    int n = inputCount + neuronCount;
    for(int i = 0; i < n; i++){
        output[i] = 0;
    }
}

void NeuronNetwork::resetBackPropagation(){
    PRINT_LOG("Reset des paramètres de backpropagation")
    int n = inputCount + neuronCount;
    for(int i = 0; i < neuronCount; i++){
        biasDifference[i] = 0;
        for(int j = 0; j < n; j++){
            weightDifference[i][j] = 0;
        }
    }
}

void NeuronNetwork::resetGradient(){
    PRINT_LOG("Reset du gradient")
    for(int i = 0; i < neuronCount; i++){
        gradient[i] = 0;
    }
}

// We define here matrices and vectors which permit to do less calculation during the running

void NeuronNetwork::init(){
    PRINT_LOG("Initialisation des tableaux de calcul")
    PRINT_LOG("vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv")
    initNextNode();
    initPreviousNode();
    initNextNeighbor();
    initPreviousNeighbor();
    PRINT_LOG("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^")
}

void NeuronNetwork::initNextNode(){
    PRINT_LOG("Initialisation du tableau des prochains noeuds")
    nextNode = new int*[neuronCount];
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
        };
        nextNode[i] = new int[nextCount[i]];
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
    PRINT_LOG("Initialisation du tableau de précèdents noeuds")
    previousNode = new int*[neuronCount];
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
        previousNode[i] = new int[previousCount[i]];
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
    PRINT_LOG("Initialisation du tableau de prochains voisins")
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
    nextNeighbor = new int*[nextNeighborTurnCount];
    nextNeighborCount = new int[nextNeighborTurnCount];

    for(int i = 0; i < nextNeighborTurnCount; i++){
        nextNeighbor[i] = result[i];
        nextNeighborCount[i] = resultCount[i];
    }
}

void NeuronNetwork::initPreviousNeighbor(){
    PRINT_LOG("Initialisation du tableau de précèdents voisins")
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
    previousNeighbor = new int*[previousNeighborTurnCount];
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
    PRINT_LOG("Paramétrage des relations")
    int n = neuronCount + inputCount;
    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < n; j++){
            relation[i][j] = relationArg[i][j];
        }
    }
}

void NeuronNetwork::setWeight(vector<vector<double> > weightArg){
    PRINT_LOG("Paramétrage des poids à partir d'un tableau de poids")
    int n = neuronCount + inputCount;
    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < n; j++){
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

void NeuronNetwork::setInput(double* inputArg){
    PRINT_LOG("Paramétrage de l'entrée")
    for(int i = 0; i < inputCount; i++){
        output[i] = inputArg[i];
    }
}

double* NeuronNetwork::getOutput(){
    //PRINT_LOG("Obtention de la sortie")
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
    PRINT_LOG("Calcul de la sortie, à partir de l'entrée")
    PRINT_LOG("vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv")
    for(int i = 0; i < nextNeighborTurnCount; i++){
        calculateOutput(nextNeighbor[i], nextNeighborCount[i]);
    }
    PRINT_LOG("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^")
}

void NeuronNetwork::calculateOutput(int* neighbor, int neighborCount){
    PRINT_LOG("Une étape du calcul des sorties")
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
        output[neighbor[i] + inputCount] = (functions[neighbor[i]])(comp[i]);
    }
}

// Make a learning

void NeuronNetwork::batchLearning(double** input, double** output, int nbreData, int nbreLearning){
    PRINT_LOG("Apprentissage par batch")
    PRINT_LOG("vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv")
    for(int k = 0; k < nbreLearning; k++){
        reset();
        for(int i = 0; i < nbreData; i++){
            learn(input[i], output[i]);
        }
        applyWeight();
    }
    PRINT_LOG("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^")
}

void NeuronNetwork::stochasticLearning(double** input, double** output, int nbreData, int nbreLearning){
    PRINT_LOG("Apprentissage stochastique")
    PRINT_LOG("vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv")
    for(int k = 0; k < nbreLearning; k++){
        reset();
        for(int i = 0; i < nbreData; i++){
            learn(input[i], output[i]);
            applyWeight();
        }
    }
    PRINT_LOG("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^")
}

void NeuronNetwork::learn(double* input, double* outputTheorical){
    PRINT_LOG("Apprentissage")
    PRINT_LOG("vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv")
    resetOutput();
    resetGradient();
    setInput(input);
    calculate();
    calculateOutputGradient(outputTheorical);
    for(int i = 1; i < previousNeighborTurnCount; i++){
        calculateGradient(previousNeighbor[i], previousNeighborCount[i]);
    }
    PRINT_LOG("Gradients")
    PRINT_LOG("vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv")
    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < previousCount[i]; j++){
            int k = previousNode[i][j];
            weightDifference[i][k] += gradient[i] * output[k];
            #ifdef LOG
            std::cout << gradient[i] << " ";
            #endif
            biasDifference[i] += gradient[i];
        }
        #ifdef LOG
        std::cout << endl;
        #endif
    }
    #ifdef LOG
    PRINT_LOG("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^")
    PRINT_LOG("Tableau de variation des poids")
    PRINT_LOG("vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv")
    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < neuronCount; j++){
            std::cout << weightDifference[i][j] << " ";
        }
        std::cout << endl;
    }
    PRINT_LOG("Outputs")
    PRINT_LOG("vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv")
    for(int i = 0; i < neuronCount + inputCount; i++){
        std::cout << output[i] << " ";
    }
    std::cout << endl;
    PRINT_LOG("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^")
    PRINT_LOG("Tableau de variation des biais")
    PRINT_LOG("vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv")
    for(int i = 0; i < neuronCount; i++){
        std::cout << biasDifference[i] << " ";
    }
    std::cout << endl;
    #endif
    PRINT_LOG("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^")
    PRINT_LOG("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^")
}

void NeuronNetwork::calculateOutputGradient(double* outputTheorical){
    PRINT_LOG("Calcul du gradient de sortie")
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
    PRINT_LOG("Calcul du gradient")
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
    PRINT_LOG("Paramétrage des poids & du biais à partir de la différence des poids et du learning rate")
    int n = neuronCount + inputCount;
    for(int i = 0; i < neuronCount; i++){
        for(int j = 0; j < n; j++){
            weight[i][j] += learningRate * weightDifference[i][j];
        }
        bias[i] += learningRate * biasDifference[i];
    }
    resetBackPropagation();
}
