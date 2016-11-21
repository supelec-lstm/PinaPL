//
//  xor.hpp
//  PinaPL
//

#ifndef DEF_TEST_XOR
#define DEF_TEST_XOR

#include <vector>
#include <random>
#include <string.h>
#include <math.h>

#include "../test.hpp"
#include "../../perceptron/neuronNetwork.hpp"
#include "../../perceptron/mathFunctions.hpp"

class Xor : public Test{

	double learningRate;
	activationFunctionType function;
	NeuronNetwork* network;
	double** inputData;
	double** outputData;

	int nbreLearn;

	int nbreTotalNeuron;
	int nbreLayout;
	int* nbreNeuron;

	double** inputConverter();
	double** outputConverter();
	void setRelation();
	void setWeight();
	void setBias();
	void setFunctions();

public:
	Xor();
	void learn();
	void test();
};

#endif