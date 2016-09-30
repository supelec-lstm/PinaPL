//
//  neuron.cpp
//  PinaPL
//

#include <math.h>
#include <random>
#include <string>
#include <iostream>

#include "neuron.hpp"

using namespace std;


Neuron::Neuron() {
    inputCount = 1;
    weight = new double[inputCount];
    input = new double[inputCount];

    setBalancedWeight();
    reset();
}

Neuron::Neuron(unsigned long count, double compositionFunction(double[], unsigned long), double activationFunction(double)) {
    activation = activationFunction;
    composition = compositionFunction;

    inputCount = count;
    weight = new double[inputCount];
    input = new double[inputCount];

    setBalancedWeight();
    reset();
}

void Neuron::reset() {
    for (unsigned int i = 0; i < inputCount; i++) {
        input[i] = 0;
    }
    output = 0;
}

// Number of entries

unsigned long Neuron::getInputCount() const{

    return inputCount;
}

// Weights

double* Neuron::getWeight() const {
    return weight;
}

void Neuron::setWeight(const double newWeight[]) {
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
        weight[i] = static_cast<double>(rand())*(max - min) + min;
    }
}

// Inputs & Output

double* Neuron::getInput() const {
    return input;
}

void Neuron::setInput(const double newInput[]) {
    for (unsigned long i = 0; i < inputCount; i++) {
        input[i] = newInput[i];
    }
}

double Neuron::getOutput() const {
    return output;
}

void Neuron::calculateOutput() {
    double *weightedInputs = new double[inputCount];

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

double Neuron::compositionSum(double x[], unsigned long n) {
    double sum = 0;
    for (unsigned long i = 0; i < n; i++) {
        sum += x[i];
    }
    return sum;
}

double Neuron::compositionDist(double x[], unsigned long n) {
    return 0;
}
