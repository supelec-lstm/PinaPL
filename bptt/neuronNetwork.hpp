//
//  neuronNetwork.hpp
//  PinaPL
//

#ifndef DEF_PERCEPTRON_NETWORK
#define DEF_PERCEPTRON_NETWORK

#include <string>
#include <vector>

#include "mathFunctions.hpp"

class NeuronNetwork {
    bool** relation;
    bool** relationOutput;
    double** weight;
    double** weightOutput;
    ActivationFunctionMain* activationFunctions;

    double** put;
    double** input;
    double** output;
    double** neurons;

    int inputCount;
    int outputCount;
    int neuronCount;
    int putCount;
    int foldCount;

    int** nextNode;
    int* nextCount;
    int** previousNode;
    int* previousCount;

    double** gradient;
    double** weightDifference;
    ActivationFunctionDerivative* derivativeActivationFunctions;
    double learningRate;

    void resetInput();
    void resetInput(int j);
    void resetOutput();
    void resetBackPropagation();
    void resetGradient();

    void initNextNode();
    void initPreviousNode();

    void calculateOutputGradient(int outputData, int fold);
    void calculateGradient(int fold);
    void applyWeight();
    void learn(int* inputData, int inputSize);

public:
    NeuronNetwork(int nbin, int nbout, int nbtot, int nbfold, double learning);
    ~NeuronNetwork();
    void reset();
    void init();

    void setRelation(std::vector<std::vector<bool> > relation);
    void setWeight(std::vector<std::vector<double> > weight);
    void setFunctions(std::vector<activationFunctionType> functions);
    void setInput(int inputArg, int j);

    double** getOutput();
	double* getOutputFold(int j);

    void calculate(int fold);

    void stochasticLearning(int** inputData, int* inputSize, int nbreInput, int nbreLearning);
    void batchLearning(int** inputData, int* inputSize, int nbreInput, int batchSize, int nbreLearning);
};


#endif // DEF_NETWORK
