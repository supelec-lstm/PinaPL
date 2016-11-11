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
    weight = vector<double>(inputCount);
    input = vector<double>(inputCount);
    biais = 0;

    setBalancedWeight();
    reset();
}

Neuron::Neuron(unsigned long count, compositionFunction compositionFunction, activationFunction activationFunction) {
    activation = activationFunction;
    composition = compositionFunction;

    inputCount = count;
    weight = vector<double>(inputCount);
    input = vector<double>(inputCount);

    biais = 0;

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
    str << "        Biais: " << biais << endl;
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
    input = vector<double>(inputCount);
    weight = vector<double>(inputCount);
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
        double a = static_cast<double>(rand()) / RAND_MAX;
        while(a > 0.4 && a < 0.6){
            a = static_cast<double>(rand()) / RAND_MAX;
        }
        weight[i] = a * (max - min) + min;
    }
}

void Neuron::setBiais(double x) {
    biais = x;
}

double Neuron::getBiais() {
    return biais;
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
    vector<double> weightedInputs = vector<double>(inputCount);

    for (unsigned long i = 0; i < inputCount; i++) {
        weightedInputs[i] = input[i] * weight[i];
    }
    output = activation.main(composition.main(weightedInputs) + biais);
}

double Neuron::getCompositionDerivative(double x) {
    return composition.derivative(x);
}

double Neuron::getActivationDerivative() {
    return activation.derivative(output);
}