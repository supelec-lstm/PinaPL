//
//  neuronNetwork.cpp
//  PinaPL
//

#include <string>
#include <sstream>
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

string NeuronNetwork::description() {
    stringstream str;
    str << "Name: " << name << endl;
    str << "Date: " << date << endl;
    str << "Number of neurons: " << neuronsCount << endl;
    str << "  Neurons: {" << endl;
    for (unsigned long i = 0; i < neuronsCount; i++) {
        str << "    #" << i << " { " << neurons[i]->description() << endl;
        str << "        Connected to: {";
        for (unsigned long j = 0; j < neuronsCount; j++) {
            if (relation[i][j])
                str << "  " << j;
        }
        str << "  }" << endl;
        str << "    }" << endl;
    }
    str <<  "}" << endl;
    
    str << "Number of input neurons: " << inputCount << endl;
    str << "  Input neurons: {";
    for (unsigned long i = 0; i < inputCount; i++) {
        str << "  " << inputNeurons[i] << "(" << input[i] << ")";
    }
    str << "  }" <<  endl;
    str << "Number of output neurons: " << outputCount << endl;
    str << "  Output neurons: {";
    for (unsigned long i = 0; i < outputCount; i++) {
        str << "  " << outputNeurons[i] << "(" << output[outputNeurons[i]] << ")";
    }
    str << "  }" <<  endl;

    return str.str();
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

void NeuronNetwork::setNeurons(Neuron **tab) {
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
    delete[] outputAfter;
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
        delete[] x;
    }
}

void NeuronNetwork::calculeNeurons() {
    for (unsigned long i = 0; i < neuronsCount; i++) {
        neurons[i]->calculateOutput();
    }
}

string NeuronNetwork::getName() {
    return name;
}

string NeuronNetwork::getDate() {
    return date;
}

unsigned long NeuronNetwork::getInputCount() {
    return inputCount;
}

unsigned long NeuronNetwork::getOutputCount() {
    return outputCount;
}

unsigned long NeuronNetwork::getNeuronsCount() {
    return neuronsCount;
}

Neuron** NeuronNetwork::getNeurons() {
    return neurons;
}

unsigned long* NeuronNetwork::getInputNeurons() {
    return inputNeurons;
}

unsigned long* NeuronNetwork::getOutputNeurons() {
    return outputNeurons;
}

bool** NeuronNetwork::getRelation() {
    return relation;
}

double* NeuronNetwork::getInput() {
    return input;
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
