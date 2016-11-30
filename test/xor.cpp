#include <iostream>
#include <map>
#include <vector>
#include <random>
#include <string.h>
#include <math.h>

#include "xor.hpp"
#include "../perceptron/neuronNetwork.hpp"
#include "../perceptron/mathFunctions.hpp"

#define NLOG

#ifdef LOG
#define PRINT_LOG(title) cout << "=== " << title << " ===" << endl;
#else
#define PRINT_LOG(title)
#endif

using namespace std;

Xor::Xor(){

    // Données à modifier

    nbreLearn = 10000;
    learningRate = 0.3;
    function = SIGMOID;

     // Données à ne pas modifier

    nbreLayout = 2;
    nbreNeuron = new int[nbreLayout];
    nbreNeuron[0] = 2;
    nbreNeuron[1] = 1;

    nbreTotalNeuron = 0;
    for(int i = 0; i < nbreLayout; i++){
        nbreTotalNeuron += nbreNeuron[i];
    }

    PRINT_LOG("Création des entrées")
    inputData = inputConverter();

    PRINT_LOG("Création des sorties")
    outputData = outputConverter();

    PRINT_LOG("Création du réseau")
    network = new NeuronNetwork(2, 1, nbreTotalNeuron, learningRate);

    PRINT_LOG("Matrice de relation")
    setRelation();

    PRINT_LOG("Création des poids")
    setWeight();

    PRINT_LOG("Création des fonctions")
    setFunctions();

    PRINT_LOG("Initialisation du réseau")
    network->init();
}

void Xor::learn(){
    PRINT_LOG("Apprentissage")
    //network->batchLearning(inputData, outputData, 4, nbreLearn);
}

void Xor::test(){
    PRINT_LOG("Test")

    for(int i = 0; i < 4; i++){
        network->reset();
        network->setInput(inputData[i]);
        network->calculate();
        double a = network->getOutput()[0];
        cout << outputData[i][0] << " - " << a << endl;
    }
}

double** Xor::inputConverter(){
    double** input = new double*[4];
    for(int i = 0; i < 4; i++){
        input[i] = new double[2];
    }
    input[0][0] = 0; input[0][1] = 0;
    input[1][0] = 0; input[1][1] = 1;
    input[2][0] = 1; input[2][1] = 0;
    input[3][0] = 1; input[3][1] = 1;
    return input;
}

double** Xor::outputConverter(){
    double** output = new double*[4];
    for(int i = 0; i < 4; i++){
        output[i] = new double[2];
    }
    output[0][0] = 0;
    output[1][0] = 1;
    output[2][0] = 1;
    output[3][0] = 0;
    return output;
}

void Xor::setRelation(){
    vector<vector<bool> > relation(nbreTotalNeuron);
    for(int i = 0; i < nbreTotalNeuron; i++){
        vector<bool> v(2 + nbreTotalNeuron, false);
        relation[i] = v;
    }
    for(int i = 0; i < nbreNeuron[0]; i++){
        for(int j = 0; j < 2; j++){
            relation[i][j] = true;
        }
    }
    int n1 = 2;
    int n2 = nbreNeuron[0];
    for(int k = 1; k < nbreLayout; k++){
        for(int i = 0; i < nbreNeuron[k]; i++){
            for(int j = 0; j < nbreNeuron[k-1]; j++){
                relation[n2+i][n1+j] = true;
            }
        }
        n1 += nbreNeuron[k-1];
        n2 += nbreNeuron[k];
    }
    network->setRelation(relation);
}

void Xor::setWeight(){
    vector<vector<double> > weight(nbreTotalNeuron);
    for(int i = 0; i < nbreTotalNeuron; i++){
        vector<double> v(2 + nbreTotalNeuron, 0);
        weight[i] = v;
    }
    for(int i = 0; i < nbreTotalNeuron; i++){
        for(int j = 0; j < 2 + nbreTotalNeuron; j++){
            weight[i][j] = randomizer(-1,1);
        }
    }
    network->setWeight(weight);
}

void Xor::setFunctions(){
    vector<ActivationFunctionMain> functions(nbreTotalNeuron);
    vector<ActivationFunctionDerivative> functionsDerivate(nbreTotalNeuron);
}
