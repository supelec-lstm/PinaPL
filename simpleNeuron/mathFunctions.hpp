//
//  mathFunctions.hpp
//  PinaPL
//
//  Created by Maxime on 9/26/16.
//  Copyright © 2016 PinaPL. All rights reserved.
//

#ifndef mathFunctions_hpp
#define mathFunctions_hpp

#include <stdio.h>


namespace compositionFunction {
    double sum(double x[], unsigned long n);
    double dist(double x[], unsigned long n);
}

namespace activationFunction {
    double heavyside(double x);
    double sigmoid(double x);
}

#endif /* mathFunctions_hpp */
