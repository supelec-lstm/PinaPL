//
//  mathFunctions.cpp
//  PinaPL
//

#include <math.h>

#include "mathFunctions.hpp"


// Composition functions

double compositionFunctionMain::sum(double x[], unsigned long n) {
    double sum = 0;
    for (unsigned long i = 0; i < n; i++) {
        sum += x[i];
    }
    return sum;
}

double compositionFunctionMain::dist(double x[], unsigned long n) {
    return 0;
}

// Composition function derivatives

double compositionFunctionDerivative::sum(double x[], unsigned long n) {
    return n;
}

double compositionFunctionDerivative::dist(double x[], unsigned long n) {
    return 0;
}

// Activation functions

double activationFunctionMain::sigmoid(double x) {
    double a = 1 + exp(-x);
    return (1 / a);
}

double activationFunctionMain::heavyside(double x) {
    if (x < 0) {
        return 0;
    } else {
        return 1;
    }
}

double activationFunctionMain::arctan(double x) {
    return atan(x);
}

double activationFunctionMain::linear(double x) {
    return x;
}

// Activation function derivatives

double activationFunctionDerivative::sigmoid(double x) {
    return x * (1 - x);
}

double activationFunctionDerivative::heavyside(double x) {
    if (fabs(x) == 0) {
        return HUGE_VAL;
    }
    return 0;
}

double activationFunctionDerivative::arctan(double x) {
    return 1 / (x * x + 1);
}

double activationFunctionDerivative::linear(double x) {
    return 1;
}

inline compositionFunction makeCompositionFunction(CompositionFunctionMain main, CompositionFunctionDerivative derivative) {
    compositionFunction composition;
    composition.id = CompositionFunctionTypeOther;
    composition.main = main;
    composition.derivative = derivative;
    return composition;
}

const compositionFunction compositionFunctionSum = {CompositionFunctionTypeSum, &compositionFunctionMain::sum, &compositionFunctionDerivative::sum};

const compositionFunction compositionFunctionDist {CompositionFunctionTypeDist, &compositionFunctionMain::dist, &compositionFunctionDerivative::dist};


inline activationFunction makeActivationFunction(ActivationFunctionMain main, ActivationFunctionDerivative derivative) {
    activationFunction activation;
    activation.id = ActivationFunctionTypeOther;
    activation.main = main;
    activation.derivative = derivative;
    return activation;
}

const activationFunction activationFunctionHeavyside{ActivationFunctionTypeHeavyside, &activationFunctionMain::heavyside, &activationFunctionDerivative::heavyside};

const activationFunction activationFunctionSigmoid {ActivationFunctionTypeSigmoid, &activationFunctionMain::sigmoid, &activationFunctionDerivative::sigmoid};

const activationFunction activationFunctionArctan {ActivationFunctionTypeArctan, &activationFunctionMain::arctan, &activationFunctionDerivative::arctan};

const activationFunction activationFunctionLinear {ActivationFunctionTypeLinear, &activationFunctionMain::linear, &activationFunctionDerivative::linear};
