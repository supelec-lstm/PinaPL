//
//  neuronNetwork.cpp
//  PinaPL
//

#include "neuronNetwork.hpp"


NeuronNetwork::NeuronNetwork() {
    neurons = vector<Neuron>();
    connections = vector<vector<unsigned long>>();
}

// Building the network

unsigned long NeuronNetwork::addNeuron(Neuron neuron, NeuronType type) {
#warning type is not implemented yet
    neurons.push_back(neuron);
    connections.push_back(vector<unsigned long>());
    return neurons.size();
}

void NeuronNetwork::addConnection(unsigned long from, unsigned long to) {
    connections.at(from).push_back(to);
}

void NeuronNetwork::disconnectNeuron(unsigned long neuronIndex) {
    connections.at(neuronIndex) = vector<unsigned long>();
}

// Getters and Setters

vector<Neuron> NeuronNetwork::getNeurons() const {
    return neurons;
}

vector<vector<unsigned long>> NeuronNetwork::getConnections() const {
    return connections;
}

void NeuronNetwork::setNeurons(vector<Neuron> newNeurons) {
    neurons = vector<Neuron>(newNeurons);
    connections = vector<vector<unsigned long>>(newNeurons.size(), vector<unsigned long>());
}

void NeuronNetwork::setConnections(vector<vector<unsigned long>> newConnections) {
    connections = vector<vector<unsigned long>>(newConnections);
}

// Network flow

void NeuronNetwork::compute() {
#warning not implemented
}
