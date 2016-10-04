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
    
    neurons = new vector<Neuron>;
    properties = new vector<NeuronProperty>;
    connections = new vector<vector<unsigned long>>;
    
    defaultCompositionFunction = NULL;
    defaultActivationFunction = NULL;
}

NeuronNetworkBuilder::NeuronNetworkBuilder(NeuronNetwork network) {
    name = network.getName();
    date = network.getDate();
    
    neurons = new vector<Neuron>;
    properties = new vector<NeuronProperty>;
    connections = new vector<vector<unsigned long>>;
    
    defaultCompositionFunction = NULL;
    defaultActivationFunction = NULL;

    for (unsigned long i = 0; i < network.getNeuronsCount(); i++) {
        neurons->push_back(*network.getNeurons()[i]);
        properties->push_back(NeuronProportyNone);
        connections->push_back(vector<unsigned long>());
    }
    
    for (unsigned long i = 0; i < network.getInputCount(); i++)
        properties->at(network.getInputNeurons()[i]) = static_cast<NeuronProperty>(properties->at(network.getInputNeurons()[i]) | NeuronProportyInput);
    for (unsigned long i = 0; i < network.getOutputCount(); i++)
        properties->at(network.getOutputNeurons()[i]) = static_cast<NeuronProperty>(properties->at(network.getOutputNeurons()[i]) | NeuronProportyOutput);
    
    for (unsigned long i = 0; i < network.getNeuronsCount(); i++) {
        for (unsigned long j = 0; j < network.getNeuronsCount(); j++) {
            if (network.getRelation()[i][j])
                connections->at(i).push_back(j);
        }
    }
}

NeuronNetwork NeuronNetworkBuilder::generateComputeNetwork(bool setRandomWeights, double min, double max) {
    vector<unsigned long> inputs = vector<unsigned long>();
    vector<unsigned long> outputs = vector<unsigned long>();
    
    for (unsigned long i = 0; i < properties->size(); i++) {
        if (properties->at(i) & NeuronProportyInput)
            inputs.push_back(i);
        if (properties->at(i) & NeuronProportyOutput)
            outputs.push_back(i);
    }
    
    unsigned long *inputTable = new unsigned long[inputs.size()];
    for (unsigned long i = 0; i < inputs.size(); i++)
        inputTable[i] = inputs.at(i);
    
    unsigned long *outputTable = new unsigned long[outputs.size()];
    for (unsigned long i = 0; i < outputs.size(); i++)
        outputTable[i] = outputs.at(i);
    
    bool **relation = static_cast<bool**>(malloc(neurons->size() * sizeof(bool*)));
    unsigned long *inputCounts = new unsigned long[neurons->size()];
    for (unsigned long i = 0; i < neurons->size(); i++)
        inputCounts[i] = 0;

    for (unsigned long i = 0; i < neurons->size(); i++) {
        relation[i] = new bool[neurons->size()];
        for (unsigned long j = 0; j < connections->at(i).size(); j++) {
            relation[i][connections->at(i).at(j)] = true;
            inputCounts[connections->at(i).at(j)]++;
        }
    }

    Neuron **neuronTable = new Neuron*[neurons->size()];
    for (unsigned long i = 0; i < neurons->size(); i++) {
        if (inputCounts[i] == 0)
            inputCounts[i] = 1;
        neurons->at(i).setInputCount(inputCounts[i]);
        if (setRandomWeights)
            neurons->at(i).setRandomWeight(min, max);
        else
            neurons->at(i).setBalancedWeight();
        neuronTable[i] = &neurons->at(i);
    }
    
    delete[] inputCounts;

    NeuronNetwork network = NeuronNetwork(name, date, inputs.size(), outputs.size(), neurons->size());
    network.setNeurons(neuronTable);
    network.setRelation(relation);
    network.setInputNeurons(inputTable);
    network.setOutputNeurons(outputTable);
    network.reset();
    
    return network;
}

// Network builder functions

unsigned long NeuronNetworkBuilder::addNeuron() {
    Neuron newNeuron;
    if (defaultCompositionFunction && defaultActivationFunction)
        newNeuron = Neuron(1, defaultCompositionFunction, defaultActivationFunction);
    else
        newNeuron = Neuron();
    neurons->push_back(newNeuron);
    properties->push_back(NeuronProportyNone);
    connections->push_back(vector<unsigned long>());
    return neurons->size() - 1;
}

unsigned long NeuronNetworkBuilder::addNeuron(CompositionFunction compositionFunction, ActivationFunction activationFunction) {
    Neuron newNeuron = Neuron(1, compositionFunction, activationFunction);
    neurons->push_back(newNeuron);
    properties->push_back(NeuronProportyNone);
    connections->push_back(vector<unsigned long>());
    return neurons->size() - 1;
}

unsigned long* NeuronNetworkBuilder::addNeurons(unsigned long count) {
    unsigned long *indexes = new unsigned long[count];
    for (unsigned long i = 0; i < count; i++) {
        indexes[i] = this->addNeuron();
    }
    return indexes;
}

unsigned long* NeuronNetworkBuilder::addNeurons(unsigned long count, CompositionFunction compositionFunction, ActivationFunction activationFunction) {
    unsigned long *indexes = new unsigned long[count];
    for (unsigned long i = 0; i < count; i++) {
        indexes[i] = this->addNeuron(compositionFunction, activationFunction);
    }
    return indexes;
}

