//
//  mathFunctions.hpp
//  PinaPL
//

#ifndef mathFunctions_hpp
#define mathFunctions_hpp

#include <stdio.h>
#include <climits>
#include <vector>


typedef double (*CompositionFunctionMain) (std::vector<double>, double);
typedef double (*CompositionFunctionDerivative) (double);
typedef double (*ActivationFunctionMain) (double);
typedef double (*ActivationFunctionDerivative) (double);


enum CompositionFunctionType : unsigned long {
    CompositionFunctionTypeSum = 1,
    CompositionFunctionTypeDist = 2,
    CompositionFunctionTypeOther = ULONG_MAX
};

enum ActivationFunctionType : unsigned long {
    ActivationFunctionTypeHeavyside = 1,
    ActivationFunctionTypeSigmoid = 2,
    ActivationFunctionTypeArctan = 3,
    ActivationFunctionTypeLinear = 4,
    ActivationFunctionTypeOther = ULONG_MAX
};


struct compositionFunction {
    CompositionFunctionType id;
    CompositionFunctionMain main;
    CompositionFunctionDerivative derivative;
};

struct activationFunction {
    ActivationFunctionType id;
    ActivationFunctionMain main;
    ActivationFunctionDerivative derivative;
};


namespace compositionFunctionMain {
    double sum(std::vector<double> x, double bias);
    double dist(std::vector<double> x, double bias);
}

namespace compositionFunctionDerivative {
    double sum(double x);
    double dist(double x);
}

namespace activationFunctionMain {
    double heavyside(double x);
    double sigmoid(double x);
    double arctan(double x);
    double linear(double x);
}

namespace activationFunctionDerivative {
    double heavyside(double x);
    double sigmoid(double x);
    double arctan(double x);
    double linear(double x);
}


inline compositionFunction makeCompositionFunction(CompositionFunctionMain main, CompositionFunctionDerivative derivative);
extern const compositionFunction compositionFunctionSum;
extern const compositionFunction compositionFunctionDist;

inline activationFunction makeActivationFunction(ActivationFunctionMain main, ActivationFunctionDerivative derivative);
extern const activationFunction activationFunctionHeavyside;
extern const activationFunction activationFunctionSigmoid;
extern const activationFunction activationFunctionArctan;
extern const activationFunction activationFunctionLinear;

#endif /* mathFunctions_hpp */
