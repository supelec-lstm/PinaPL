//
//  main.cpp
//  PinaPL
//

#include <iostream>

#include "Neuron.hpp"
#include "SumCompositionFunction.hpp"
#include "SigmoidActivationFunction.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    SumCompositionFunction composition;
    SigmoidActivationFunction activation;
    
    Neuron neuron(composition, activation);
    
    neuron.setWeights({1, 2});
    neuron.setInputs({0.1, -0.5});
    neuron.calculateOutput();
    
    cout << neuron.getOutput();
    
    return 0;
}
