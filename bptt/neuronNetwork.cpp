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
#include <Eigen/Core>

#include "neuronNetwork.hpp"
#include "mathFunctions.hpp"

#define NLOG
#define FILE_NAME "neuronNetwork.cpp\t"
#include "../log.hpp"

using namespace std;
using namespace Eigen;

// Initialization

NeuronNetwork::NeuronNetwork(int inputCount, int outputCount, int neuronCount, int foldCount, double learningRate){
    PRINT_BEGIN_FUNCTION("NeuronNetwork")
    // Main information

	this->inputCount = inputCount;
	this->outputCount = outputCount;
	this->neuronCount = neuronCount;
	this->putCount = neuronCount + inputCount;
	this->foldCount = foldCount;

    this->learningRate = learningRate;

    // Input/Output vector

	this->input = new int[this->foldCount];
	this->output = new VectorXd[this->foldCount];
    for(int i = 0; i < this->foldCount; i++){
		this->output[i] = VectorXd(this->neuronCount);
    }

    // Vector and matrice defining the network

	this->weightRecursive = MatrixXd(this->neuronCount, this->neuronCount);
	this->weightInput = MatrixXd(this->neuronCount, this->inputCount);
	this->weightBias = VectorXd(this->neuronCount);

    // Learning

    this->gradient = new VectorXd[this->foldCount];
	for (int i = 0; i < this->foldCount; i++) {
		this->gradient[i] = VectorXd(this->neuronCount);
	}

	this->weightDifferenceRecursive = MatrixXd(this->neuronCount, this->neuronCount);
	this->weightDifferenceInput = MatrixXd(this->neuronCount, this->inputCount);
	this->weightDifferenceRecursive = VectorXd(this->neuronCount);

    // Reset before running

    reset();
    PRINT_END_FUNCTION()
}

NeuronNetwork::~NeuronNetwork(){
	PRINT_BEGIN_FUNCTION("~NeuronNetwork")
	delete(input);
	delete(output);

	delete(this->gradient);
    PRINT_END_FUNCTION()
}

void NeuronNetwork::reset(){
    PRINT_BEGIN_FUNCTION("reset")
    this->resetOutput();
    this->resetBackPropagation();
    this->resetGradient();
    PRINT_END_FUNCTION()
}

