//
//  neuron.cpp
//  PinaPL
//

#include <math.h>
#include <random>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include "neuron.hpp"

using namespace std;

Neuron::Neuron() {
    inputCount = 1;
    weight = new vector<double>(inputCount);
    input = new vector<double>(inputCount);

    setBalancedWeight();
    reset();
}

Neuron::Neuron(unsigned long count, CompositionFunction compositionFunction, ActivationFunction activationFunction) {
    activation = activationFunction;
    composition = compositionFunction;

    inputCount = count;
    weight = new vector<double>(inputCount);
    input = new vector<double>(inputCount);

    setBalancedWeight();
    reset();
}

void Neuron::reset() {
    for (unsigned int i = 0; i < inputCount; i++) {
        input[i] = 0;
    }
    output = 0;
}

string Neuron::description() {
    stringstream str;
    str << "Number of inputs: " << inputCount << endl;
    str << "        Inputs: {";
    for (unsigned long i = 0; i < inputCount; i++) {
        str << "  " << input[i];
    }
    str << "  }" << endl;
    str << "        Weigths: {";
    for (unsigned long i = 0; i < inputCount; i++) {
        str << "  " << weight[i];
    }
    str << "  }" << endl;
    str << "        Output: " << output;
    return str.str();
}

void Neuron::setInputCount(unsigned long count) {
    inputCount = count;
    input = new double[inputCount];
    weight = new double[inputCount];
}

// Weights

vector<double> Neuron::getWeight() const {
    return weight;
}

void Neuron::setWeight(const vector<double> newWeight) {
    for (unsigned long i = 0; i < inputCount; i++) {
        weight[i] = newWeight[i];
    }
}

void Neuron::setBalancedWeight() {
    double balancedWeight = 1 / static_cast<double>(inputCount);
    for (unsigned long i = 0; i < inputCount; i++) {
        weight[i] = balancedWeight;
    }
}

void Neuron::setRandomWeight(double min, double max) {
    for (unsigned long i = 0; i < inputCount; i++) {
        weight[i] = static_cast<double>(rand()) / RAND_MAX * (max - min) + min;
    }
}

// Inputs & Output

unsigned long Neuron::getInputCount() const {
    return inputCount;
}

vector<double> Neuron::getInput() const {
    return input;
}

void Neuron::setInput(const vector<double> newInput) {
    for (unsigned long i = 0; i < inputCount; i++) {
        input[i] = newInput[i];
    }
}

double Neuron::getOutput() const {
    return output;
}

void Neuron::calculateOutput() {
    vector<double> weightedInputs = new vector<double>(inputCount);

    for (unsigned long i = 0; i < inputCount; i++) {
        weightedInputs[i] = input[i] * weight[i];
    }
    output = activation(composition(weightedInputs, inputCount));
}

// Activation functions

double Neuron::activationSigmoid(double x) {
    double a = 1 + exp(-x);
    return (1 / a);
}

double Neuron::activationHeavyside(double x) {
    if (x < 0) {
        return 0;
    } else {
        return 1;
    }
}

double Neuron::activationArctan(double x) {
    return atan(x);
}

double Neuron::activationLinear(double x) {
    return x;
}

// Composition functions

double Neuron::compositionSum(vector<double> x, unsigned long n) {
    double sum = 0;
    for (unsigned long i = 0; i < n; i++) {
        sum += x[i];
    }
    return sum;
}

double Neuron::compositionDist(vector<double> x, unsigned long n) {
    return 0;
}
