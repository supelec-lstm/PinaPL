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
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <algorithm>

#include "grammar/grammar.hpp"

#include "rtrl/neuronNetwork.hpp"
#include "rtrl/mathFunctions.hpp"

#include "test/rtrl.hpp"

#define LOG
#define FILE_NAME "main.cpp\t\t"
#include "log.hpp"
#include "test/bptt.hpp"

#include <Eigen/Dense>
using namespace Eigen;

int tab_log = 0;

using namespace std;

int main(int argc, char **argv) {
    /*srand(time(NULL));

    int opt;
    int nbreData  = 60000;
    int nbreLearn = 1;
    int nbreTest  = 10000;
    double learningRate = 0.3;
    int nbreLayout = 1;
    int nbreNeuronPerLayout = 20;

    while ((opt = getopt (argc, argv, "d:l:t:r:L:N:h")) != -1) {
        switch (opt) {
        case 'd':
            nbreData = atoi(optarg);
            break;
        case 'l':
            nbreLearn = atoi(optarg);
            break;
        case 't':
            nbreTest = atoi(optarg);
            break;
        case 'L':
            nbreLayout = atoi(optarg);
            break;
        case 'N':
            nbreNeuronPerLayout = atoi(optarg);
            break;
        case 'r':
            learningRate = stod(optarg);
            break;
        case 'h':
            cout << "Arguments:" << endl;
            cout << "-d : number of data to import from learning set (integer)(default: 60000)" << endl;
            cout << "-l : number of learns per input (integer)(default: 1)" << endl;
            cout << "-t : number of data to import from test set (integer)(default: 10000)" << endl;
            cout << "-r : learning rate (double)(default: 0.3)" << endl;
            cout << "-L : number of network hidden layouts, does not include output layer (integer)(default: 1)" << endl;
            cout << "-N : number of neurons per hidden layout (integer)(default: 20)" << endl;
            return 0;
            break;
        }
    }

    /*int nbreNeuron[nbreLayout+1];
    if (isArgumentPresent("--interactive", &stringedArgv)) {
        // if there is a single argument and it is "--interactive"
        Console console;
        console.greeting();
        console.interactive();
        console.goodbye();
    } else {
    /*
    NeuronNetwork network(7, 7, 14, 0.3);

    vector<vector<double>> weight(14);
    for(int i = 0; i < 14; i++){
        vector<double> w(21, 0.1);
        weight[i] = w;
    }
    network.setWeight(weight);

    vector<ActivationFunctionMain> functions(14, &sigmoid);
    network.setActivation(functions);

    vector<ActivationFunctionDerivative> functionsDerivate(14, &sigmoidDerivate);
    network.setActivationDerivate(functionsDerivate);
    int nbreNeuron[nbreLayout+1];
    std::fill_n(nbreNeuron, nbreLayout, nbreNeuronPerLayout);
    nbreNeuron[nbreNeuronPerLayout] = 10;

    Mnist test = Mnist(nbreData, nbreLearn, nbreTest, learningRate, nbreLayout, nbreNeuron);
    test.learn();
    test.test();


	Bptt* test = new Bptt();
	test->learn();
	test->test();

    Grammar grammar = createReber();
    vector<int> word = grammar.word();
    int* intWord = grammar.inputWord(word);
    int** input = new int*[1];
    input[0] = intWord;
    int* inputCount = new int[1];
    inputCount[0] = word.size();

    for(int i = 0; i < 100; i++){
        network.completeBatchLearning(input, inputCount, 1);
    }

    double* res;

    network.reset();
    network.setInput(intWord[0]);
    network.calculate();
    res = network.getOutput();
    PRINT_VECTOR(res, 7)
    network.setInput(intWord[1]);
    network.calculate();
    res = network.getOutput();
    PRINT_VECTOR(res, 7)
    network.setInput(intWord[2]);
    network.calculate();
    res = network.getOutput();
    PRINT_VECTOR(res, 7)
    network.setInput(intWord[3]);
    network.calculate();
    res = network.getOutput();
    PRINT_VECTOR(res, 7)
    */

    return 0;
}
