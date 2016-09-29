//
//  main.cpp
//  PinaPL
//


#define RAND_MAX 2

#include <iostream>
#include <map>
#include <typeinfo>
#include <random>

#include "simpleNeuron/neuron.hpp"
#include "simpleNeuron/neuronNetwork.hpp"
#include "console/console.hpp"


using namespace std;

void test();

int main(int argc, const char * argv[]) {

    test();
    return 0;
}

void test(){
    // test

    // neurones

    Neuron *neurons[5];
    neurons[0] = new Neuron(1, Neuron::compositionSum, Neuron::activationLinear); //entry
    neurons[1] = new Neuron(1, Neuron::compositionSum, Neuron::activationLinear); //entry
    neurons[2] = new Neuron(2, Neuron::compositionSum, Neuron::activationSigmoid);
    neurons[3] = new Neuron(1, Neuron::compositionSum, Neuron::activationSigmoid);
    neurons[4] = new Neuron(1, Neuron::compositionSum, Neuron::activationSigmoid);

    for(int i = 0; i < 5; i++){
        neurons[i]->setBalancedWeight();
    }

    // input - output

    unsigned long input[2];
    input[0] = 0;
    input[1] = 1;

    unsigned long output[2];
    output[0] = 3;
    output[1] = 4;

    // relations

    bool** relation = (bool**)malloc(5*sizeof(bool*)); //#magic trick for 2-dimensional array
    for(unsigned long i = 0; i < 5; i++){
        relation[i] = new bool[5];
    }
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            relation[i][j] = false;
        }
    }
    relation[0][2] = true;
    relation[1][2] = true;
    relation[2][3] = true;
    relation[2][4] = true;

    // data

    double x[2];
    x[0] = 0;
    x[1] = 1;

    // definition du network

    NeuronNetwork *network = new NeuronNetwork("test", "date", 2, 2, 5);
    network->setNeurons(neurons);
    network->setInputNeurons(input);
    network->setOutputNeurons(output);
    network->setRelation(relation);
    network->reset();

    // utilisation

    network->setInput(x);
    network->calculate();
    double* y = network->getOutput();
    cout << y[0] << endl << y[1] << endl;

}
