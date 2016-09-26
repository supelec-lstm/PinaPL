//
//  neuron.cpp
//  PinaPL
//

#include <math.h>

#include "neuron.hpp"


Neuron::Neuron(unsigned long in, double compositionFunction(double[], unsigned long), double activationFunction(double)) {
    inputCount = in;
    weight = new double[in];
    activation = activationFunction;
    composition = compositionFunction;
}

double Neuron::compute(double x[]) {
    double y[inputCount];

    for(unsigned long i = 0; i < inputCount; i++) {
        y[i] = x[i] * weight[i];
    }
    return activation(composition(y, inputCount));
}

void Neuron::setWeight(double x[]) {
    for(unsigned long i = 0; i < inputCount; i++) {
        weight[i] = x[i];
    }
}

void Neuron::initWeight() {
    double a = 1 / ((double)inputCount);
    for (unsigned long i = 0; i < inputCount; i++) {
        weight[i] = a;
    }
}

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
