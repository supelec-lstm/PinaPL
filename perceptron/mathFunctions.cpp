//
//  mathFunctions.cpp
//  PinaPL
//

#include <math.h>

#include "mathFunctions.hpp"


using namespace std;

// Activation functions

double relu(double x) {
    return (x < 0 ? 0 : x);
}

double sigmoid(double x) {
    double a = tanh(x/2);
    return (1+a)/2;
}

double arctan(double x) {
    return atan(x);
}

// Activation function derivatives

double reluDerivate(double x) {
    return (x > 0 ? 1 : 0);
}

double sigmoidDerivate(double x) {
    return x * (1 - x);
}

double arctanDerivate(double x) {
    double a = cos(x);
    return a*a;
}

double tanhDerivate(double x) {
    return (1-x*x);
}