//
//  neuron.cpp
//  PinaPL
//

#include <math.h>
#include <random>
#include <string>
#include <sstream>
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

Neuron::Neuron(unsigned long count, compositionFunction compositionFunction, activationFunction activationFunction) {
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
        weight[i] = static_cast<double>(rand()) / RAND_MAX * (max - min) + min;
    }
}

// Inputs & Output

unsigned long Neuron::getInputCount() const {
    return inputCount;
}

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
    output = activation.main(composition.main(weightedInputs, inputCount));
}
