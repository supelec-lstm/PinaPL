//
//  neuronNetwork.cpp
//  PinaPL
//

#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <Eigen/Dense>

#include "neuronNetwork.hpp"
#include "mathFunctions.hpp"

#define NLOG
#define FILE_NAME "neuronNetwork.cpp\t"
#include "../log.hpp"

using namespace std;
using namespace Eigen;

// Initialization

NeuronNetwork::NeuronNetwork(int inputCount, int outputCount, int neuronCount, int foldCount, double learningRate){
    PRINT_BEGIN_FUNCTION("New network instantiation")
    // Main information

	this->inputCount = inputCount;
	this->outputCount = outputCount;
	this->neuronCount = neuronCount;
	this->putCount = neuronCount + inputCount + 1;
	this->foldCount = foldCount;

    this->learningRate = learningRate;

    // Input/Output vector

	this->put = new VectorXd[this->foldCount];
    for(int i = 0; i < this->foldCount; i++){
		this->put[i] = VectorXd(this->putCount);
    }

    // Vector and matrice defining the network

    this->relation = MatrixXd(this->putCount, this->neuronCount);
    for(int i = 0; i < this->neuronCount; i++){
        this->relation(i, 0) = 1;
    }

	this->weight = MatrixXd(this->putCount, this->neuronCount);

    this->activationFunctions = new ActivationFunctionMain[this->neuronCount];

    // Learning

    this->gradient = new VectorXd[this->foldCount];
	for (int i = 0; i < this->foldCount; i++) {
		this->gradient[i] = VectorXd(this->neuronCount);
	}

	this->weightInverse = this->weight.block(0, this->inputCount + 1, this->neuronCount, this->neuronCount).transpose();
	this->weightDifference = MatrixXd(this->putCount, this->neuronCount);

    this->derivativeActivationFunctions = new ActivationFunctionDerivative[neuronCount];

    // Reset before running

    reset();
    PRINT_END_FUNCTION()
}

NeuronNetwork::~NeuronNetwork(){
	PRINT_BEGIN_FUNCTION("Network unallocation")
	delete(this->put);
    delete(this->activationFunctions);

    delete(this->gradient);
    delete(this->derivativeActivationFunctions);
    PRINT_END_FUNCTION()
}

void NeuronNetwork::reset(){
    PRINT_BEGIN_FUNCTION("Network calculus parameters reset")
    this->resetOutput();
    this->resetBackPropagation();
    this->resetGradient();
    PRINT_END_FUNCTION()
}

