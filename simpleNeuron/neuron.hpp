//
//  neuron.hpp
//  PinaPL
//

#ifndef DEF_NEURON
#define DEF_NEURON


typedef double (*ActivationFunction) (double);
typedef double (*CompositionFunction) (double[], unsigned long);

class Neuron {
    unsigned long inputCount;
    double* weight;
    double* input;
    double output;
    CompositionFunction composition;
    ActivationFunction activation;

public:
    Neuron();
    Neuron(unsigned long count, CompositionFunction compositionFunction, ActivationFunction activationFunction);
    void reset();
    std::string description();

    void setInputCount(unsigned long count);
    
    double* getWeight() const;
    void setWeight(const double newWeight[]);
    void setBalancedWeight();
    void setRandomWeight(double min, double max);

    unsigned long getInputCount() const;
    double* getInput() const;
    void setInput(const double newInput[]);

    double getOutput() const;
    void calculateOutput();

    // Math functions
    static double activationSigmoid(double x);
    static double activationHeavyside(double x);
    static double activationArctan(double x);
    static double activationLinear(double x);

    static double compositionSum(double x[], unsigned long n);
    static double compositionDist(double x[], unsigned long n);
};


#endif // DEF_NEURON
