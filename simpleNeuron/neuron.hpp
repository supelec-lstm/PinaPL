//
//  neuron.hpp
//  PinaPL
//

#include <vector>

#ifndef DEF_NEURON
#define DEF_NEURON


typedef double (*ActivationFunction) (double);
typedef double (*CompositionFunction) (std::vector<double>, unsigned long);

class Neuron {
    unsigned long inputCount;
    std::vector<double> weight;
    std::vector<double> input;
    double output;
    CompositionFunction composition;
    ActivationFunction activation;

public:
    Neuron();
    Neuron(unsigned long count, CompositionFunction compositionFunction, ActivationFunction activationFunction);
    void reset();
    std::string description();

    void setInputCount(unsigned long count);
    
    std::vector<double> getWeight() const;
    void setWeight(const std::vector<double> newWeight);
    void setBalancedWeight();
    void setRandomWeight(double min, double max);

    unsigned long getInputCount() const;
    std::vector<double> getInput() const;
    void setInput(const std::vector<double> newInput);

    double getOutput() const;
    void calculateOutput();

    // Math functions
    static double activationSigmoid(double x);
    static double activationHeavyside(double x);
    static double activationArctan(double x);
    static double activationLinear(double x);

    static double compositionSum(std::vector<double> x, unsigned long n);
    static double compositionDist(std::vector<double> x, unsigned long n);
};


#endif // DEF_NEURON
