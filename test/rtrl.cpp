#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <random>
#include <string.h>
#include <math.h>

#include "rtrl.hpp"
#include "../rtrl/neuronNetwork.hpp"
#include "../rtrl/mathFunctions.hpp"

#include "../grammar/grammar.hpp"

#define LOG
#define FILE_NAME "rtrl.cpp\t\t"
#include "../log.hpp"

#define NBATCH

using namespace std;

Rtrl::Rtrl(){

    // Données à modifier

    #ifdef BATCH
    nbreWords = 60000; // nombre de données à importer de la base d'apprentissage
    //nbreLearn = 1; // nombre de batch learnings avec les données ci-dessus
    //batchSize = 128; // taille des batchs
    #else
    nbreWords = 60000;
    //nbreLearn = 1;
    #endif

    nbreTest = 10;
    learningRate = 0.3;
    function = SIGMOID;

    // Données à ne pas modifier

    nbreInput = 7;

    nbreTotalNeuron = 14;
    PRINT_LOG("Importation des entrées")

    PRINT_LOG("Création du réseau")
    network = new NeuronNetwork(nbreInput, nbreInput, nbreTotalNeuron, learningRate);

    PRINT_LOG("Création de la matrice de relation")
    setRelation();

    PRINT_LOG("Création des poids")
    setWeight();

    PRINT_LOG("Création des fonctions")
    setFunctions();

    PRINT_LOG("Création de la grammaire")
    *grammar = createReber();
}

void Rtrl::learn(){
    #ifdef NBATCH
    PRINT_LOG("Apprentissage stochastique")
    generateLearningSet();
    network->completeStochasticLearning(inputData, inputDataCount, nbreWords);
    #endif
    //#ifdef BATCH
    //PRINT_LOG("Apprentissage par batch")
    //network->completebatchLearning(inputData, inputDataCount, nbreWords);
    //#endif
}

void Rtrl::generateLearningSet(){
    vector<int> word;
    for(int i  =0; i < nbreWords; i++){
        word = grammar->word();
        int* intWord = grammar->inputWord(word);
        inputData[i] = intWord;
        inputDataCount[i] = word.size();
    }
}

void Rtrl::test(){
    PRINT_BEGIN_FUNCTION("Tests")
    PRINT_LOG("Attendu - Obtenu")
    int** inputTest = new int*[nbreTest];      // Will contain test words
    int* inputTestCount = new int[nbreTest];       // Will contain word sizes
    int score = 0;
    vector<int> testWord;
    for(int i = 0; i < nbreTest; i++){

        grammar->reset();
        network->reset();
        // Running the network and the grammar
        while(!grammar->isWordFinished()){
            testWord.push_back(grammar->newLetter());
            int* probabilities = grammar->getProba();
            network->setInput(testWord.back());
            network->calculate();
            double* result = network->getOutput();
            //TODO : compare results and probabilities
        }
        testWord.clear();
    }
}



void Rtrl::setRelation(){
    vector<vector<bool> > relation(nbreTotalNeuron);
    for(int i = 0; i < nbreTotalNeuron; i++){
        vector<bool> v(nbreInput + nbreTotalNeuron, false);
        relation[i] = v;
        for(int j = 0; j < nbreInput + nbreTotalNeuron; j++){
            relation[i][j]=true; // TO CHECK
        }
    }
}

void Rtrl::setWeight(){
    vector<vector<double> > weight(nbreTotalNeuron);
    for(int i = 0; i < nbreTotalNeuron; i++){
        vector<double> v(nbreInput + nbreTotalNeuron, 0);
        weight[i] = v;
        for(int j = 0; j < nbreInput + nbreTotalNeuron; j++){
            weight[i][j] = randomizer(-0.1, 0.1);
        }
    }
    network->setWeight(weight);
}

void Rtrl::setFunctions(){
    vector<activationFunctionType> functions(nbreTotalNeuron, function);
    network->setFunctions(functions); // ?
}
/*
void Rtrl::readFile(string fileName){
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
int Rtrl::maximum(double* tab){
    int res = 0;
    for(int i = 1; i < nbreInput; i++){
        if(tab[i] > tab[res]){
            res = i;
        }
    }
    return res;
}
