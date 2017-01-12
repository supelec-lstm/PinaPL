//
//  Bptt.hpp
//  PinaPL
//

#ifndef DEF_TEST_Bptt
#define DEF_TEST_Bptt

#include <vector>
#include <random>
#include <string.h>
#include <math.h>

#include "test.hpp"
#include "../Bptt/neuronNetwork.hpp"
#include "../Bptt/mathFunctions.hpp"

class Bptt : public Test{

    double learningRate;
    activationFunctionType function;
    NeuronNetwork* network;
    double** inputData;
    double** outputData;
    double** outputTest;

    int nbreLearn;
    int nbreWords;
    int batchSize;

    int nbreInput;
    int nbreTotalNeuron;

    void setRelation();
    void setWeight();
    void setFunctions();

    int maximum(double* tab);

public:
    Bptt();
    void learn();
    void test();
};

#endif
