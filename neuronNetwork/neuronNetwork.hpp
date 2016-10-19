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
    
    double learningFactor;
    std::vector<Neuron> neurons;
    
    std::vector<unsigned long> inputNeuronIndexes;
    std::vector<unsigned long> outputNeuronIndexes;
    std::vector<std::vector<bool>> connections;
    std::vector<std::vector<double>> connectionWeights;
    std::vector<double> inputs;
    std::vector<double> allNeuronOutputs;

public:
    NeuronNetwork(std::string aName, std::string aDate, std::vector<Neuron> someNeurons, std::vector<unsigned long> someInputNeuronIndexes, std::vector<unsigned long> someOutputNeuronIndexes, std::vector<std::vector<bool>> neuronConnections, std::vector<std::vector<double>> connectionsIntitialWeights, double aLearningFactor);
    void reset();
    std::string description();
    
    std::string getName();
    std::string getDate();
    double getLearningFactor();

    unsigned long getNeuronsCount();
    unsigned long getInputNeuronsCount();
    unsigned long getOutputNeuronsCount();
    
    std::vector<Neuron> getNeurons();
    std::vector<unsigned long> getInputNeuronIndexes();
    std::vector<unsigned long> getOutputNeuronIndexes();
    std::vector<std::vector<bool>> getConnections();
    std::vector<double> getInputs();
    std::vector<double> getOutputs();
    
    void setInput(std::vector<double> data);
    void calculate();

    std::vector<double> computeGradient(std::vector<double> expectedOutput);
    std::vector<std::vector<double>> computeWeight(std::vector<double> gradient);
    void applyWeight(std::vector<std::vector<double>> difference, std::vector<double> gradient);

    void onlineLearn(std::vector<std::vector<double>> dataInput, std::vector<std::vector<double>> dataOutput, unsigned long dataCount);
    void batchLearn(std::vector<std::vector<double>> dataInput, std::vector<std::vector<double>> dataOutput, unsigned long dataCount);

private:
    void plugInputIntoNeuron();
    void calculeNeurons();
    double leastSquareError(std::vector<double> x, std::vector<double> y, unsigned long n);
};


#endif // DEF_NETWORK
