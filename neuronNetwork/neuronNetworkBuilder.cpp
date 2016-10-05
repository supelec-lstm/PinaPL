//
//  neuronNetworkBuilder.cpp
//  PinaPL
//

#include <iostream>
#include <ctime>

#include "neuronNetworkBuilder.hpp"


using namespace std;

// Initialization

NeuronNetworkBuilder::NeuronNetworkBuilder() {
    name = "New neuron network";
    
    time_t rawtime;
    time(&rawtime);
    struct tm *timeinfo = localtime(&rawtime);
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d", timeinfo);
    date = string(buffer);
    
    neurons = vector<Neuron>();
    properties = vector<NeuronProperty>();
    connections = vector<vector<unsigned long>>();
}

NeuronNetworkBuilder::NeuronNetworkBuilder(NeuronNetwork network) {
    name = network.getName();
    date = network.getDate();
    
    neurons = vector<Neuron>();
    properties = vector<NeuronProperty>();
    connections = vector<vector<unsigned long>>();

    for (unsigned long i = 0; i < network.getNeuronsCount(); i++) {
        neurons.push_back(network.getNeurons()[i]);
        properties.push_back(NeuronProportyNone);
        connections.push_back(vector<unsigned long>());
    }
    
    for (unsigned long i = 0; i < network.getInputCount(); i++)
        properties[network.getInputNeurons()[i]] = static_cast<NeuronProperty>(properties[network.getInputNeurons()[i]] | NeuronProportyInput);
    for (unsigned long i = 0; i < network.getOutputCount(); i++)
        properties[network.getOutputNeurons()[i]]= static_cast<NeuronProperty>(properties[network.getOutputNeurons()[i]] | NeuronProportyOutput);
    
    for (unsigned long i = 0; i < network.getNeuronsCount(); i++) {
        for (unsigned long j = 0; j < network.getNeuronsCount(); j++) {
            if (network.getRelation()[i][j])
                connections[i].push_back(j);
        }
    }
}

NeuronNetwork NeuronNetworkBuilder::generateComputeNetwork(bool setRandomWeights, double min, double max) {
    vector<unsigned long> inputs = vector<unsigned long>();
    vector<unsigned long> outputs = vector<unsigned long>();
    
    for (unsigned long i = 0; i < properties.size(); i++) {
        if (properties[i] & NeuronProportyInput)
            inputs.push_back(i);
        if (properties[i] & NeuronProportyOutput)
            outputs.push_back(i);
    }
    
    vector<vector<bool>> relations = vector<vector<bool>>(neurons.size());
    vector<unsigned long> inputCounts = vector<unsigned long>(neurons.size());
    for (unsigned long i = 0; i < neurons.size(); i++) {
        relations[i] = vector<bool>(neurons.size());
        for (unsigned long j = 0; j < connections[i].size(); j++) {
            relations[i][connections[i][j]] = true;
            inputCounts[connections[i][j]]++;
        }
    }

    for (unsigned long i = 0; i < neurons.size(); i++) {
        if (inputCounts[i] == 0)
            inputCounts[i] = 1;
        neurons[i].setInputCount(inputCounts[i]);
        if (setRandomWeights)
            neurons[i].setRandomWeight(min, max);
        else
            neurons[i].setBalancedWeight();
    }
    
    NeuronNetwork network = NeuronNetwork(name, date, inputs.size(), outputs.size(), neurons.size());
    network.setNeurons(neurons);
    network.setRelation(relations);
    network.setInputNeurons(inputs);
    network.setOutputNeurons(outputs);
    network.reset();
    
    return network;
}

// Network builder functions

unsigned long NeuronNetworkBuilder::addNeuron() {
    Neuron newNeuron;
    newNeuron = Neuron(1, defaultCompositionFunction, defaultActivationFunction);
    neurons.push_back(newNeuron);
    properties.push_back(NeuronProportyNone);
    connections.push_back(vector<unsigned long>());
    return neurons.size() - 1;
}

unsigned long NeuronNetworkBuilder::addNeuron(compositionFunction compositionFunction, activationFunction activationFunction) {
    Neuron newNeuron = Neuron(1, compositionFunction, activationFunction);
    neurons.push_back(newNeuron);
    properties.push_back(NeuronProportyNone);
    connections.push_back(vector<unsigned long>());
    return neurons.size() - 1;
}

vector<unsigned long> NeuronNetworkBuilder::addNeurons(unsigned long count) {
    vector<unsigned long> indexes =  vector<unsigned long>(count);
    for (unsigned long i = 0; i < count; i++) {
        indexes[i] = addNeuron();
    }
    return indexes;
}

vector<unsigned long> NeuronNetworkBuilder::addNeurons(unsigned long count, compositionFunction compositionFunction, activationFunction activationFunction) {
    vector<unsigned long> indexes = vector<unsigned long>(count);
    for (unsigned long i = 0; i < count; i++) {
        indexes[i] = addNeuron(compositionFunction, activationFunction);
    }
    return indexes;
}

void NeuronNetworkBuilder::removeNeuron(unsigned long index) {
    neurons.erase(neurons.begin() + index);
    properties.erase(properties.begin() + index);
    connections.erase(connections.begin() + index);
    
    for (unsigned long i = 0; i < connections.size(); i++) {
        for (unsigned long j = 0; j < connections[i].size(); j++) {
            if (connections[i][j] == index) {
                connections[i].erase(connections[i].begin() + j);
                j--;
            } else if (connections[i][j] > index)
                connections[i][j]--;
        }
    }
}

