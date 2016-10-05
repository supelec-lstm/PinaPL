//
//  neuronNetwork.hpp
//  PinaPL
//

#ifndef DEF_NETWORK
#define DEF_NETWORK

#include <string>
#include <vector>

#include "../simpleNeuron/neuron.hpp"


class NeuronNetwork {
    std::string name;
    std::string date;
    
    unsigned long inputCount;
    unsigned long outputCount;
    unsigned long neuronsCount;
    std::vector<Neuron*> neurons;
    std::vector<unsigned long> inputNeurons;
    std::vector<unsigned long> outputNeurons;
    std::vector<std::vector<bool>> relation;
    std::vector<std::vector<double>> weight;
    std::vector<double> output;
    std::vector<double> input;

public:
    NeuronNetwork(std::string name, std::string date, unsigned long nbin, unsigned long nbout, unsigned long ntot);
    void reset();
    std::string description();
    
    std::string getName();
    std::string getDate();
    unsigned long getInputCount();
    unsigned long getOutputCount();
    unsigned long getNeuronsCount();
    std::vector<Neuron*> getNeurons();
    std::vector<unsigned long> getInputNeurons();
    std::vector<unsigned long> getOutputNeurons();
    std::vector<std::vector<bool>> getRelation();
    std::vector<double> getInput();
    std::vector<double> getOutput();
    
    void setRelation(std::vector<std::vector<bool>> tab);
    void setInputNeurons(std::vector<unsigned long> tab);
    void setOutputNeurons(std::vector<unsigned long> tab);
    void setNeurons(std::vector<Neuron*> tab);

    void setInput(std::vector<double> data);
    void calculate();

    std::vector<double> computeGradient(std::vector<double> expectedOutput);
    std::vector<std::vector<double>> computeWeight(std::vector<double> gradient);
    void applyWeight(std::vector<std::vector<double>> difference);

    void onlineLearn(std::vector<std::vector<double>> dataInput, std::vector<std::vector<double>> dataOutput, unsigned long dataCount);
    void batchLearn(std::vector<std::vector<double>> dataInput, std::vector<std::vector<double>> dataOutput, unsigned long dataCount);

private:
    void plugInputIntoNeuron();
    void calculeNeurons();
    double leastSquareError(std::vector<double> x, std::vector<double> y, unsigned long n);
};


#endif // DEF_NETWORK
