//
//  neuron.cpp
//  PinaPL
//

#include <random>

#include "neuron.hpp"


#pragma mark Initialization

Neuron::Neuron(unsigned long count, double compositionFunction(double[], unsigned long), double activationFunction(double)) {
    activation = activationFunction;
    composition = compositionFunction;

    inputCount = count;
    inputs = new double[inputCount];
    weights = new double[inputCount];
    output = 0;
}

#pragma mark - Inputs

double* Neuron::getInputs() {
    return inputs;
}

void Neuron::setInputs(double *someInputs, unsigned long count) {
    inputCount = count;
    inputs = someInputs;
// Should we reset weights here?
}

#pragma mark Weights

double* Neuron::getWeights() {
    return weights;
}

void Neuron::setWeights(double x[]) {
    for (unsigned long i = 0; i < inputCount; i++) {
        weights[i] = x[i];
    }
}

void Neuron::setBalancedWeights() {
    double a = 1 / ((double)inputCount);
    for (unsigned long i = 0; i < inputCount; i++) {
        weights[i] = a;
    }
}

void Neuron::setRandomWeights(double min, double max) {
    for (unsigned long i = 0; i < inputCount; i++) {
        weights[i] = (((double)rand()) / (RAND_MAX + 1.0) - min) * fabs(max - min);
    }
}

#pragma mark Output

double Neuron::getOutput() {
    return output;
}

void Neuron::calculateOutuput() {
    double weightedInputs[inputCount];
    
    for (unsigned long i = 0; i < inputCount; i++) {
        weightedInputs[i] = inputs[i] * weights[i];
    }
    
    output = activation(composition(weightedInputs, inputCount));
}

