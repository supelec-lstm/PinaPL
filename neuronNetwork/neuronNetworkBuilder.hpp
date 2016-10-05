//
//  neuronNetworkBuilder.hpp
//  PinaPL
//

#ifndef neuronNetworkBuilder_hpp
#define neuronNetworkBuilder_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <map>

#include "../simpleNeuron/neuron.hpp"
#include "neuronNetwork.hpp"


enum NeuronProperty : unsigned long {
    NeuronProportyNone = 0,
    NeuronProportyInput = 1 << 0,
    NeuronProportyOutput = 1 << 1
};

class NeuronNetworkBuilder {
    std::string name;
    std::string date;
    
    std::vector<Neuron> *neurons;
    std::vector<NeuronProperty> *properties;
    std::vector<std::vector<unsigned long>> *connections;
    
    compositionFunction defaultCompositionFunction;
    activationFunction defaultActivationFunction;
    
public:
    NeuronNetworkBuilder();
    NeuronNetworkBuilder(NeuronNetwork network);
    NeuronNetwork generateComputeNetwork(bool setRandomWeights, double min = 0, double max = 0);

    unsigned long addNeuron();
    unsigned long addNeuron(compositionFunction compositionFunction, activationFunction activationFunction);
    unsigned long* addNeurons(unsigned long count);
    unsigned long* addNeurons(unsigned long count, compositionFunction compositionFunction, activationFunction activationFunction);
    
    void removeNeuron(unsigned long index);
    void removeNeurons(unsigned long* indexes, unsigned long count);
    void removeNeuronsRange(unsigned long fromIndex, unsigned long toIndex);
    
    void addConnection(unsigned long fromIndex, unsigned long toIndex);
    void addManyConnectionsToOne(unsigned long fromIndex, unsigned long *toIndexes, unsigned long toIndexesCount);
    void addManyConnectionsToOneRange(unsigned long fromIndex, unsigned long toFirstIndex, unsigned long toLastIndex);
    void addOneConnectionToMany(unsigned long *fromIndexes, unsigned long fromIndexesCount, unsigned long toIndex);
    void addOneConnectionToManyRange(unsigned long fromFirstIndex, unsigned long fromLastIndex, unsigned long toIndex);
    void addManyConnectionsToMany(unsigned long *fromIndexes, unsigned long fromIndexesCount, unsigned long *toIndexes, unsigned long toIndexesCount);
    void addManyConnectionsToManyRange(unsigned long fromFirstIndex, unsigned long fromLastIndex, unsigned long toFirstIndex, unsigned long toLastIndex);
    void removeConnection(unsigned long from, unsigned long to);
    
    
    std::string getName();
    std::string getDate();
    Neuron getNeuron(unsigned long index);
    std::vector<Neuron>* getNeurons();
    NeuronProperty getPropertiesForNeuron(unsigned long index);
    std::vector<NeuronProperty>* getProperties();
    std::vector<std::vector<unsigned long>>* getConnections();
    compositionFunction getDefaultCompositionFunction();
    activationFunction getDefaultActivationFunction();

    void setName(std::string aName);
    void setDate(std::string aDate);
    void setNeuron(Neuron neuron, unsigned long index);
    void setNeurons(std::vector<Neuron> *someNeurons);
    void setPropertiesForNeuron(NeuronProperty property, unsigned long index);
    void setPropertiesForNeurons(NeuronProperty property, unsigned long *indexes, unsigned long count);
    void setPropertiesForNeuronRange(NeuronProperty property, unsigned long firstIndex, unsigned long lastIndex);
    void setProperties(std::vector<NeuronProperty> *someProperties);
    void setConnections(std::vector<std::vector<unsigned long>> *someConnections);
    void setDefaultCompositionFunction(compositionFunction compositionFunction);
    void setDefaultActivationFunction(activationFunction activationFunction);
};

#endif /* neuronNetworkBuilder_hpp */
