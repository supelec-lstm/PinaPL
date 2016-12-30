#include <iostream>
#include <map>
#include <vector>
#include <random>
#include <string.h>
#include <math.h>

#include "rtrl.hpp"
#include "../rtrl/neuronNetwork.hpp"
#include "../rtrl/mathFunctions.hpp"

#define LOG
#define FILE_NAME "rtrl.cpp\t\t"
#include "../log.hpp"

#define BATCH

using namespace std;

Rtrl::Rtrl(){

      // Données à modifier

      #ifdef BATCH
      nbreWords = 60000; // nombre de données à importer de la base d'apprentissage
      nbreLearn = 1; // nombre de batch learnings avec les données ci-dessus
      batchSize = 128; // taille des batchs
      #else
      nbreWords = 60000;
      nbreLearn = 1;
      #endif

      learningRate = 0.3;
      function = SIGMOID;

      // Données à ne pas modifier

     nbreInput = 26;

     nbreTotalNeuron = 0;
     PRINT_LOG("Importation des entrées")
     inputData = // TODO
     inputDataCount = // TODO

     PRINT_LOG("Création du réseau")
     network = new NeuronNetwork(nbreInput, nbreInput, nbreTotalNeuron, learningRate);

     PRINT_LOG("Création de la matrice de relation")
     setRelation();

     PRINT_LOG("Création des poids")
     setWeight();

     PRINT_LOG("Création des fonctions")
     setFunctions();

     PRINT_LOG("Initialisation du réseau")
     network->init();
}

void Rtrl::learn(){
    #ifdef NBATCH
    PRINT_LOG("Apprentissage stochastique")
    network->completestochasticLearning(inputData, inputDataCount, nbreWords);
    #endif
    #ifdef BATCH
    PRINT_LOG("Apprentissage par batch")
    network->completebatchLearning(inputData, inputDataCount, nbreWords);
    #endif
}

void Rtrl::test(){
    PRINT_BEGIN_FUNCTION("Tests")
    PRINT_LOG("Attendu - Obtenu")
    int** inputTest = new int*[nbreTest];      // Will contain test words
    int* inputTestCount = new int[nbreTest];       // Will contain word sizes
    int score = 0;
    for(int i = 0; i < nbreTest; i++){
        // Generating test word

        vector<int> testWord = grammar.word(); // Generate a test word
        int* intTestWord = grammar.inputWord(testWord); //Convert it
        inputTest[i] = intTestWord;
        int testWordSize = testWord.size();
        inputTestCount[i] = testWordSize;

        // Running the tests

        network->reset();
        for(int j = 0; j < testWordSize; j++){
            network->setInput(inputTest[i][j]);
            network->calculate();
            result = network->getOutput();
        }

        // TO COMPLETE
        }
    }
}

void Rtrl::setRelation(){
    vector<vector<bool> > relation(nbreTotalNeuron);
    for(int i = 0; i < nbreTotalNeuron; i++){
        vector<bool> v(nbreInput + nbreTotalNeuron, false);
        relation[i] = v;
        for(int j = 0; j < nbreInput + nbreTotalNeuron; j++){
            relation[i][j]=true // TO CHECK
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

int Mnist::maximum(double* tab){
    int res = 0;
    for(int i = 1; i < nbreInput; i++){
        if(tab[i] > tab[res]){
            res = i;
        }
    }
    return res;
}
