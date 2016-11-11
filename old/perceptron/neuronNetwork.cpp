//
//  neuronNetwork.cpp
//  PinaPL
//

#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>

#include "neuronNetwork.hpp"
#include "../simpleNeuron/neuron.hpp"

#define MAX_DIFFERENCE_OUTPUT 0.001
#define MAX_DIFFERENCE_ERROR 0


using namespace std;

// Initialization

NeuronNetwork::NeuronNetwork(string aName, string aDate, vector<Neuron> someNeurons, vector<unsigned long> someInputNeuronIndexes, vector<unsigned long> someOutputNeuronIndexes, vector<vector<bool>> neuronConnections, vector<vector<double>> connectionsIntitialWeights, double aLearningFactor) {
    name = aName;
    date = aDate;
    learningFactor = aLearningFactor;

    neurons = someNeurons;
    inputNeuronIndexes = someInputNeuronIndexes;
    outputNeuronIndexes = someOutputNeuronIndexes;

    connections = neuronConnections;
    connectionWeights = connectionsIntitialWeights;

    inputs = vector<double>(inputNeuronIndexes.size());
    allNeuronOutputs = vector<double>(neurons.size());

}

void NeuronNetwork::reset() {
    inputs = vector<double>(inputNeuronIndexes.size());
    allNeuronOutputs = vector<double>(neurons.size());
    for (unsigned long i = 0; i < neurons.size(); i++) {
        neurons[i].reset();
        allNeuronOutputs[i] = 0;
    }
    for (unsigned long i = 0; i < neurons.size(); i++) {
        neurons[inputNeuronIndexes[i]].setBalancedWeight();
        inputs[i] = 0;
    }
}

string NeuronNetwork::description() {
    stringstream str;
    str << "Name: " << name << endl;
    str << "Date: " << date << endl;
    str << "Number of neurons: " << neurons.size() << endl;
    str << "  Neurons: {" << endl;
    for (unsigned long i = 0; i < neurons.size(); i++) {
        str << "    #" << i << " { " << neurons[i].description() << endl;
        str << "        Connected to: {";
        for (unsigned long j = 0; j < neurons.size(); j++) {
            if (connections[i][j])
                str << "  " << j;
        }
        str << "  }" << endl;
        str << "    }" << endl;
    }
    str <<  "}" << endl;
    
    str << "Number of input neurons: " << inputNeuronIndexes.size() << endl;
    str << "  Input neurons: {";
    for (unsigned long i = 0; i < inputNeuronIndexes.size(); i++) {
        str << "  " << inputNeuronIndexes[i] << "(" << inputs[i] << ")";
    }
    str << "  }" <<  endl;
    str << "Number of output neurons: " << outputNeuronIndexes.size() << endl;
    str << "  Output neurons: {";
    for (unsigned long i = 0; i < outputNeuronIndexes.size(); i++) {
        str << "  " << outputNeuronIndexes[i] << "(" << allNeuronOutputs[outputNeuronIndexes[i]] << ")";
    }
    str << "  }" <<  endl;

    return str.str();
}

// Computing

void NeuronNetwork::setInput(vector<double> data) {
    reset();
    for (unsigned long i = 0; i < inputNeuronIndexes.size(); i++) {
        inputs[i] = data[i];
    }
}

void NeuronNetwork::calculate() {
    // Initialization
    vector<double> outputAfter(neurons.size());
    for (unsigned long i = 0; i < neurons.size(); i++) {
        outputAfter[i] = neurons[i].getOutput();
    }

    // Main loop
    do {
        for (unsigned long i = 0; i < neurons.size(); i++) {
            allNeuronOutputs[i] = outputAfter[i];
        }
        plugInputIntoNeuron();
        calculeNeurons();
        for (unsigned long i = 0; i < neurons.size(); i++) {
            outputAfter[i] = neurons[i].getOutput();
        }
    } while (leastSquareError(allNeuronOutputs, outputAfter, neurons.size()) > MAX_DIFFERENCE_OUTPUT);

    // Result
    for (unsigned long i = 0; i < neurons.size(); i++) {
        allNeuronOutputs[i] = outputAfter[i];
    }
}

void NeuronNetwork::plugInputIntoNeuron() {
    unsigned long length;
    unsigned long k;
    for (unsigned long j = 0; j < inputNeuronIndexes.size(); j++) {
        vector<double> x(1);
        x[0] = inputs[j];
        neurons[inputNeuronIndexes[j]].setInput(x);
    }
    for (unsigned long j = 0; j < neurons.size(); j++) {
        k = 0;
        length = neurons[j].getInputCount();
        vector<double> x(length);
        for (unsigned long i = 0; i < neurons.size(); i++) {
            if (connections[i][j]) {
                x[k] = allNeuronOutputs[i];
                k++;
            }
        }
        if (k == length) {
            neurons[j].setInput(x);
        }
    }
}

void NeuronNetwork::calculeNeurons() {
    for (unsigned long i = 0; i < neurons.size(); i++) {
        neurons[i].calculateOutput();
    }
}

string NeuronNetwork::getName() {
    return name;
}

string NeuronNetwork::getDate() {
    return date;
}

