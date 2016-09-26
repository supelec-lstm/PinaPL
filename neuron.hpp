#ifndef DEF_NEURONE
#define DEF_NEURONE

class Neuron
{
    public:

    Neuron(int in, double compositionFunction(double[], int), double activationFunction(double));
    double compute(double x[]);
    void setWeight(double x[]);
    void initWeight();

    static double activationSigmoid(double x);
    static double activationHeavyside(double x);
    static double activationArctan(double x);

    static double compositionSum(double x[], int n);
    static double compositionDist(double x[], int n);

    private:

    int inputCount;
    double* weight;
    double (*composition) (double[], int);
    double (*activation) (double);
};


#endif
