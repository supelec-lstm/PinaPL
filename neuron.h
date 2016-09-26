#ifndef DEF_NEURONE
#define DEF_NEURONE

#include <string>

enum ActivationFunction {SIG, HEA, ARCT};
enum CompositionFunction {SUM, DIST};

class Neuron
{
    public:

    Neuron(int in, int out, ActivationFunction activationFunction, CompositionFunction compositionFunction);
    double compute(double x[]);

    private:

    int inputCount;
    int outputCount;
    double* weight;
    double (*composition) (double[], int);
    double (*activation) (double);

    static double activationSigmoid(double x);
    static double activationHeavyside(double x);
    static double activationArctan(double x);

    static double compositionSum(double x[], int n);
    static double compositionDist(double x[], int n);
};


#endif

