//
//  neuronNetwork.hpp
//  PinaPL
//

#ifndef DEF_PERCEPTRON_NETWORK
#define DEF_PERCEPTRON_NETWORK

#include <string>
#include <vector>

typedef double (*ActivationFunctionMain) (double);
typedef double (*ActivationFunctionDerivative) (double);

class NeuronNetwork {
    bool** relation;
    double** weight;
    double* bias;
    ActivationFunctionMain* functions;

    double* output;

    int inputCount;
    int outputCount;
    int neuronCount;

    int** nextNode;
    int* nextCount;
    int** previousNode;
    int* previousCount;
    int** nextNeighbor;
    int* nextNeighborCount;
    int nextNeighborTurnCount;
    int** previousNeighbor;
    int* previousNeighborCount;
    int previousNeighborTurnCount;

    double* gradient;
    double** weightDifference;
    double* biasDifference;
    ActivationFunctionDerivative* functionsDerivative;
    double learningRate;

    void resetOutput();
    void resetBackPropagation();
    void resetGradient();

    void initNextNode();
    void initPreviousNode();
    void initNextNeighbor();
    void initPreviousNeighbor();

    void calculateOutput(int* neighbor, int neighborCount);
    int newNextNeighbor(bool* voisin);
    int newPreviousNeighbor(bool* voisin);

    void calculateOutputGradient(double* outputTheorical);
    void calculateGradient(int* neighbor, int neighborCount);
    void applyWeight();
    void learn(double* input, double* outputTheorical);

public:
    NeuronNetwork(int nbin, int nbout, int nbtot, double learning);
    ~NeuronNetwork();
    void reset();
    void init();

    void setRelation(std::vector<std::vector<bool> > relation);
    void setWeight(std::vector<std::vector<double> > weight);
    void setBias(std::vector<double> bias);
    void setActivation(std::vector<ActivationFunctionMain> functions);
    void setActivationDerivate(std::vector<ActivationFunctionDerivative> functions);
    void setInput(double*);

    double* getOutput();

    void calculate();

    void stochasticLearning(double** input, int inputSize, double** outputTheorical, int nbreLearning);
    void batchLearning(double** input, int inputSize, double** outputTheorical, int nbreData, int nbreLearning);
};


#endif // DEF_NETWORK