void NeuronNetwork::resetInput(){
    PRINT_BEGIN_FUNCTION("Network input")
    for(int j = 0; j < this->foldCount; j++){
		this->put[j].segment(1, this->inputCount) = VectorXd::Constant(0.0);
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::resetInput(int j){
    PRINT_BEGIN_FUNCTION("Network input")
	this->put[j].segment(1, this->inputCount) = VectorXd::Constant(0.0);
    PRINT_END_FUNCTION()
}

void NeuronNetwork::resetOutput(){
    PRINT_BEGIN_FUNCTION("Network input & output reset")
	for (int j = 0; j < this->foldCount; j++) {
		this->put[j] = VectorXd::Constant(0.0);
		this->put[j](0) = 1.0;
	}
    PRINT_END_FUNCTION()
}

void NeuronNetwork::resetBackPropagation(){
	PRINT_BEGIN_FUNCTION("Backpropagation parameters reset")
	weightDifference = MatrixXd::Constant(0.0);
    PRINT_END_FUNCTION()
}

void NeuronNetwork::resetGradient(){
    PRINT_BEGIN_FUNCTION("Gradient reset")
    for(int j = 0; j < foldCount; j++){
		gradient[j] = VectorXd::Constant(0.0);
    }
    PRINT_END_FUNCTION()
}

// Getters and setters

void NeuronNetwork::setRelation(vector<vector<bool> > relationArg){
    PRINT_BEGIN_FUNCTION("Setting relations")
    for(int i = 0; i < this->neuronCount; i++){
        for(int j = 1; j < this->putCount; j++){
			this->relation(i, j) = relationArg[i][j-1]?1:0;
        }
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::setWeight(vector<vector<double> > weightArg){
    PRINT_BEGIN_FUNCTION("Setting weights from an array")
    for(int i = 0; i < this->neuronCount; i++){
        for(int j = 1; j < this->putCount; j++){
			this->weight(i, j) = weightArg[i][j-1];
        }
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::setRandomWeight() {
	PRINT_BEGIN_FUNCTION("Setting weights from an array")
	this->weight = MatrixXd::Random();
	PRINT_END_FUNCTION()
}

void NeuronNetwork::setConstantWeight(double x)
{
}

void NeuronNetwork::setFunctions(vector<activationFunctionType> functions){
    PRINT_BEGIN_FUNCTION("Setting functions from an array")
    for(int i = 0; i < this->neuronCount; i++){
        switch(functions[i]){
            case SIGMOID:
				this->activationFunctions[i] = sigmoid;
				this->derivativeActivationFunctions[i] = sigmoidDerivate;
                break;

            case ARCTAN:
				this->activationFunctions[i] = arctan;
				this->derivativeActivationFunctions[i] = arctanDerivate;
                break;

            case TANH:
				this->activationFunctions[i] = tanh;
				this->derivativeActivationFunctions[i] = tanhDerivate;
                break;

            case RELU:
				this->activationFunctions[i] = relu;
				this->derivativeActivationFunctions[i] = reluDerivate;
                break;
        }
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::setInput(int inputArg, int j){
    PRINT_BEGIN_FUNCTION("Setting input")
    this->resetInput(j);
    this->put[j](inputArg + 1) = 1;
    PRINT_END_FUNCTION()
}

VectorXd* NeuronNetwork::getOutput(){
	PRINT_BEGIN_FUNCTION("Obtaining output")
	PRINT_END_FUNCTION()
	VectorXd* result = new VectorXd[this->foldCount];
	for (int i = 0; i < this->foldCount; i++) {
		result[i] = this->put[i].tail(this->outputCount);
	}
	return result;
}

VectorXd NeuronNetwork::getOutput(int j) {
	PRINT_BEGIN_FUNCTION("Obtaining output")
	PRINT_END_FUNCTION()
	return this->put[j].tail(this->outputCount);
}

// Calculate from the input

void NeuronNetwork::calculate(int fold){
    PRINT_BEGIN_FUNCTION("Output computing")
	this->put[fold].tail(this->neuronCount) = this->weight * this->put[fold-1];
	int indiceNeuron = this->inputCount + 1;
	for (int i = indiceNeuron; i < this->putCount; i++) {
		this->put[fold](i) = this->activationFunctions[i - indiceNeuron](this->put[fold](i));
	}
    PRINT_END_FUNCTION()
}

// Make a learning

void NeuronNetwork::calculateOutputGradient(int outputData, int fold){
	PRINT_BEGIN_FUNCTION("Output gradient computation")
	this->gradient[fold].tail(this->outputCount) = -(this->put[fold].tail(this->outputCount));
	this->gradient[fold](this->putCount - this->outputCount + outputData) += 1.0;
    PRINT_END_FUNCTION()
}

void NeuronNetwork::calculateGradient(int fold){
    PRINT_BEGIN_FUNCTION("Gradient computation")
	int indiceNeuron = this->inputCount + 1;
	VectorXd derivate(this->neuronCount);
	for (int i = 0; i < this->neuronCount; i++) {
		derivate(i) = this->derivativeActivationFunctions[i](this->put[fold](i + indiceNeuron));
	}

	this->gradient[fold] += this->weightInverse * this->gradient[fold+1];
	this->gradient[fold] = this->gradient[fold].cwiseProduct(derivate);

	this->weightDifference += gradient[fold] * put[fold].transpose();
    PRINT_END_FUNCTION()
}

void NeuronNetwork::applyWeight(){
	PRINT_BEGIN_FUNCTION("Setting weights from weight differences and learning rate")
		this->weight += this->weightDifference.cwiseProduct(this->relation) * this->learningRate;
    resetBackPropagation();
    PRINT_END_FUNCTION()
}

void NeuronNetwork::allExitLearn(int* outputData){
    PRINT_BEGIN_FUNCTION("Learning of a word")
	for (int i = 1; i < this->foldCount; i++) {
		this->calculate(i);
	}
	this->calculateOutputGradient(this->foldCount-1, outputData[this->foldCount-1]);
	for (int i = foldCount - 2; i > 0; i--) {
		this->calculateOutputGradient(i, outputData[i]);
		this->calculateGradient(i);
	}
    PRINT_END_FUNCTION()
}

void NeuronNetwork::lastExitLearn(int outputData) {
	PRINT_BEGIN_FUNCTION("Learning of a word")
	for (int i = 1; i < this->foldCount; i++) {
		this->calculate(i);
	}
	this->calculateOutputGradient(this->foldCount - 1, outputData);
	for (int i = this->foldCount - 2; i > 0; i--) {
		this->calculateGradient(i);
	}
	PRINT_END_FUNCTION()
}

void NeuronNetwork::slipperyLearn(int* inputData, int inputSize) {
	for (int j = 0; j < inputSize-1; j++) {
		this->resetInput();
		int firstFold = max(0, this->foldCount - j);
		for (int i = firstFold; i < this->foldCount; i++) {
			this->setInput(inputData[i + j - this->foldCount], i);
		}
		this->lastExitLearn(inputData[j+1]);
	}
	this->applyWeight();
}