void NeuronNetworkBuilder::removeNeuron(unsigned long index) {
    neurons->erase(neurons->begin() + index);
    properties->erase(properties->begin() + index);
    connections->erase(connections->begin() + index);
    
    for (unsigned long i = 0; i < connections->size(); i++) {
        for (unsigned long j = 0; j < connections->at(i).size(); j++) {
            if (connections->at(i).at(j) == index) {
                connections->at(i).erase(connections->at(i).begin() + j);
                j--;
            } else if (connections->at(i).at(j) > index)
                connections->at(i).at(j)--;
        }
    }
}

void NeuronNetworkBuilder::removeNeurons(unsigned long* indexes, unsigned long count) {
    for (unsigned long i = 0; i < count; i++) {
        removeNeuron(indexes[i]);
    }
}

void NeuronNetworkBuilder::removeNeuronsRange(unsigned long fromIndex, unsigned long toIndex) {
    for (unsigned long i = fromIndex; i < toIndex + 1; i++) {
        removeNeuron(i);
    }
}

void NeuronNetworkBuilder::addConnection(unsigned long from, unsigned long to) {
    connections->at(from).push_back(to);
}

void NeuronNetworkBuilder::addManyConnectionsToOne(unsigned long fromIndex, unsigned long *toIndexes, unsigned long toIndexesCount) {
    for (unsigned long i = 0; i < toIndexesCount; i++) {
        addConnection(fromIndex, toIndexes[i]);
    }
}

void NeuronNetworkBuilder::addManyConnectionsToOneRange(unsigned long fromIndex, unsigned long toFirstIndex, unsigned long toLastIndex) {
    for (unsigned long i = toFirstIndex; i < toLastIndex + 1; i++) {
        addConnection(fromIndex, i);
    }
}

void NeuronNetworkBuilder::addOneConnectionToMany(unsigned long *fromIndexes, unsigned long fromIndexesCount, unsigned long toIndex) {
    for (unsigned long i = 0; i < fromIndexesCount; i++) {
        addConnection(fromIndexes[i], toIndex);
    }
}

void NeuronNetworkBuilder::addOneConnectionToManyRange(unsigned long fromFirstIndex, unsigned long fromLastIndex, unsigned long toIndex) {
    for (unsigned long i = fromFirstIndex; i < fromLastIndex + 1; i++) {
        addConnection(i, toIndex);
    }
}

void NeuronNetworkBuilder::addManyConnectionsToMany(unsigned long *fromIndexes, unsigned long fromIndexesCount, unsigned long *toIndexes, unsigned long toIndexesCount) {
    for (unsigned long i = 0; i < fromIndexesCount; i++) {
        for (unsigned long j = 0; j < toIndexesCount; j++) {
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
    for (unsigned long i = 0; i < connections->at(from).size(); i++) {
        if (connections->at(from).at(i) == to) {
            connections->at(from).erase(connections->at(from).begin() + i);
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
    return neurons->at(index);
}

vector<Neuron>* NeuronNetworkBuilder::getNeurons() {
    return neurons;
}

NeuronProperty NeuronNetworkBuilder::getPropertiesForNeuron(unsigned long index) {
    return properties->at(index);
}

vector<NeuronProperty>* NeuronNetworkBuilder::getProperties() {
    return properties;
}

vector<vector<unsigned long>>* NeuronNetworkBuilder::getConnections() {
    return connections;
}

// Setters

CompositionFunction NeuronNetworkBuilder::getDefaultCompositionFunction() {
    return defaultCompositionFunction;
}

ActivationFunction NeuronNetworkBuilder::getDefaultActivationFunction() {
    return defaultActivationFunction;
}

void NeuronNetworkBuilder::setName(string aName) {
    name = aName;
}

void NeuronNetworkBuilder::setDate(string aDate) {
    date = aDate;
}

void NeuronNetworkBuilder::setNeuron(Neuron neuron, unsigned long index) {
    (*neurons)[index] = neuron;
}

void NeuronNetworkBuilder::setNeurons(vector<Neuron> *someNeurons) {
    neurons = someNeurons;
}

void NeuronNetworkBuilder::setPropertiesForNeuron(NeuronProperty property, unsigned long index) {
    (*properties)[index] = property;
}

void NeuronNetworkBuilder::setPropertiesForNeurons(NeuronProperty property, unsigned long *indexes, unsigned long count) {
    for (unsigned long i = 0; i < count; i++)
        setPropertiesForNeuron(property, indexes[i]);
}

void NeuronNetworkBuilder::setPropertiesForNeuronRange(NeuronProperty property, unsigned long firstIndex, unsigned long lastIndex) {
    for (unsigned long i = firstIndex; i < lastIndex + 1; i++)
        setPropertiesForNeuron(property, i);
}

void NeuronNetworkBuilder::setProperties(vector<NeuronProperty> *someProperties) {
    properties = someProperties;
}

void NeuronNetworkBuilder::setConnections(vector<vector<unsigned long>> *someConnections) {
    connections = someConnections;
}

void NeuronNetworkBuilder::setDefaultCompositionFunction(CompositionFunction compositionFunction) {
    defaultCompositionFunction = compositionFunction;
}

void NeuronNetworkBuilder::setDefaultActivationFunction(ActivationFunction activationFunction) {
    defaultActivationFunction = activationFunction;
}

