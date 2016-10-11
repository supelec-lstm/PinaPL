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
    double biais;
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

    void setBiais(double x);
    double getBiais();

    double getOutput() const;
    void calculateOutput();

    double getCompositionDerivative(double x);
    double getActivationDerivative();
};


#endif // DEF_NEURON
