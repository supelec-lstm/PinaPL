//
//  Bptt.hpp
//  PinaPL
//

#ifndef DEF_TEST_BPTT
#define DEF_TEST_BPTT

#include <vector>
#include <random>
#include <string.h>
#include <math.h>

#include "../grammar/grammar.hpp"
#include "test.hpp"
#include "../bptt/neuronNetwork.hpp"
#include "../bptt/mathFunctions.hpp"

class Bptt : public Test{

    double learningRate;
    activationFunctionType function;

    NeuronNetwork* network;

    int** inputData;
    int* inputDataCount;

    int wordCount;
	int letterCount;
	int hiddenCount;

    int learnCount;
    int neuronCount;
    int testCount;
    int foldCount;

    int** inputTest;
    int* inputTestCount;

    void setWeight();
    void setFunctions();
    void setGrammar();
    void generateLearningSet();

    int maximum(double* tab);
    double score(double* probabilities, double* normalizedOutput);
    Grammar* grammar;
public:
    Bptt();
    void learn();
    void test();
};

#endif
