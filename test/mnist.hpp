//
//  mnist.hpp
//  PinaPL
//

#ifndef DEF_TEST_MNIST
#define DEF_TEST_MNIST

#include <vector>
#include <random>
#include <string.h>
#include <math.h>

#include "test.hpp"
#include "../perceptron/neuronNetwork.hpp"
#include "../perceptron/mathFunctions.hpp"

class Mnist : public Test{

    double learningRate;
    activationFunctionType function;
    NeuronNetwork* network;
    double** inputData;
    double** inputTest;
    double** outputData;
    double** outputTest;

    int nbreLearn;
    int nbreData;
    int nbreTest;
    int batchSize;

    int nbreInput;
    int nbreTotalNeuron;
    int nbreLayout;
    int* nbreNeuron;

    double** inputConverter(std::string path, int nbre);
    double** outputConverter(std::string path, int nbre);
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
