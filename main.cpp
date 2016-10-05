//
//  main.cpp
//  PinaPL
//

#include <iostream>
#include <map>
#include <vector>
#include <typeinfo>
#include <random>
#include <string.h>

#include "simpleNeuron/neuron.hpp"
#include "neuronNetwork/neuronNetwork.hpp"
#include "neuronNetwork/neuronNetworkBuilder.hpp"
#include "console/console.hpp"
#include "idxParser/idxParser.hpp"


using namespace std;

/*
void test2();
void test3();
*/

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
        cout << "Non-interactive start" << endl;
        IdxParser parser;
        parser.importMNISTImages("./idxParser/train-images-idx3-ubyte.gz");
        parser.importMNISTLabels("./idxParser/train-labels-idx1-ubyte.gz");
    }
    return 0;
}

/*
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
    
    vector<double> inputs = {0, 1};
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
    
    vector<double> inputs = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    NeuronNetwork network = builder.generateComputeNetwork(true, -0.1, 0.1);
    network.setInput(inputs);
    network.calculate();
    
    cout << network.description();
}
*/
