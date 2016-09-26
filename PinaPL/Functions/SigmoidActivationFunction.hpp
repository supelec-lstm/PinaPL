//
//  SigmoidActivationFunction.hpp
//  PinaPL
//

#ifndef SigmoidActivationFunction_hpp
#define SigmoidActivationFunction_hpp

#include <stdio.h>

#include "ActivationFunction.hpp"


class SigmoidActivationFunction: public ActivationFunction {
    double k;
    double a;
    
public:
    double calculateValue(double x); // Calculates (k / (1 + exp(-a * x)))
};

#endif /* SigmoidActivationFunction_hpp */
