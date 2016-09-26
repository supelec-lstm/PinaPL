//
//  HeavisideActivationFunction.hpp
//  PinaPL
//

#ifndef HeavisideActivationFunction_hpp
#define HeavisideActivationFunction_hpp

#include <stdio.h>

#include "ActivationFunction.hpp"


class HeavisideActivationFunction: public ActivationFunction {
    
public:
    double calculateValue(double x);
};

#endif /* HeavisideActivationFunction_hpp */
