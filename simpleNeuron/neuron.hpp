#ifndef DEF_NEURONE
#define DEF_NEURONE

class Neuron{

    public:

    Neuron();
    Neuron(unsigned long in, double compositionFunction(double[], unsigned long), double activationFunction(double));
    void compute();
    void reset();

    void setWeight(const double x[]);
    double* getWeight() const;
    void initWeight();

    void setInput(const double x[]);
    double getOutput() const;

    static double activationSigmoid(double x);
    static double activationHeavyside(double x);
    static double activationArctan(double x);

    static double compositionSum(double x[], unsigned long n);
    static double compositionDist(double x[], unsigned long n);

    private:

    unsigned long inputCount;
    double* weight;
    double* input;
    double output;
    double (*composition) (double[], unsigned long);
    double (*activation) (double);
};


#endif
