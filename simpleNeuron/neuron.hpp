//
//  neuron.hpp
//  PinaPL
//

#ifndef DEF_NEURON
#define DEF_NEURON

#include <vector>

#include "mathFunctions.hpp"


class Neuron {
    unsigned long inputCount;
    std::vector<double> weight;
    std::vector<double> input;
    double output;
    compositionFunction composition;
    activationFunction activation;

public:
    Neuron();
    Neuron(unsigned long count, compositionFunction compositionFunction, activationFunction activationFunction);
    void reset();
    std::string description();

    void setInputCount(unsigned long count);
    
    std::vector<double> getWeight() const;
    void setWeight(const std::vector<double> newWeight);
    void setBalancedWeight();
    void setRandomWeight(double min, double max);

    unsigned long getInputCount() const;
    std::vector<double> getInput() const;
    void setInput(const std::vector<double> newInput);

    double getOutput() const;
    void calculateOutput();

    compositionFunction getCompositionFunction();
    activationFunction getActivationFunction();
};


#endif // DEF_NEURON
