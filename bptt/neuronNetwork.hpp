//
//  neuronNetwork.hpp
//  PinaPL
//

#ifndef DEF_PERCEPTRON_NETWORK
#define DEF_PERCEPTRON_NETWORK

#include <string>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Core>

#include "mathFunctions.hpp"

class NeuronNetwork {

	Eigen::MatrixXd weightRecursive;
	Eigen::MatrixXd weightInput;
	Eigen::VectorXd weightBias;

    ActivationFunctionMain activationFunctions;

	int* input;
	Eigen::VectorXd* output;

    int inputCount;
    int outputCount;
    int neuronCount;
    int putCount;
    int foldCount;

    Eigen::VectorXd* gradient;
	Eigen::MatrixXd weightDifferenceRecursive;
	Eigen::MatrixXd weightDifferenceInput;
	Eigen::VectorXd weightDifferenceBias;
    ActivationFunctionDerivative derivativeActivationFunctions;
    double learningRate;

    void resetInput();
    void resetInput(int j);
    void resetOutput();
    void resetBackPropagation();
    void resetGradient();

    void calculateOutputGradient(int outputData, int fold);
    void calculateGradient(int fold);
    void applyWeight();

	void allExitLearn(int outputData, int start);
	void lastExitLearn(int outputData, int start);

public:
    NeuronNetwork(int nbin, int nbout, int nbtot, int nbfold, double learning);
    ~NeuronNetwork();
    void reset();

    void setWeight(std::vector<std::vector<double> > weight);
	void setRandomWeight(double amplitude);
	void setConstantWeight(double x);
    void setFunctions(activationFunctionType function);
    void setInput(int inputArg, int j);

    Eigen::VectorXd* getOutput();
	Eigen::VectorXd getOutput(int j);
	Eigen::MatrixXd getWeightRecursive();
	Eigen::MatrixXd getWeightInput();
	Eigen::MatrixXd getWeightBias();

    void calculate(int fold);

	void slipperyLearn(int* inputData, int inputSize);
	void staticLearn(int* inputData, int inputSize);
	void learn(int** inputData, int* inputSize, int wordCount, int learnCount);
};


#endif // DEF_NETWORK
