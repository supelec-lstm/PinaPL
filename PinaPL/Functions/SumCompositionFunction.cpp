//
//  SumCompositionFunction.cpp
//  PinaPL
//

#include "SumCompositionFunction.hpp"


double SumCompositionFunction::calculateValue(vector<double> x) {
    double sum = 0;
    for (vector<double>::iterator it = x.begin(); it != x.end(); ++it) {
        sum += *it;
    }
    return sum;
}
