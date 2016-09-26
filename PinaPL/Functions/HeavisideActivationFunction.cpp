//
//  HeavisideActivationFunction.cpp
//  PinaPL
//

#include "HeavisideActivationFunction.hpp"

double HeavisideActivationFunction::calculateValue(double x) {
    if (x < 0) {
        return -1;
    }
    if (x > 0) {
        return 1;
    }
    return 0;
}
