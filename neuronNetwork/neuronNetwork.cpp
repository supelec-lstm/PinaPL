//
//  neuronNetwork.cpp
//  PinaPL
//

#include <string>
#include <iostream>
#include <stdlib.h>

#include "neuronNetwork.hpp"

#define MAX_DIFFERENCE_OUTPUT 0.001


using namespace std;

// Initialization

NeuronNetwork::NeuronNetwork(string givenName, string givenDate, unsigned long nbin, unsigned long nbout, unsigned long ntot) {
    name = givenName;
    date = givenDate;
    inputCount = nbin;
    outputCount = nbout;
    neuronsCount = ntot;

    input = new double[nbin];
    output = new double[ntot];

    // 2-dimensional array allocation
    relation = static_cast<bool**>(malloc(ntot * sizeof(bool*)));
    for (unsigned long i = 0; i < ntot; i++) {
        relation[i] = new bool[ntot];
    }

    inputNeurons = new unsigned long[nbin];
    outputNeurons = new unsigned long[nbout];
    neurons = static_cast<Neuron**>(malloc(ntot * sizeof(Neuron*)));
}

void NeuronNetwork::reset() {
    input = new double[inputCount];
    output = new double[neuronsCount];
    for (unsigned long i = 0; i < neuronsCount; i++) {
        neurons[i]->reset();
    }
}

void NeuronNetwork::setRelation(bool** tab) {
    relation = tab;
}

void NeuronNetwork::setInputNeurons(unsigned long* tab) {
    inputNeurons = tab;
}

void NeuronNetwork::setOutputNeurons(unsigned long* tab) {
    outputNeurons = tab;
}

void NeuronNetwork::setNeurons(Neuron* tab[]) {
    neurons = tab;
}

// Computing

void NeuronNetwork::setInput(double* data) {
    reset();
    for (unsigned long i = 0; i < inputCount; i++) {
        input[i] = data[i];
    }
}

void NeuronNetwork::calculate() {
    // Initialization
    double *outputAfter = new double[neuronsCount];
    for (unsigned long i = 0; i < neuronsCount; i++) {
        outputAfter[i] = neurons[i]->getOutput();
    }

    // Main loop
    do {
        for (unsigned long i = 0; i < neuronsCount; i++) {
            output[i] = outputAfter[i];
        }
        plugInputIntoNeuron();
        calculeNeurons();
        for (unsigned long i = 0; i < neuronsCount; i++) {
            outputAfter[i] = neurons[i]->getOutput();
        }
    } while(leastSquareError(output, outputAfter, neuronsCount) >= MAX_DIFFERENCE_OUTPUT);

    // Result
    for (unsigned long i = 0; i < neuronsCount; i++) {
        output[i] = outputAfter[i];
    }
}

void NeuronNetwork::plugInputIntoNeuron() {
    unsigned long length;
    unsigned long k;
    for (unsigned long j = 0; j < inputCount; j++) {
        double x[1];
        x[0] = input[j];
        neurons[inputNeurons[j]]->setInput(x);
    }
    for (unsigned long j = 0; j < neuronsCount; j++) {
        k = 0;
        length = neurons[j]->getInputCount();
        double *x = new double[length];
        for (unsigned long i = 0; i < neuronsCount; i++) {
            if (relation[i][j]) {
                x[k] = output[i];
                k++;
            }
        }
        if (k == length) {
            neurons[j]->setInput(x);
        }
    }
}

void NeuronNetwork::calculeNeurons() {
    for (unsigned long i = 0; i < neuronsCount; i++) {
        neurons[i]->calculateOutput();
    }
}

double* NeuronNetwork::getOutput() {
    double *result = new double[outputCount];
    for (unsigned long i = 0; i < outputCount; i++) {
        result[i] = output[outputNeurons[i]];
    }
    return result;
}

double NeuronNetwork::leastSquareError(double x[], double y[], unsigned long n) {
    double result = 0;
    for (unsigned long i = 0; i < n; i++) {
        double d = x[i] - y[i];
        result += d*d;
    }
    return result;
}
