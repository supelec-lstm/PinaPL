//
//  neuronNetwork.hpp
//  PinaPL
//

#ifndef DEF_PERCEPTRON_NETWORK
#define DEF_PERCEPTRON_NETWORK

#include <string>
#include <vector>
#include <Eigen/Dense>

#include "mathFunctions.hpp"

class NeuronNetwork {

	Eigen::MatrixXd relation;
	Eigen::MatrixXd weight;

    ActivationFunctionMain* activationFunctions;

	Eigen::VectorXd* put;

    int inputCount;
    int outputCount;
    int neuronCount;
    int putCount;
    int foldCount;

    Eigen::VectorXd* gradient;
	Eigen::MatrixXd weightInverse;
	Eigen::MatrixXd weightDifference;
    ActivationFunctionDerivative* derivativeActivationFunctions;
    double learningRate;

    void resetInput();
    void resetInput(int j);
    void resetOutput();
    void resetBackPropagation();
    void resetGradient();

    void calculateOutputGradient(int outputData, int fold);
    void calculateGradient(int fold);
    void applyWeight();

	void allExitLearn(int* outputData);
	void lastExitLearn(int outputData);

public:
    NeuronNetwork(int nbin, int nbout, int nbtot, int nbfold, double learning);
    ~NeuronNetwork();
    void reset();

    void setRelation(std::vector<std::vector<bool> > relation);
    void setWeight(std::vector<std::vector<double> > weight);
	void setRandomWeight();
	void setConstantWeight(double x);
    void setFunctions(std::vector<activationFunctionType> functions);
    void setInput(int inputArg, int j);

    Eigen::VectorXd* getOutput();
	Eigen::VectorXd getOutput(int j);

    void calculate(int fold);

	void slipperyLearn(int* inputData, int inputSize);
};


#endif // DEF_NETWORK
