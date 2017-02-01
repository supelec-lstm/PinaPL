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
    PRINT_BEGIN_FUNCTION("Initialisation du Test")
    // Données à modifier

    #ifdef BATCH
    nbreWords = 60000; // nombre de données à importer de la base d'apprentissage
    //nbreLearn = 1; // nombre de batch learnings avec les données ci-dessus
    //batchSize = 128; // taille des batchs
    #else
    nbreWords = 1;
    nbreLearn = 5000;
    #endif

    nbreTest = 1;
    learningRate = 0.2;
    function = SIGMOID;
    threshold = 0.3;
    // Données à ne pas modifier

    nbreInput = 7;

    nbreTotalNeuron = 21;

    inputData = new int*[nbreWords];
    inputDataCount = new int[nbreWords];

    PRINT_LOG("Création du réseau")
    network = new NeuronNetwork(nbreInput, nbreInput, nbreTotalNeuron, learningRate);

    PRINT_LOG("Création des poids")
    setWeight();

    PRINT_LOG("Création des fonctions")
    setFunctions();

    PRINT_LOG("Création de la grammaire")
    setSimpleGrammar();
    //setDoubleGrammar();

    PRINT_LOG("Importation des entrées")
    generateLearningSet();

    PRINT_END_FUNCTION()
}

void Rtrl::learn(){
    PRINT_BEGIN_FUNCTION("Apprentissage stochastique")
    #ifdef NBATCH
    // DEBUG
    for(int i = 0; i < inputDataCount[0]; i++){
        std::cout << inputData[0][i] << " " ;
    }
    std::cout << "starting tests" << std::endl;
    // END-DEBUG
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

void Rtrl::generateLearningSet(){
    PRINT_BEGIN_FUNCTION("Génération du set d'apprentissage")
    for(int i  =0; i < nbreWords; i++){
        grammar->createWord();
        inputData[i] = grammar->inputWord();
        inputDataCount[i] = grammar->inputSize();
    }
    PRINT_END_FUNCTION()
}

void Rtrl::test(){
    PRINT_BEGIN_FUNCTION("Tests")
    double* result;
    double m;
    for(int i = 0; i < nbreTest; i++){
        PRINT_LOG("================================")
        PRINT_LOG(i)
        PRINT_LOG("================================")
        grammar->reset();
        network->reset();

        while(!grammar->isTerminal()){
            int a = grammar->newLetter();
            network->setInput(a);
            network->calculate();
            result = network->getOutput();
            m = result[maximum(result)];
            /*for(int i = 0; i < 7; i++){
                result[i] = result[i]/m;
            }*/
            //this->score+=this->score(grammar->getProba(),result);
            PRINT_LOG(grammar->getState())
            PRINT_VECTOR(grammar->getProba(),this->nbreInput)
            PRINT_VECTOR(result, this->nbreInput)
            PRINT_LOG(this->score(grammar->getProba(), result))
            PRINT_LOG("-----")
        }
    }
    PRINT_END_FUNCTION()
}


void Rtrl::testDEBUG(){
    PRINT_BEGIN_FUNCTION("Tests")
    double* result;
    double m;
    grammar->reset();
    network->reset();

    for(int i = 0; i < inputDataCount[0]; i++){
      int a = inputData[0][i];
      network->setInput(a);
      network->calculate();
      result = network->getOutput();
      m = result[maximum(result)];
      /*for(int i = 0; i < 7; i++){
          result[i] = result[i]/m;
      }*/
      //this->score+=this->score(grammar->getProba(),result);
      PRINT_LOG(a)
      PRINT_VECTOR(result, this->nbreInput)
      PRINT_LOG("-----")
    }
    PRINT_END_FUNCTION()
}

void Rtrl::testDouble(){
  PRINT_BEGIN_FUNCTION("Tests")
  int score= 0;
  for(int i = 0; i < nbreTest; i++){

    grammar->reset();
    network->reset();

    grammar->createWord();
    grammar->inputWord();
    int a=grammar->newLetter();
    while(a != 1){
      network->setInput(a);
      network->calculate();
      int a = grammar->newLetter();
      }
    network->setInput(a);
    network->calculate();
    double* result = network->getOutput();
    double* theoricalResult = grammar->getProba();
    if (this->maximum(result) == this->maximum(theoricalResult)) {
      score++;
    }
  }
  cout << score << endl;
  PRINT_END_FUNCTION()
}


void Rtrl::setWeight(){
    vector<vector<double> > weight(nbreTotalNeuron);
    for(int i = 0; i < nbreTotalNeuron; i++){
        vector<double> v(nbreInput + nbreTotalNeuron +1, 0);
        weight[i] = v;
        for(int j = 0; j < nbreInput + nbreTotalNeuron +1; j++){
            weight[i][j] = randomizer(-1, 1);
        }
    }
    network->setWeight(weight);
}

void Rtrl::setSimpleGrammar(){
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

void Rtrl::setDoubleGrammar(){
  int nbreLetters = 7;
  char* letters = new char[nbreLetters];
  letters[0] = 'B';
  letters[1] = 'E';
  letters[2] = 'P';
  letters[3] = 'S';
  letters[4] = 'T';
  letters[5] = 'V';
  letters[6] = 'X';

  int nbreState = 20;
  grammar = new Grammar(nbreState, nbreLetters, letters);
  //grammar->setState(stateNumber,nextStateCount,(transitionLetter,nextStateNumber,probability)...);
  grammar->setState(0, 1, 0, 1, 1);
  grammar->setState(1, 2, 4, 2, 2, 10, 1, 1);
  grammar->setState(2, 1, 0, 3, 1);
  grammar->setState(3, 2, 4, 2, 4, 6, 1, 1);
  grammar->setState(4, 2, 3, 6, 4, 5, 1, 1);
  grammar->setState(5, 2, 6, 3, 6, 8, 1, 1);
  grammar->setState(6, 2, 4, 5, 6, 7, 1, 1);
  grammar->setState(7, 2, 2, 5, 5, 8, 1, 1);
  grammar->setState(8, 1, 1, 9, 1);
  grammar->setState(9, 1, 4, 18, 1);
  grammar->setState(10, 1, 0, 11, 1);
  grammar->setState(11, 2, 4, 2, 12, 14, 1, 1);
  grammar->setState(12, 2, 3, 6, 12, 13, 1, 1);
  grammar->setState(13, 2, 6, 3, 14, 16, 1, 1);
  grammar->setState(14, 2, 4, 5, 14, 15, 1, 1);
  grammar->setState(15, 2, 2, 5, 13, 16, 1, 1);
  grammar->setState(16, 1, 1, 17, 1);
  grammar->setState(17, 1, 2, 18, 1);
  grammar->setState(18, 1, 1, 19, 1);
  grammar->setState(19, 0);
  grammar->setTerminated(19);
}

void Rtrl::setFunctions(){
  vector<activationFunctionType> functions(nbreTotalNeuron, function);
  network->setFunctions(functions);
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

double Rtrl::score(double* probabilities, double* normalizedOutput){
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
