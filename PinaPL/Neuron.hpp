//
//  Neuron.h
//  PinaPL
//


#ifndef neuron_hpp
#define neuron_hpp

#include <stdio.h>
#include <vector>

#include "Functions/ActivationFunction.hpp"
#include "Functions/CompositionFunction.hpp"


using namespace std;

class Neuron {
private:
    vector<double> inputs;
    double output;
    
    vector<double> weights;
    
    CompositionFunction compositionFunction;
    ActivationFunction activationFunction;
    
public:
    Neuron(CompositionFunction aCompositionFunction, ActivationFunction anActivationFunction);
    
    vector<double> getWeights();
    void setWeights(vector<double> someWeights);
    void setRandomWeights(int count);
    
    CompositionFunction getCompositionFunction();
    ActivationFunction getActivationFunction();
    
    void setInputs(vector<double> someInputs);
    void calculateOutput();
    
    double getOutput();
};


#endif /* neuron_hpp */
