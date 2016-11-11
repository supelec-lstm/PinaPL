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

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
class NeuronNetworkBuilder {
#pragma clang diagnostic pop
    std::string name;
    std::string date;
    double learningFactor;
    
    std::vector<Neuron> neurons;
    std::vector<NeuronProperty> properties;
    std::vector<std::vector<unsigned long>> connections;
    
    compositionFunction defaultCompositionFunction;
    activationFunction defaultActivationFunction;
    
    bool isPrepared;
    
public:
    NeuronNetworkBuilder();
    NeuronNetworkBuilder(NeuronNetwork network);
    void buildNeurons(bool setRandomWeights, double min = 0, double max = 0);
    NeuronNetwork generateComputationalNetwork();

    unsigned long addNeuron();
    unsigned long addNeuron(compositionFunction compositionFunction, activationFunction activationFunction);
    std::vector<unsigned long> addNeurons(unsigned long count);
    std::vector<unsigned long> addNeurons(unsigned long count, compositionFunction compositionFunction, activationFunction activationFunction);
    
    void removeNeuron(unsigned long index);
    void removeNeurons(std::vector<unsigned long> indexes);
    void removeNeuronsRange(unsigned long fromIndex, unsigned long toIndex);
    
    void addConnection(unsigned long fromIndex, unsigned long toIndex);
    void addOneConnectionToMany(unsigned long fromIndex, std::vector<unsigned long> toIndexes);
    void addOneConnectionToManyRange(unsigned long fromIndex, unsigned long toFirstIndex, unsigned long toLastIndex);
    void addManyConnectionsToOne(std::vector<unsigned long> fromIndexes, unsigned long toIndex);
    void addManyConnectionsToOneRange(unsigned long fromFirstIndex, unsigned long fromLastIndex, unsigned long toIndex);
    void addManyConnectionsToMany(std::vector<unsigned long> fromIndexes, std::vector<unsigned long> toIndexes);
    void addManyConnectionsToManyRange(unsigned long fromFirstIndex, unsigned long fromLastIndex, unsigned long toFirstIndex, unsigned long toLastIndex);
    void removeConnection(unsigned long from, unsigned long to);
    
    bool setWeighstForNeuron(unsigned long aNeuron, std::vector<double>weights);
    std::vector<bool> setWeightsForNeurons(std::vector<unsigned long> someNeurons, std::vector<double>weights);
    std::vector<bool> setWeightsForNeuronRange(unsigned long firstNeuron, unsigned long lastNeuron, std::vector<double>weights);
    
    std::string getName();
    std::string getDate();
    double getLearningFactor();
    Neuron getNeuron(unsigned long index);
    std::vector<Neuron> getNeurons();
    NeuronProperty getPropertiesForNeuron(unsigned long index);
    std::vector<NeuronProperty> getProperties();
    std::vector<std::vector<unsigned long>> getConnections();
    compositionFunction getDefaultCompositionFunction();
    activationFunction getDefaultActivationFunction();

    void setName(std::string aName);
    void setDate(std::string aDate);
    void setLearningFactor(double aLearningFactor);
    void setNeuron(Neuron neuron, unsigned long index);
    void setNeurons(std::vector<Neuron> someNeurons);
    void setPropertiesForNeuron(NeuronProperty property, unsigned long index);
    void setPropertiesForNeurons(NeuronProperty property, std::vector<unsigned long> indexes);
    void setPropertiesForNeuronRange(NeuronProperty property, unsigned long firstIndex, unsigned long lastIndex);
    void setProperties(std::vector<NeuronProperty> someProperties);
    void setConnections(std::vector<std::vector<unsigned long>> someConnections);
    void setDefaultCompositionFunction(compositionFunction compositionFunction);
    void setDefaultActivationFunction(activationFunction activationFunction);
};

#endif /* neuronNetworkBuilder_hpp */
