//
//  mathFunctions.cpp
//  PinaPL
//
//  Created by Maxime on 9/26/16.
//  Copyright © 2016 PinaPL. All rights reserved.
//

#include <math.h>

#include "mathFunctions.hpp"


#pragma mark Composition functions

double compositionFunction::sum(double x[], unsigned long n) {
    double sum = 0;
    for (unsigned long i = 0; i < n; i++) {
        sum += x[i];
    }
    return sum;
}

double compositionFunction::dist(double x[], unsigned long n) {
    return 0;
}

#pragma mark - Activation functions

double activationFunction::sigmoid(double x) {
    double a = 1 + exp(-x);
    return (1 / a);
}

double activationFunction::heavyside(double x) {
    if (x < 0) {
        return 0;
    } else {
        return 1;
    }
}

