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

#include "grammar/grammar.hpp"

#include "rtrl/neuronNetwork.hpp"
#include "rtrl/mathFunctions.hpp"

#include "test/rtrl.hpp"

#define LOG
#define FILE_NAME "main.cpp\t\t"
#include "log.hpp"

int tab_log = 0;

using namespace std;

int main(int argc, const char *argv[]) {
    srand(time(NULL));
    /*vector<string> stringedArgv = vector<string>(unsigned(argc));
    bool log = isArgumentPresent("--log", stringedArgv);

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
    }*/
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
    Rtrl test = Rtrl();
    test.learn();
    test.test();

    return 0;
}
