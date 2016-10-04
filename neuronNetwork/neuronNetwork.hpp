//
//  neuronNetwork.hpp
//  PinaPL
//

#ifndef DEF_NETWORK
#define DEF_NETWORK

#include <string>

#include "../simpleNeuron/neuron.hpp"


class NeuronNetwork {
    std::string name;
    std::string date;
    
    unsigned long inputCount;
    unsigned long outputCount;
    unsigned long neuronsCount;
    Neuron **neurons;
    unsigned long *inputNeurons;
    unsigned long *outputNeurons;
    bool **relation;
    double *output;
    double *input;

public:
    NeuronNetwork(std::string name, std::string date, unsigned long nbin, unsigned long nbout, unsigned long ntot);
    void reset();
    std::string description();
    
    std::string getName();
    std::string getDate();
    unsigned long getInputCount();
    unsigned long getOutputCount();
    unsigned long getNeuronsCount();
    Neuron** getNeurons();
    unsigned long* getInputNeurons();
    unsigned long* getOutputNeurons();
    bool** getRelation();
    double* getInput();
    double* getOutput();
    
    void setRelation(bool **tab);
    void setInputNeurons(unsigned long *tab);
    void setOutputNeurons(unsigned long *tab);
    void setNeurons(Neuron **tab);

    void setInput(double *data);
    void calculate();

private:
    void plugInputIntoNeuron();
    void calculeNeurons();
    double leastSquareError(double x[], double y[], unsigned long n);
};


#endif // DEF_NETWORK
