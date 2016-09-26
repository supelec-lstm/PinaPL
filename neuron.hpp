//
//  neuron.hpp
//  PinaPL
//

#ifndef DEF_NEURON
#define DEF_NEURON

class Neuron {
    double (*composition) (double[], unsigned long);
    double (*activation) (double);
    long inputCount;
    double *inputs;
    double *weights;
    double output;

public:
    Neuron(unsigned long count, double compositionFunction(double[], unsigned long), double activationFunction(double));

    double* getInputs();
    void setInputs(double* someInputs, unsigned long count);

    double* getWeights();
    void setWeights(double x[]);
    void setBalancedWeights();
    void setRandomWeights(double min, double max);
    
    double getOutput();
    void calculateOutuput();
};


#endif // DEF_NEURON
