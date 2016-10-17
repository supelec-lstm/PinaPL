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

<<<<<<< HEAD
void testXOR();
void testMNIST(vector<vector<double> > imagesLearn, vector<double> labelsLearn, int numberData, vector<vector<double> > imagesTest, vector<double> labelsTest, int numberTest);

int main(int argc, const char * argv[]) {
    srand(unsigned(short(time(NULL))));

    vector<string> stringedArgv = vector<string>(unsigned(argc));

    for (int i = 0; i < argc; i++) {
        unsigned long length = strlen(argv[i]);
        string argument;
        argument.assign(argv[i], length);
        stringedArgv[unsigned(i)] = argument;
    }

    if (isArgumentPresent("--log", &stringedArgv)) {
    }

    if (isArgumentPresent("--interactive", &stringedArgv)) {
        // if there is a single argument and it is "--interactive"
        Console console;
        console.greeting();
        console.interactive();
        console.goodbye();
    } else {
        // else
        cout << "Non-interactive start" << endl;
        IdxParser parser;
        string imagesLearnPath = "./idxs/train-images-idx3-ubyte.gz";
        string labelsLearnPath = "./idxs/train-labels-idx1-ubyte.gz";
        string imagesTestPath = "./idxs/t10k-images-idx3-ubyte.gz";
        string labelsTestPath = "./idxs/t10k-labels-idx1-ubyte.gz";
        vector<vector<double> > imgLearn = parser.importMNISTImages(imagesLearnPath);
        vector<double> labelLearn = parser.importMNISTLabels(labelsLearnPath);
        vector<vector<double> > imgTest = parser.importMNISTImages(imagesTestPath);
        vector<double> labelTest = parser.importMNISTLabels(labelsTestPath);
        testMNIST(imgLearn, labelLearn, 20, imgTest, labelTest, 100);
    }

    return 0;
}

void testXOR() {

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

    builder.buildNeurons(true, -1.5, 1.5);

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

    dataInput[0][0] = 0; dataInput[0][1] = 0; dataOutput[0][0] = 0;
    dataInput[1][0] = 0; dataInput[1][1] = 1; dataOutput[1][0] = 1;
    dataInput[2][0] = 1; dataInput[2][1] = 0; dataOutput[2][0] = 1;
    dataInput[3][0] = 1; dataInput[3][1] = 1; dataOutput[3][0] = 0; 

    for(int i = 0; i < 1000; i++){
        network.onlineLearn(dataInput, dataOutput, nData);
    }

    cout << network.description() << endl;

    for(unsigned long i = 0; i < 4; i++){
        network.setInput(dataInput[i]);
        network.calculate();
        cout << network.getOutput()[0] << endl;
    }    
}

void testMNIST(vector<vector<double> > imagesLearn, vector<double> labelsLearn, int numberData, vector<vector<double> > imagesTest, vector<double> labelsTest, int numberTest){

    cout << "---------  Création du réseau  ---------" << endl;

    NeuronNetworkBuilder builder = NeuronNetworkBuilder();
    builder.setName("Test");
    builder.setDate("2016-09-28");
    builder.setDefaultCompositionFunction(compositionFunctionSum);
    builder.setDefaultActivationFunction(activationFunctionSigmoid);

    builder.addNeurons(784, compositionFunctionSum, activationFunctionLinear);
    builder.addNeurons(20);

    builder.setPropertiesForNeuronRange(NeuronProportyInput, 0, 783);
    builder.setPropertiesForNeuronRange(NeuronProportyOutput, 794, 803);

    builder.addManyConnectionsToManyRange(0, 783, 784, 793);
    builder.addManyConnectionsToManyRange(784, 793, 794, 803);

    builder.buildNeurons(true, 0, 1);

    NeuronNetwork network = builder.generateComputationalNetwork();

    cout << "---------  Génération des données  ---------" << endl;

    vector<vector<double> > dataInput(numberData);
    vector<vector<double> > dataOutput(numberData);
    vector<vector<double> > testInput(numberTest);
    vector<double> testOutput = labelsTest;

    for(int i = 0; i < numberData; i++){
        vector<double> v1(784);
        vector<double> v2(10, 0);
        dataInput[i] = v1;
        dataOutput[i] = v2;
        for(int j = 0; j < 784; j++){
            dataInput[i][j] = imagesLearn[i][j] / 255;
        }
        dataOutput[i][(int)labelsLearn[i]] = 1;
    }

    for(int i = 0; i < numberTest; i++){
        vector<double> v(784);
        testInput[i] = v;
        for(int j = 0; j < 784; j++){
            testInput[i][j] = imagesTest[i][j] / 255;
        }
    }

    vector<vector<double> > s(0);
    vector<double> s2(0);
    imagesLearn = s;
    labelsLearn = s2;
    imagesTest = s;
    labelsTest = s2;

    cout << "---------  Apprentissage  ---------" << endl;

    for(unsigned long i = 0; i < 200; i++){
        cout << i << endl;
        network.batchLearn(dataInput, dataOutput, numberData);
    }

    cout << "---------  Test  ---------" << endl;

    int result = 0;

    for(int i = 0; i < numberTest; i++){
        network.setInput(testInput[i]);
        network.calculate();
        int a = maximum(network.getOutput());
        cout << a << " - " << testOutput[i] << endl;
        if(a == (int)testOutput[i]){
            result ++;
        }
    }

    cout << (double)result/numberTest * 100 << endl;
}

int maximum(vector<double> v){
    int result = 0;
    int n = v.size();
    for(int i = 1; i < n; i++){
        if(v[result] < v[i]){
            result = i;
        }
    }
    return result;
}