//
//  neuronNetwork.hpp
//  PinaPL
//

#ifndef DEF_RTRL_NETWORK
#define DEF_RTRL_NETWORK

#include <string>
#include <vector>

typedef double (*ActivationFunctionMain) (double);
typedef double (*ActivationFunctionDerivative) (double);

class NeuronNetwork {
    double** weight;
    double** weightOutput;
    double* bias;
    ActivationFunctionMain* functions;

    double* put;
    double* output;
    double* neurons;

    int inputCount;
    int outputCount;
    int neuronCount;
    int putCount;

    double*** gradient;
    double** weightDifference;
    double** biasGradient;
    double* biasDifference;
    ActivationFunctionDerivative* functionsDerivative;
    double learningRate;

    void resetInput();
    void resetOutput();
    void resetBackPropagation();
    void resetGradient();

    void calculateGradient(int& outputTheorical);
    void applyWeight();
    void learn(int& inputData, int& outputTheorical);

    void stochasticLearning(int* inputData, int n);
    void batchLearning(int* inputData, int n);

public:
    NeuronNetwork(int nbin, int nbout, int nbtot, double learning);
    ~NeuronNetwork();
    void reset();
    void init();

    void setWeight(std::vector<std::vector<double> > weight);
    void setBias(std::vector<double> bias);
    void setActivation(std::vector<ActivationFunctionMain> functions);
    void setActivationDerivate(std::vector<ActivationFunctionDerivative> functions);
    void setInput(int& inputArg);

    double* getOutput();

    void calculate();

    void completeBatchLearning(int** inputData, int* inputDataCount, int n);
    void completeStochasticLearning(int** inputData, int* inputDataCount, int n);
};


#endif // DEF_NETWORK