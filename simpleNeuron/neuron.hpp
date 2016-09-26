//
//  neuron.hpp
//  PinaPL
//

#ifndef DEF_NEURON
#define DEF_NEURON

class Neuron
{
    public:

    Neuron(unsigned long in, double compositionFunction(double[], unsigned long), double activationFunction(double));
    double compute(double x[]);
    void setWeight(double x[]);
    void initWeight();

    static double activationSigmoid(double x);
    static double activationHeavyside(double x);
    static double activationArctan(double x);

    static double compositionSum(double x[], unsigned long n);
    static double compositionDist(double x[], unsigned long n);

    private:

    long inputCount;
    double *weight;
    double (*composition) (double[], unsigned long);
    double (*activation) (double);
};


#endif // DEF_NEURON
