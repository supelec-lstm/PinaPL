//
//  SigmoidActivationFunction.cpp
//  PinaPL
//

#include <math.h>

#include "SigmoidActivationFunction.hpp"


double SigmoidActivationFunction::calculateValue(double x) {
    return k / (1 + exp(-a * x));
}
