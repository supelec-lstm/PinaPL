//
//  neuron.hpp
//  PinaPL
//

#ifndef DEF_NEURON
#define DEF_NEURON

#include "mathFunctions.hpp"


class Neuron {
    unsigned long inputCount;
    double* weight;
    double* input;
    double output;
    compositionFunction composition;
    activationFunction activation;

public:
    Neuron();
    Neuron(unsigned long count, compositionFunction compositionFunction, activationFunction activationFunction);
    void reset();
    std::string description();

    void setInputCount(unsigned long count);
    
    double* getWeight() const;
    void setWeight(const double newWeight[]);
    void setBalancedWeight();
    void setRandomWeight(double min, double max);

    unsigned long getInputCount() const;
    double* getInput() const;
    void setInput(const double newInput[]);

    double getOutput() const;
    void calculateOutput();
};


#endif // DEF_NEURON
