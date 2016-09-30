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

enum NeuronProporty {
    NeuronProportyNone = 0,
    NeuronProportyInput = 1 << 0,
    NeuronProportyOutput = 1 << 1
};

class neuronNetworkBuilder {
    std::string name;
    std::string date;
    
    std::vector<Neuron> *neurons;
    std::map<Neuron, NeuronProporty> properties;
    std::map<Neuron, std::vector<unsigned long>> connections;
    
public:
//    <#member functions#>
};

#endif /* neuronNetworkBuilder_hpp */
