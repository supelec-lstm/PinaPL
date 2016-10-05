//
//  main.cpp
//  PinaPL
//

#include <iostream>
#include <map>
#include <typeinfo>
#include <random>
#include <string.h>

#include "simpleNeuron/neuron.hpp"
#include "neuronNetwork/neuronNetwork.hpp"
#include "neuronNetwork/neuronNetworkBuilder.hpp"
#include "console/console.hpp"


using namespace std;

void test();
void test2();
void test3();


int main(int argc, const char * argv[]) {

    vector<string> stringedArgv;

    for (int i = 0; i < argc; i++) {
        int length = strlen(argv[i]);
        string argument;
        argument.assign(argv[i], length);
        stringedArgv.push_back(argument);
    }

    if (argc == 2 && stringedArgv[1] == "--interactive") {
        Console console;
        console.greeting();
        console.interactive();
        console.goodbye();
    } else {
        test();
        test2();
        test3();
    }
    return 0;
}

void test() {
    // test

    // neurones

    Neuron *neurons[5];
    neurons[0] = new Neuron(1, compositionFunctionSum, activationFunctionLinear); //entry
    neurons[1] = new Neuron(1, compositionFunctionSum, activationFunctionLinear); //entry
    neurons[2] = new Neuron(2, compositionFunctionSum, activationFunctionSigmoid);
    neurons[3] = new Neuron(1, compositionFunctionSum, activationFunctionSigmoid);
    neurons[4] = new Neuron(1, compositionFunctionSum, activationFunctionSigmoid);
    
    for (unsigned long i = 0; i < 5; i++) {
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
    bool **relation = static_cast<bool**>(malloc(5 * sizeof(bool*)));
    for (unsigned long i = 0; i < 5; i++) {
        relation[i] = new bool[5];
    }
    for (unsigned long i = 0; i < 5; i++) {
        for (unsigned long j = 0; j < 5; j++) {
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

    NeuronNetwork *network = new NeuronNetwork("Test", "2016-09-28", 2, 2, 5);
    network->setNeurons(neurons);
    network->setInputNeurons(input);
    network->setOutputNeurons(output);
    network->setRelation(relation);
    network->reset();

    // utilisation

    network->setInput(x);
    network->calculate();
//    double* y = network->getOutput();
//    cout << y[0] << endl << y[1] << endl;
    
    cout << network->description() << endl << endl;
}

void test2() {
    NeuronNetworkBuilder builder = NeuronNetworkBuilder();
    builder.setName("Test");
    builder.setDate("2016-09-28");
    builder.setDefaultCompositionFunction(compositionFunctionSum);
    builder.setDefaultActivationFunction(activationFunctionSigmoid);
    
    builder.addNeurons(2, compositionFunctionSum, activationFunctionSigmoid);
    builder.addNeurons(3);
    
    builder.setPropertiesForNeuronRange(NeuronProportyInput, 0, 1);
    builder.setPropertiesForNeuronRange(NeuronProportyOutput, 3, 4);
    
    builder.addOneConnectionToManyRange(0, 1, 2);
    builder.addManyConnectionsToOneRange(2, 3, 4);
    
    double inputs[] = {0, 1};
    NeuronNetwork network = builder.generateComputeNetwork(false);
    network.setInput(inputs);
    network.calculate();

    cout << network.description();
}

void test3() {
    NeuronNetworkBuilder builder = NeuronNetworkBuilder();
    builder.setDefaultCompositionFunction(compositionFunctionSum);
    builder.setDefaultActivationFunction(activationFunctionSigmoid);
    builder.addNeurons(40);
    builder.setPropertiesForNeuronRange(NeuronProportyInput, 0, 9);
    builder.setPropertiesForNeuronRange(NeuronProportyOutput, 30, 39);
    builder.addManyConnectionsToManyRange(0, 9, 10, 19);
    builder.addManyConnectionsToManyRange(10, 19, 20, 29);
    builder.addManyConnectionsToManyRange(20, 29, 30, 39);
    
    double inputs[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    NeuronNetwork network = builder.generateComputeNetwork(true, -0.1, 0.1);
    network.setInput(inputs);
    network.calculate();
    
    cout << network.description();
}
