#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <random>
#include <string.h>
#include <math.h>
#include <Eigen/Dense>
#include <Eigen/Core>

#include "bptt.hpp"
#include "../bptt/neuronNetwork.hpp"
#include "../bptt/mathFunctions.hpp"

#include "../grammar/grammar.hpp"

#define LOG
#define FILE_NAME "bptt.cpp\t\t"
#include "../log.hpp"

#define NBATCH

using namespace std;
using namespace Eigen;

Bptt::Bptt(){
    PRINT_BEGIN_FUNCTION("Bptt")
    // Données à modifier

    this->foldCount = 5;
	this->wordCount = 30000;
	this->learnCount = 1;

	this->testCount = 4;
	this->learningRate = 0.1;
	this->function = SIGMOID;
	
    this->letterCount = 7;
    this->hiddenCount = 7;

	//Données à ne pas modifier

	this->neuronCount = this->letterCount + this->hiddenCount;

    this->inputData = new int*[this->wordCount];
    this->inputDataCount = new int[this->wordCount];

    this->network = new NeuronNetwork(this->letterCount, this->letterCount, this->neuronCount, this->foldCount, this->learningRate);

    this->setWeight();
    this->setFunctions();

    this->setGrammar();
    this->generateLearningSet();
    PRINT_END_FUNCTION()
}

void Bptt::learn(){
    PRINT_BEGIN_FUNCTION("learn")
    this->network->learn(this->inputData, this->inputDataCount, this->wordCount, this->learnCount);
    PRINT_END_FUNCTION()
}

void Bptt::generateLearningSet(){
    PRINT_BEGIN_FUNCTION("generateLearningSet")
    for(int i = 0; i < wordCount; i++){
        grammar->createWord();
        inputData[i] = grammar->inputWord();
        inputDataCount[i] = grammar->inputSize();
    }
    PRINT_END_FUNCTION()
}

void Bptt::test(){
	PRINT_BEGIN_FUNCTION("test")
	this->network->setInput(0, 0);
	this->network->calculate(0);
	cout << this->network->getOutput(0) << endl << endl;

	this->network->setInput(2, 1);
	this->network->calculate(1);
	cout << this->network->getOutput(1) << endl << endl;

	this->network->setInput(4, 1);
	this->network->calculate(1);
	cout << this->network->getOutput(1) << endl << endl;


	cout << this->network->getWeightInput() << endl << endl;
	cout << this->network->getWeightRecursive() << endl << endl;
	cout << this->network->getWeightBias() << endl << endl;
    /*vector<int> testWord;
    for(int i = 0; i < this->testCount; i++){

        this->grammar->reset();
        this->network->reset();

		int j = 0;

        while(!this->grammar->isTerminal()){

            int a = this->grammar->newLetter();
            this->network->setInput(a, j);
            this->network->calculate(j);
            VectorXd result = this->network->getOutput(j);
            double m = result[maximum(result)];
            for(int i = 0; i < 7; i++){
                result[i] = result[i]/m;
            }
            //this->score+=this->score(grammar->getProba(),result);
            PRINT_LOG(grammar->getState())
            PRINT_VECTOR(grammar->getProba(),this->nbreInput)
            PRINT_VECTOR(result, this->nbreInput)
            PRINT_LOG(this->score(grammar->getProba(), result))
            PRINT_LOG("-----")
        }
        testWord.clear();

		j = (j + 1) % this->nbreFold;
    }*/
    PRINT_END_FUNCTION()
}

void Bptt::setWeight(){
	PRINT_BEGIN_FUNCTION("setWeight")
    this->network->setRandomWeight(0.1);
	PRINT_END_FUNCTION()
}

void Bptt::setGrammar(){
	PRINT_BEGIN_FUNCTION("setGrammar")
    char* letters = new char[letterCount];
    letters[0] = 'B';
    letters[1] = 'E';
    letters[2] = 'P';
    letters[3] = 'S';
    letters[4] = 'T';
    letters[5] = 'V';
    letters[6] = 'X';

    int stateCount = 8;
    grammar = new Grammar(stateCount, letterCount, letters);

    grammar->setState(0, 1, 0, 1, 1);
    grammar->setState(1, 2, 4, 2, 2, 4, 1, 1);
    grammar->setState(2, 2, 3, 6, 2, 3, 1, 1);
    grammar->setState(3, 2, 6, 3, 4, 6, 1, 1);
    grammar->setState(4, 2, 4, 5, 4, 5, 1, 1);
    grammar->setState(5, 2, 2, 5, 3, 6, 1, 1);
    grammar->setState(6, 1, 1, 7, 1);
    grammar->setState(7, 0);

    grammar->setTerminated(7);
	PRINT_END_FUNCTION()
}

void Bptt::setFunctions(){
	PRINT_BEGIN_FUNCTION("setFunctions")
    this->network->setFunctions(this->function);
	PRINT_END_FUNCTION()
}

int Bptt::maximum(double* tab){
	PRINT_BEGIN_FUNCTION("maximum")
    int res = 0;
    for(int i = 1; i < this->letterCount; i++){
        if(tab[i] > tab[res]){
            res = i;
        }
    }
    return res;
	PRINT_END_FUNCTION()
}

double Bptt::score(double* probabilities, double* normalizedOutput){
	PRINT_BEGIN_FUNCTION("score")
    double accuracy = 0;
    bool* proba = new bool[this->letterCount];
    bool* result = new bool[this->letterCount];
    for(int i = 0; i < this->letterCount; i++){
        proba[i]=(probabilities[i]>0.3);
        result[i]=(normalizedOutput[i]>0.3);
        if (proba[i]==result[i]){
            accuracy+=1;
        }
    }
    return(accuracy/this->letterCount);
	PRINT_END_FUNCTION()
}