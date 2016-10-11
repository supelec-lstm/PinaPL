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
#include <time.h>

#include "simpleNeuron/mathFunctions.hpp"
#include "simpleNeuron/neuron.hpp"
#include "neuronNetwork/neuronNetwork.hpp"
#include "neuronNetwork/neuronNetworkBuilder.hpp"
#include "console/console.hpp"
#include "idxParser/idxParser.hpp"


using namespace std;

void test();
void test2();
void test3();


int main(int argc, const char * argv[]) {
    srand(time(NULL));
    vector<string> stringedArgv = vector<string>(argc);

    for (int i = 0; i < argc; i++) {
        unsigned long length = strlen(argv[i]);
        string argument;
        argument.assign(argv[i], length);
        stringedArgv[i] = argument;
    }

    if (argc == 2 && stringedArgv[1] == "--interactive") {
        // if there is a single argument and it is "--interactive"
        Console console;
        console.greeting();
        console.interactive();
        console.goodbye();
    } else {
        // else
        /*cout << "Non-interactive start" << endl;
        IdxParser parser;
        string imagesPath = "./idxParser/train-images-idx3-ubyte.gz";
        string labelsPath = "./idxParser/train-labels-idx1-ubyte.gz";
        parser.importMNISTImages(imagesPath);
        parser.importMNISTLabels(labelsPath);*/
        test();
    }

    return 0;
}

void test() {

    NeuronNetworkBuilder builder = NeuronNetworkBuilder();
    builder.setName("Test");
    builder.setDate("2016-09-28");
    builder.setDefaultCompositionFunction(compositionFunctionSum);
    builder.setDefaultActivationFunction(activationFunctionSigmoid);

    builder.addNeurons(2, compositionFunctionSum, activationFunctionLinear);
    builder.addNeurons(3);

    builder.setPropertiesForNeuronRange(NeuronProportyInput, 0, 1);
    builder.setPropertiesForNeuronRange(NeuronProportyOutput, 4, 4);

    builder.addOneConnectionToManyRange(0, 1, 2);
    builder.addOneConnectionToManyRange(0, 1, 3);
    builder.addOneConnectionToManyRange(2, 3, 4);;

    builder.buildNeurons(true, -5, 5);

    NeuronNetwork network = builder.generateComputationalNetwork();

    unsigned long sizeData = 4;
    unsigned long nData = 4;
    vector<vector<double> > dataInput(sizeData);
    vector<vector<double> > dataOutput(sizeData);
    for(unsigned long i = 0; i < sizeData; i++) {
        vector<double> input(2);
        vector<double> output(1);
        dataInput[i] = input;
        dataOutput[i] = output;
    }

    dataInput[0][0] = 0; dataInput[0][1] = 1; dataOutput[0][0] = 1;
    dataInput[1][0] = 0; dataInput[1][1] = 0; dataOutput[1][0] = 0;
    dataInput[2][0] = 1; dataInput[2][1] = 1; dataOutput[2][0] = 0;
    dataInput[3][0] = 1; dataInput[3][1] = 0; dataOutput[3][0] = 1; 

    for(int i = 0; i < 1000; i++){
        network.batchLearn(dataInput, dataOutput, nData);
    }

    cout << network.description() << endl;

    for(unsigned long i = 0; i < 4; i++){
        network.setInput(dataInput[i]);
        network.calculate();
        cout << network.getOutput()[0] << endl;
    }    
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
    builder.buildNeurons(false);
    NeuronNetwork network = builder.generateComputationalNetwork();
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
    builder.buildNeurons(true, -0.1, 0.1);
    NeuronNetwork network = builder.generateComputationalNetwork();
    network.setInput(inputs);
    network.calculate();
    
    cout << network.description();
}*/