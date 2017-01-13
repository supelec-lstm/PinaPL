#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <random>
#include <string.h>
#include <math.h>

#include "bptt.hpp"
#include "../bptt/neuronNetwork.hpp"
#include "../bptt/mathFunctions.hpp"

#include "../grammar/grammar.hpp"

#define LOG
#define FILE_NAME "bptt.cpp\t\t"
#include "../log.hpp"

#define NBATCH

using namespace std;

Bptt::Bptt(){
    PRINT_BEGIN_FUNCTION("Initialisation du Test")
    // Données à modifier

    #ifdef BATCH
    nbreFold = 5;
    nbreWords = 60000; // nombre de données à importer de la base d'apprentissage
    //nbreLearn = 1; // nombre de batch learnings avec les données ci-dessus
    //batchSize = 128; // taille des batchs
    #else
    nbreFold = 5;
    nbreWords = 10000;
    nbreLearn = 1;
    #endif

    nbreTest = 4;
    learningRate = 0.1;
    function = SIGMOID;
    threshold = 0.4;
    // Données à ne pas modifier

    nbreInput = 7;

    nbreTotalNeuron = 14;

    inputData = new int*[nbreWords];
    inputDataCount = new int[nbreWords];

    PRINT_LOG("Création du réseau")
    network = new NeuronNetwork(nbreInput, nbreInput, nbreTotalNeuron, learningRate);

    PRINT_LOG("Création des poids")
    setWeight();

    PRINT_LOG("Création des fonctions")
    setFunctions();

    PRINT_LOG("Création de la grammaire")
    setGrammar();

    PRINT_LOG("Importation des entrées")
    generateLearningSet();

    PRINT_END_FUNCTION()
}

void Bptt::learn(){
    PRINT_BEGIN_FUNCTION("Apprentissage stochastique")
    #ifdef NBATCH
    for(int i = 0; i < nbreLearn; i++){
        network->completeStochasticLearning(inputData, inputDataCount, nbreWords);
    }
    #endif
    //#ifdef BATCH
    //PRINT_LOG("Apprentissage par batch")
    //network->completebatchLearning(inputData, inputDataCount, nbreWords);
    //#endif
    PRINT_END_FUNCTION()
}

void Bptt::generateLearningSet(){
    PRINT_BEGIN_FUNCTION("Génération du set d'apprentissage")
    for(int i  =0; i < nbreWords; i++){
        grammar->createWord();
        inputData[i] = grammar->inputWord();
        inputDataCount[i] = grammar->inputSize();
    }
    PRINT_END_FUNCTION()
}

void Bptt::test(){
    PRINT_BEGIN_FUNCTION("Tests")
    /*PRINT_LOG("Attendu - Obtenu")
    int** inputTest = new int*[nbreTest];      // Will contain test words
    int* inputTestCount = new int[nbreTest];       // Will contain word sizes
    int score = 0;*/
    vector<int> testWord;
    for(int i = 0; i < nbreTest; i++){

        grammar->reset();
        network->reset();

        //PRINT_LOG(grammar->isTerminal())

        while(!grammar->isTerminal()){
            /*testWord.push_back(grammar->newLetter());
            double* probabilities = grammar->getProba();*/
            int a = grammar->newLetter();
            network->setInput(a);
            network->calculate();
            double* result = network->getOutput();
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
    }
    PRINT_END_FUNCTION()
}

void Bptt::setWeight(){
    vector<vector<double> > weight(nbreTotalNeuron);
    for(int i = 0; i < nbreTotalNeuron; i++){
        vector<double> v(nbreInput + nbreTotalNeuron, 0);
        weight[i] = v;
        for(int j = 0; j < nbreInput + nbreTotalNeuron; j++){
            weight[i][j] = randomizer(-0.5, 0.5);
        }
    }
    network->setWeight(weight);
}

void Bptt::setGrammar(){
    int nbreLetters = 7;
    char* letters = new char[nbreLetters];
    letters[0] = 'B';
    letters[1] = 'E';
    letters[2] = 'P';
    letters[3] = 'S';
    letters[4] = 'T';
    letters[5] = 'V';
    letters[6] = 'X';

    int nbreState = 8;
    grammar = new Grammar(nbreState, nbreLetters, letters);

    grammar->setState(0, 1, 0, 1, 1);
    grammar->setState(1, 2, 4, 2, 2, 4, 1, 1);
    grammar->setState(2, 2, 3, 6, 2, 3, 1, 1);
    grammar->setState(3, 2, 6, 3, 4, 6, 1, 1);
    grammar->setState(4, 2, 4, 5, 4, 5, 1, 1);
    grammar->setState(5, 2, 2, 5, 3, 6, 1, 1);
    grammar->setState(6, 1, 1, 7, 1);
    grammar->setState(7, 0);

    grammar->setTerminated(7);
}

void Bptt::setFunctions(){
    vector<activationFunctionType> functions(nbreTotalNeuron, function);
    network->setFunctions(functions);
}
/*
void Bptt::readFile(string fileName){
    ifstream fileStream(fileName);
    string word[];
    if(fileStream){
        cout << "While opening a file an error is encountered" << endl;
    }
    else{
        cout << "File is successfully opened" << endl;
    }
    while(!fileStream.eof()){
        fileStream >> word;
        cout << word << endl;
        // TODO : convert string into usable word
    }
}
*/
int Bptt::maximum(double* tab){
    int res = 0;
    for(int i = 1; i < nbreInput; i++){
        if(tab[i] > tab[res]){
            res = i;
        }
    }
    return res;
}

double Bptt::score(double* probabilities, double* normalizedOutput){
    double accuracy = 0;
    bool* proba = new bool[this->nbreInput];
    bool* result = new bool[this->nbreInput];
    for(int i = 0; i< this->nbreInput; i++){
        proba[i]=(probabilities[i]>this->threshold);
        result[i]=(normalizedOutput[i]>this->threshold);
        if (proba[i]==result[i]){
            accuracy+=1;
        }
    }
    return(accuracy/this->nbreInput);
}
