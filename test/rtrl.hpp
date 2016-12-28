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

#include "test.hpp"
#include "../rtrl/neuronNetwork.hpp"
#include "../rtrl/mathFunctions.hpp"

class Mnist : public Test{

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
    Mnist();
    void learn();
    void test();
};

#endif