void NeuronNetworkBuilder::removeNeurons(vector<unsigned long> indexes) {
    for (unsigned long i = 0; i < indexes.size(); i++) {
        removeNeuron(indexes[i]);
    }
}

void NeuronNetworkBuilder::removeNeuronsRange(unsigned long fromIndex, unsigned long toIndex) {
    for (unsigned long i = fromIndex; i < toIndex + 1; i++) {
        removeNeuron(i);
    }
}

void NeuronNetworkBuilder::addConnection(unsigned long from, unsigned long to) {
    connections[from].push_back(to);
}

void NeuronNetworkBuilder::addManyConnectionsToOne(unsigned long fromIndex, vector<unsigned long> toIndexes) {
    for (unsigned long i = 0; i < toIndexes.size(); i++) {
        addConnection(fromIndex, toIndexes[i]);
    }
}

void NeuronNetworkBuilder::addManyConnectionsToOneRange(unsigned long fromIndex, unsigned long toFirstIndex, unsigned long toLastIndex) {
    for (unsigned long i = toFirstIndex; i < toLastIndex + 1; i++) {
        addConnection(fromIndex, i);
    }
}

void NeuronNetworkBuilder::addOneConnectionToMany(vector<unsigned long> fromIndexes, unsigned long toIndex) {
    for (unsigned long i = 0; i < fromIndexes.size(); i++) {
        addConnection(fromIndexes[i], toIndex);
    }
}

void NeuronNetworkBuilder::addOneConnectionToManyRange(unsigned long fromFirstIndex, unsigned long fromLastIndex, unsigned long toIndex) {
    for (unsigned long i = fromFirstIndex; i < fromLastIndex + 1; i++) {
        addConnection(i, toIndex);
    }
}

void NeuronNetworkBuilder::addManyConnectionsToMany(vector<unsigned long> fromIndexes, vector<unsigned long> toIndexes) {
    for (unsigned long i = 0; i < fromIndexes.size(); i++) {
        for (unsigned long j = 0; j < toIndexes.size(); j++) {
            addConnection(fromIndexes[i], toIndexes[j]);
        }
    }
}

void NeuronNetworkBuilder::addManyConnectionsToManyRange(unsigned long fromFirstIndex, unsigned long fromLastIndex, unsigned long toFirstIndex, unsigned long toLastIndex) {
    for (unsigned long i = fromFirstIndex; i < fromLastIndex + 1; i++) {
        for (unsigned long j = toFirstIndex; j < toLastIndex + 1; j++) {
            addConnection(i, j);
        }
    }
}

void NeuronNetworkBuilder::removeConnection(unsigned long from, unsigned long to) {
    for (unsigned long i = 0; i < connections[from].size(); i++) {
        if (connections[from][i] == to) {
            connections[from].erase(connections[from].begin() + i);
            i--;
        }
    }
}

// Getters

string NeuronNetworkBuilder::getName() {
    return name;
}

string NeuronNetworkBuilder::getDate() {
    return date;
}

Neuron NeuronNetworkBuilder::getNeuron(unsigned long index) {
    return neurons[index];
}

vector<Neuron> NeuronNetworkBuilder::getNeurons() {
    return neurons;
}

NeuronProperty NeuronNetworkBuilder::getPropertiesForNeuron(unsigned long index) {
    return properties[index];
}

vector<NeuronProperty> NeuronNetworkBuilder::getProperties() {
    return properties;
}

vector<vector<unsigned long>> NeuronNetworkBuilder::getConnections() {
    return connections;
}

// Setters

compositionFunction NeuronNetworkBuilder::getDefaultCompositionFunction() {
    return defaultCompositionFunction;
}

activationFunction NeuronNetworkBuilder::getDefaultActivationFunction() {
    return defaultActivationFunction;
}

void NeuronNetworkBuilder::setName(string aName) {
    name = aName;
}

void NeuronNetworkBuilder::setDate(string aDate) {
    date = aDate;
}

void NeuronNetworkBuilder::setNeuron(Neuron neuron, unsigned long index) {
    neurons[index] = neuron;
}

void NeuronNetworkBuilder::setNeurons(vector<Neuron> someNeurons) {
    neurons = someNeurons;
}

void NeuronNetworkBuilder::setPropertiesForNeuron(NeuronProperty property, unsigned long index) {
    properties[index] = property;
}

void NeuronNetworkBuilder::setPropertiesForNeurons(NeuronProperty property, vector<unsigned long> indexes) {
    for (unsigned long i = 0; i < indexes.size(); i++)
        setPropertiesForNeuron(property, indexes[i]);
}

void NeuronNetworkBuilder::setPropertiesForNeuronRange(NeuronProperty property, unsigned long firstIndex, unsigned long lastIndex) {
    for (unsigned long i = firstIndex; i < lastIndex + 1; i++)
        setPropertiesForNeuron(property, i);
}

void NeuronNetworkBuilder::setProperties(vector<NeuronProperty> someProperties) {
    properties = someProperties;
}

void NeuronNetworkBuilder::setConnections(vector<vector<unsigned long>> someConnections) {
    connections = someConnections;
}

void NeuronNetworkBuilder::setDefaultCompositionFunction(compositionFunction compositionFunction) {
    defaultCompositionFunction = compositionFunction;
}

void NeuronNetworkBuilder::setDefaultActivationFunction(activationFunction activationFunction) {
    defaultActivationFunction = activationFunction;
}

