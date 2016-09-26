//
//  SumCompositionFunction.hpp
//  PinaPL
//

#ifndef SumCompositionFunction_hpp
#define SumCompositionFunction_hpp

#include <stdio.h>
#include <vector>

#include "CompositionFunction.hpp"


using namespace std;

class SumCompositionFunction: public CompositionFunction {
public:
    SumCompositionFunction();
    
    double calculateValue(vector<double> x);
};

#endif /* SumCompositionFunction_hpp */
