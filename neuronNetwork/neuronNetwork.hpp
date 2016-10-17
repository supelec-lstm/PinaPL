//
//  neuronNetwork.hpp
//  PinaPL
//

#ifndef DEF_NETWORK
#define DEF_NETWORK

#include <string>

typedef double (*ActivationFunctionMain) (double);
typedef double (*ActivationFunctionDerivative) (double);

class NeuronNetwork {
    bool** relation;
    double** weight;
    double* biais;
    ActivationFunctionMain* functions;

    double* output;

    int inputCount;
    int outputCount;
    int neuronCount;

    int** nextNode;
    int* nextCount;
    int** previousNode;
    int* previousCount;
    bool* firstNode;

    void calculateOutput(bool* voisin);
    bool newNode(bool* voisin);

public:
    NeuronNetwork(int nbin, int nbout, int nbtot);
    void reset();

    void setRelation(bool** relation);
    void setWeight(double** weight);
    void setBiais(double* biais);
    void setActivation(ActivationFunctionMain* functions);
    void setInput(double*);

    double* getOutput();

    void calculate();
};


#endif // DEF_NETWORK
