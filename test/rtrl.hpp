//
//  rtrl.hpp
//  PinaPL
//

#ifndef DEF_TEST_RTRL
#define DEF_TEST_RTRL

#include <vector>
#include <random>
#include <string.h>
#include <math.h>

#include "../grammar/grammar.hpp"
#include "test.hpp"
#include "../rtrl/neuronNetwork.hpp"
#include "../rtrl/mathFunctions.hpp"

class Rtrl : public Test{

    double learningRate;
    activationFunctionType function;
    NeuronNetwork* network;
    int** inputData;
    int* inputDataCount;
    double** outputData;
    double** outputTest;

    //int nbreLearn;
    int nbreWords;
    //int batchSize;

    int nbreInput;
    int nbreLearn;
    int nbreTotalNeuron;
    int nbreTest;

    int** inputTest;
    int* inputTestCount;

    void setWeight();
    void setFunctions();
    void setGrammar();
    void generateLearningSet();
    //void readFile(string fileName);

    int maximum(double* tab);

    Grammar* grammar;
public:
    Rtrl();
    void learn();
    void test();
};

#endif
