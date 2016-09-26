//
//  Neuron.cpp
//  PinaPL
//


#include <math.h>
#include <random>

#include "Neuron.hpp"


Neuron::Neuron(CompositionFunction aCompositionFunction, ActivationFunction anActivationFunction) {
    compositionFunction = aCompositionFunction;
    activationFunction = anActivationFunction;
    
    weights = {0};
    inputs = {0};
    output = 0;
}

vector<double> Neuron::getWeights() {
    return weights;
}

void Neuron::setWeights(vector<double> someWeights) {
    
    vector<double> newWeights(someWeights);
    weights = newWeights;
}

void Neuron::setRandomWeights(int count) {
    weights = vector<double>(count);
    for (vector<double>::iterator it = weights.begin(); it != weights.end(); ++it) {
        *it = (((double)rand()) / (RAND_MAX + 1.0) - 0.5) / 5.0;
    }
}

CompositionFunction Neuron::getCompositionFunction() {
    return compositionFunction;
}

ActivationFunction Neuron::getActivationFunction() {
    return activationFunction;
}

void Neuron::setInputs(vector<double> someInputs) {
    vector<double> newInputs(someInputs);
    weights = newInputs;
}

void Neuron::calculateOutput() {
    double composedInput = compositionFunction.calculateValue(inputs);
    output = activationFunction.calculateValue(composedInput);
}

double Neuron::getOutput() {
    return output;
}
