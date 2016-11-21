#ifndef mathFunctions_hpp
#define mathFunctions_hpp

#include <stdio.h>
#include <climits>
#include <vector>

typedef double (*ActivationFunctionMain) (double);
typedef double (*ActivationFunctionDerivative) (double);

enum activationFunctionType : unsigned long {
    RELU = 1,
    SIGMOID = 2,
    ARCTAN = 3,
    TANH = 4
};

double relu(double x);
double sigmoid(double x);
double arctan(double x);

double reluDerivate(double x);
double sigmoidDerivate(double x);
double arctanDerivate(double x);
double tanhDerivate(double x);


#endif /* mathFunctions_hpp */