double NeuronNetwork::getLearningFactor() {
    return learningFactor;
}

unsigned long NeuronNetwork::getNeuronsCount() {
    return neurons.size();
}

unsigned long NeuronNetwork::getInputNeuronsCount() {
    return inputNeuronIndexes.size();
}

unsigned long NeuronNetwork::getOutputNeuronsCount() {
    return outputNeuronIndexes.size();
}

vector<Neuron> NeuronNetwork::getNeurons() {
    return neurons;
}

vector<unsigned long> NeuronNetwork::getInputNeuronIndexes() {
    return inputNeuronIndexes;
}

vector<unsigned long> NeuronNetwork::getOutputNeuronIndexes() {
    return outputNeuronIndexes;
}

vector<vector<bool>> NeuronNetwork::getConnections() {
    return connections;
}

vector<double> NeuronNetwork::getInputs() {
    return inputs;
}

vector<double> NeuronNetwork::getOutputs() {
    vector<double> result(outputNeuronIndexes.size());
    for (unsigned long i = 0; i < outputNeuronIndexes.size(); i++) {
        result[i] = allNeuronOutputs[outputNeuronIndexes[i]];
    }
    return result;
}

double NeuronNetwork::leastSquareError(vector<double> x, vector<double> y, unsigned long n) {
    double result = 0;
    for (unsigned long i = 0; i < n; i++) {
        double d = x[i] - y[i];
        result += d*d;
    }
    return result;
}

vector<double> NeuronNetwork::computeGradient(vector<double> expectedOutput) {
    vector<double> error(neurons.size(), 0);
    vector<double> gradient(neurons.size(), 0);
    vector<double> gradientBefore(neurons.size(), 0);
     
    do {
        for (unsigned long i = 0; i < neurons.size(); i++) {
            gradientBefore[i] = gradient[i];
            error[i] = 0;
            for (unsigned j = 0; j < neurons.size(); j++) {
                if (connections[i][j])
                    error[i] += connectionWeights[i][j] * gradient[j];
            }
        }
        for (unsigned long i = 0; i < outputNeuronIndexes.size(); i++) {
            error[outputNeuronIndexes[i]] = expectedOutput[i] - allNeuronOutputs[outputNeuronIndexes[i]];
        }
        for (unsigned long i = 0; i < neurons.size(); i++) {
            gradient[i] = error[i] * neurons[i].getActivationDerivative();
        }

    } while (leastSquareError(gradient, gradientBefore, neurons.size()) > MAX_DIFFERENCE_ERROR);

    for (unsigned long i = 0; i < inputNeuronIndexes.size(); i++)
        gradient[inputNeuronIndexes[i]] = 0;

    return gradient;
}

vector<vector<double>> NeuronNetwork::computeWeight(vector<double> gradient) {
    vector<vector<double>> result(neurons.size());

    for (unsigned long i = 0; i < neurons.size(); i++) {
        vector<double> v(neurons.size());
        result[i] = v;
        for (unsigned long j = 0; j < neurons.size(); j++) {
            result[i][j] = 0;
            if (connections[i][j]) {
                result[i][j] = gradient[j]*allNeuronOutputs[i];
            }
        }
    }

    return result;
}

void NeuronNetwork::applyWeight(vector<vector<double>> difference, vector<double> gradient) {
    for (unsigned long i = 0; i < neurons.size(); i++) {
        neurons[i].setBias(neurons[i].getBias() + gradient[i]);
        unsigned long k = 0;
        vector<double> v(neurons[i].getInputCount());
        for (unsigned long j = 0; j < neurons.size(); j++) {
            connectionWeights[i][j] += learningFactor * difference[i][j];
            if (connections[j][i]) {
                v[k] = connectionWeights[j][i];
                k++;
            }
        }
        if (k != 0)
            neurons[i].setWeight(v);
    }
}

void NeuronNetwork::onlineLearn(vector<vector<double>> dataInput, vector<vector<double>> dataOutput, unsigned long dataCount) {
    for (unsigned long i = 0; i < dataCount; i++) {
        reset();
        setInput(dataInput[i]);
        calculate();
        vector<double> gradient = computeGradient(dataOutput[i]);
        vector<vector<double>> difference = computeWeight(gradient);
        applyWeight(difference, gradient);
    }
}


void NeuronNetwork::batchLearn(vector<vector<double>> dataInput, vector<vector<double>> dataOutput, unsigned long dataCount) {
    vector<vector<double>> difference(neurons.size());
    for (unsigned long i = 0; i < neurons.size(); i++) {
        vector<double> v(neurons.size(), 0);
        difference[i] = v;
    }
    vector<double> gradients(neurons.size(), 0);
    for (unsigned long i = 0; i < dataCount; i++) {
        reset();
        setInput(dataInput[i]);
        calculate();
        vector<double> grad = computeGradient(dataOutput[i]);
        vector<vector<double>> diff = computeWeight(grad);
        for (unsigned long j = 0; j < neurons.size(); j++) {
            for (unsigned long k = 0; k < neurons.size(); k++)
                difference[i][j] += diff[i][j];
            gradients[i] += grad[i];
        }
    }
    applyWeight(difference, gradients);
}
