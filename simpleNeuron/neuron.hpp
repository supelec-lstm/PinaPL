//
//  neuron.hpp
//  PinaPL
//

#ifndef DEF_NEURON
#define DEF_NEURON

class Neuron {
    unsigned long inputCount;
    double* weight;
    double* input;
    double output;
    double (*composition) (double[], unsigned long);
    double (*activation) (double);

public:
    Neuron();
    Neuron(unsigned long count, double compositionFunction(double[], unsigned long), double activationFunction(double));
    void reset();

    double* getWeight() const;
    void setWeight(const double newWeight[]);
    void setBalancedWeight();
    void setRandomWeight(double min, double max);

    unsigned long getInputCount() const;
    double* getInput() const;
    void setInput(const double newInput[], unsigned long count);

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
