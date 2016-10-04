#ifndef DEF_NETWORK
#define DEF_NETWORK

#include <string>

#include "neuron.hpp"

class NeuronNetwork{

    public:

    NeuronNetwork(std::string name, std::string date, unsigned long nbin, unsigned long nbout, unsigned long ntot);
    void reset();

    void setRelation(bool** tab);
    void setInputNeurons(unsigned long* tab);
    void setOutputNeurons(unsigned long* tab);
    void setNeurons(Neuron* tab);

    void setInput(double* data);
    void calculate();
    double* getOutput();

    private:

    std::string name;
    std::string date;

    unsigned long inputCount;
    unsigned long outputCount;
    unsigned long neuronsCount;
    Neuron *neurons;
    unsigned long* inputNeurons;
    unsigned long* outputNeurons;
    bool** relation;
    double* output;
    double* input;

    void plugInputIntoNeuron();
    void calculeNeurons();
    void getDifference();
};


#endif