void NeuronNetwork::resetInput(){
    PRINT_BEGIN_FUNCTION("resetInput")
    for(int j = 0; j < this->foldCount; j++){
		this->input[j] = -1;
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::resetInput(int j){
	PRINT_BEGIN_FUNCTION("resetInput")
	this->input[j] = -1;
    PRINT_END_FUNCTION()
}

void NeuronNetwork::resetOutput(){
    PRINT_BEGIN_FUNCTION("resetOutput")
	for (int j = 0; j < this->foldCount; j++) {
		this->input[j] = -1;
		this->output[j] = VectorXd::Zero(this->neuronCount);
	}
    PRINT_END_FUNCTION()
}

void NeuronNetwork::resetBackPropagation(){
	PRINT_BEGIN_FUNCTION("resetBackPropagation")
	this->weightDifferenceRecursive = MatrixXd::Zero(this->neuronCount, this->neuronCount);
	this->weightDifferenceInput = MatrixXd::Zero(this->neuronCount, this->inputCount);
	this->weightDifferenceBias = VectorXd::Zero(this->neuronCount);
    PRINT_END_FUNCTION()
}

void NeuronNetwork::resetGradient(){
    PRINT_BEGIN_FUNCTION("resetGradient")
    for(int j = 0; j < foldCount; j++){
		this->gradient[j] = VectorXd::Zero(this->neuronCount);
    }
    PRINT_END_FUNCTION()
}

// Getters and setters

void NeuronNetwork::setWeight(vector<vector<double> > weightArg){
    PRINT_BEGIN_FUNCTION("setWeight")
    for(int i = 0; i < this->neuronCount; i++){
        for(int j = 0; j < this->inputCount; j++){
			this->weightInput(i, j) = weightArg[i][j];
        }
		for (int j = 0; j < this->neuronCount; j++) {
			this->weightRecursive(i, j) = weightArg[i][inputCount + j];
		}
		this->weightBias(i) = weightArg[i][putCount];
    }
    PRINT_END_FUNCTION()
}

void NeuronNetwork::setRandomWeight(double amplitude) {
	PRINT_BEGIN_FUNCTION("setRandomWeight")
	this->weightRecursive = (MatrixXd::Random(this->neuronCount, this->neuronCount) - MatrixXd::Constant(this->neuronCount, this->neuronCount, 0.5)) * amplitude;
	this->weightInput = (MatrixXd::Random(this->neuronCount, this->inputCount) - MatrixXd::Constant(this->neuronCount, this->inputCount, 0.5)) * amplitude;
	this->weightBias = (VectorXd::Random(this->neuronCount) - VectorXd::Constant(this->neuronCount, 0.5)) * amplitude;
	PRINT_END_FUNCTION()
}

void NeuronNetwork::setConstantWeight(double x){
	PRINT_BEGIN_FUNCTION("setConstantWeight")
	this->weightRecursive = MatrixXd::Constant(this->neuronCount, this->neuronCount, x);
	this->weightInput = MatrixXd::Constant(this->neuronCount, this->inputCount, x);
	this->weightBias = VectorXd::Constant(this->neuronCount, x);
	PRINT_END_FUNCTION()
}

void NeuronNetwork::setFunctions(activationFunctionType function){
    PRINT_BEGIN_FUNCTION("setFunctions")
	switch (function) {
	case SIGMOID:
		this->activationFunctions = sigmoid;
		this->derivativeActivationFunctions = sigmoidDerivate;
		break;

	case ARCTAN:
		this->activationFunctions = arctan;
		this->derivativeActivationFunctions = arctanDerivate;
		break;

	case TANH:
		this->activationFunctions = tanh;
		this->derivativeActivationFunctions = tanhDerivate;
		break;

	case RELU:
		this->activationFunctions = relu;
		this->derivativeActivationFunctions = reluDerivate;
		break;
	}
    PRINT_END_FUNCTION()
}

void NeuronNetwork::setInput(int inputArg, int j){
    PRINT_BEGIN_FUNCTION("setInput")
    this->input[j] = inputArg;
    PRINT_END_FUNCTION()
}

VectorXd* NeuronNetwork::getOutput(){
	PRINT_BEGIN_FUNCTION("getOutput")
	VectorXd* result = new VectorXd[this->foldCount];
	for (int i = 0; i < this->foldCount; i++) {
		result[i] = this->output[i].tail(this->outputCount);
	}
	PRINT_END_FUNCTION()
	return result;
}

VectorXd NeuronNetwork::getOutput(int j) {
	PRINT_BEGIN_FUNCTION("getOutput")
	PRINT_END_FUNCTION()
	return this->output[j].tail(this->outputCount);
}

MatrixXd NeuronNetwork::getWeightRecursive() {
	PRINT_BEGIN_FUNCTION("getWeightRecursive")
	PRINT_END_FUNCTION()
	return this->weightRecursive;
}

MatrixXd NeuronNetwork::getWeightInput() {
	PRINT_BEGIN_FUNCTION("getWeightInput")
		PRINT_END_FUNCTION()
		return this->weightInput;
}

MatrixXd NeuronNetwork::getWeightBias() {
	PRINT_BEGIN_FUNCTION("getWeightBias")
		PRINT_END_FUNCTION()
		return this->weightBias;
}

// Calculate from the input

void NeuronNetwork::calculate(int fold){
	PRINT_BEGIN_FUNCTION("calculate")
	PRINT_LOG(fold)
	PRINT_LOG(input[fold])
	VectorXd inter = this->weightInput.col(this->input[fold]) + this->weightBias;
	if (fold != 0) {
		inter += this->weightRecursive * this->output[fold - 1];
	}
	this->output[fold] = inter.unaryExpr(this->activationFunctions);
	PRINT_LOG(output[fold])
    PRINT_END_FUNCTION()
}

// Make a learning

void NeuronNetwork::calculateOutputGradient(int outputData, int fold){
	PRINT_BEGIN_FUNCTION("calculateOutputGradient")
	PRINT_LOG(fold)
	PRINT_LOG(outputData)
	this->gradient[fold].tail(this->outputCount) = - this->output[fold].tail(this->outputCount);
	this->gradient[fold](this->neuronCount - this->outputCount + outputData) += 1.0;
	PRINT_LOG(gradient[fold])
    PRINT_END_FUNCTION()
}

void NeuronNetwork::calculateGradient(int fold){
    PRINT_BEGIN_FUNCTION("calculateGradient")
	VectorXd derivate = this->output[fold].unaryExpr(this->derivativeActivationFunctions);
	if (fold != this->foldCount - 1) {
		this->gradient[fold] += this->weightRecursive.transpose() * this->gradient[fold + 1];
	}
	this->gradient[fold] = this->gradient[fold].cwiseProduct(derivate);

	this->weightDifferenceRecursive += this->gradient[fold] * this->output[fold].transpose();
	this->weightDifferenceInput.col(this->input[fold]) += this->gradient[fold];
	this->weightDifferenceBias += this->gradient[fold];
    PRINT_END_FUNCTION()
}

void NeuronNetwork::applyWeight(){
	PRINT_BEGIN_FUNCTION("applyWeight")
	this->weightRecursive -= this->weightDifferenceRecursive * this->learningRate;
	this->weightInput -= this->weightDifferenceInput * this->learningRate;
	this->weightBias -= this->weightDifferenceBias * this->learningRate;
    resetBackPropagation();
    PRINT_END_FUNCTION()
}

void NeuronNetwork::allExitLearn(int outputData, int start = 0){
    PRINT_BEGIN_FUNCTION("allExitLearn")
	for (int i = start; i < this->foldCount; i++) {
		this->calculate(i);
	}
	this->calculateOutputGradient(outputData, this->foldCount-1);
	this->calculateGradient(this->foldCount - 1);
	for (int i = this->foldCount - 2; i >= start; i--) {
		this->calculateOutputGradient(this->input[i+1], i);
		this->calculateGradient(i);
	}
	this->resetGradient();
    PRINT_END_FUNCTION()
}

void NeuronNetwork::lastExitLearn(int outputData, int start = 0) {
	PRINT_BEGIN_FUNCTION("lastExitLearn")
	for (int i = start; i < this->foldCount; i++) {
		this->calculate(i);
	}
	this->calculateOutputGradient(outputData, this->foldCount - 1);
	for (int i = this->foldCount - 1; i >= start; i--) {
		this->calculateGradient(i);
	}
	this->resetGradient();
	PRINT_END_FUNCTION()
}

void NeuronNetwork::staticLearn(int* inputData, int inputSize) {
	PRINT_BEGIN_FUNCTION("staticLearn")
	int n = (inputSize - 1) / this->foldCount;
	for (int j = 0; j < n; j++) {
		int k = j * this->foldCount;
		for (int i = 0; i < this->foldCount; i++) {
			this->setInput(inputData[i + k], i);
		}
		this->allExitLearn(inputData[this->foldCount + k]);
	}
	int j = (inputSize - 1) % this->foldCount;
	for (int i = this->foldCount - j; i < this->foldCount; i++) {
		this->setInput(inputData[i + (n-1)*this->foldCount + j], i);
	}
	this->allExitLearn(inputData[inputSize - 1], this->foldCount - j);
	this->applyWeight();
	PRINT_END_FUNCTION()
}

void NeuronNetwork::slipperyLearn(int* inputData, int inputSize) {
	PRINT_BEGIN_FUNCTION("slipperyLearn")
	for (int j = 0; j < inputSize-1; j++) {
		this->resetOutput();
		int firstFold = max(0, this->foldCount - j - 1);
		for (int i = firstFold; i < this->foldCount; i++) {
			this->setInput(inputData[i + j - this->foldCount + 1], i);
		}
		this->lastExitLearn(inputData[j+1], firstFold);
	}
	this->applyWeight();
	PRINT_END_FUNCTION()
}

void NeuronNetwork::learn(int** inputData, int* inputSize, int wordCount, int learnCount) {
	PRINT_BEGIN_FUNCTION("learn")
	for (int i = 0; i < learnCount; i++) {
		for (int j = 0; j < wordCount; j++) {
			this->staticLearn(inputData[j], inputSize[j]);
		}
	}
	PRINT_END_FUNCTION()
}
