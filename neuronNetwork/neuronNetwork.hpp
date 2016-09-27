//
//  neuronNetwork.hpp
//  PinaPL
//

#ifndef DEF_NEURONNETWORK
#define DEF_NEURONNETWORK

#include <vector>

#include "../simpleNeuron/neuron.hpp"


using namespace std;

enum NeuronType : unsigned long {
    NeuronTypeInternal = 0,
    NeuronTypeInput = 1 << 0,
    NeuronTypeOutput = 1 << 1,
};

class NeuronNetwork {
    vector<Neuron> neurons;
    vector<vector<unsigned long>> connections;
    
    vector<unsigned long> inputNeurons;
    vector<double> inputValues;
    
public:
    NeuronNetwork();
    
    unsigned long addNeuron(Neuron neuron, NeuronType type);
    void changeNeuronType(unsigned long neuronIndex, NeuronType newType);
    void addConnection(unsigned long from, unsigned long to);
    void disconnectNeuron(unsigned long neuronIndex);
    
    vector<Neuron> getNeurons() const;
    vector<vector<unsigned long>> getConnections() const;
    void setNeurons(vector<Neuron> newNeurons);
    void setConnections(vector<vector<unsigned long>> newConnections);
    
    void compute();
};

#endif // DEF_NEURONNETWORK
