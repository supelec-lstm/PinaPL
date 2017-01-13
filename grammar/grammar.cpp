#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdarg.h>

#include "grammar.hpp"
#include "state.hpp"

#define NLOG
#define FILE_NAME "grammar.cpp\t\t"
#include "../log.hpp"

using namespace std;

Grammar::Grammar(int stateCount, int letterCount, char* letters){
    PRINT_BEGIN_FUNCTION("Création de la grammaire")
	this->stateCount = stateCount;
    this->states = new State*[stateCount];

    for(int i = 0; i < stateCount; i++){
        this->states[i] = new State(i);
    }

    this->initState = this->states[0];
    this->actualState = this->states[0];

    this->letterCount = letterCount;
    this->letters = new char[letterCount];
    for(int i = 0; i < letterCount; i++){
        this->letters[i] = letters[i];
    }
    PRINT_END_FUNCTION()
}

Grammar::~Grammar(){
    PRINT_BEGIN_FUNCTION("Suppression de la grammaire")
	delete(initState);
	delete(actualState);
	delete(states);
	delete(letters);
    PRINT_END_FUNCTION()
}


void Grammar::setState(int j, ...){
    PRINT_BEGIN_FUNCTION("Définition des états de la grammaire")
    va_list ap;
    va_start(ap, j);

    int n = va_arg(ap, int);

    int* letters = new int[n];
    State** states = new State*[n];
    int* weight = new int[n];

    for(int i = 0; i < n; i++) {
        int a = va_arg(ap, int);
        letters[i] = a;
    }

    for(int i = 0; i < n; i++) {
        int a = va_arg(ap, int);
        states[i] = this->states[a];
    }

    for(int i = 0; i < n; i++) {
        int a = va_arg(ap, int);
        weight[i] = a;
    }

    va_end(ap);

    this->states[j]->setSize(n);
    this->states[j]->setData(letters, states, weight);
    PRINT_END_FUNCTION()
}

void Grammar::setTerminated(int j){
    PRINT_BEGIN_FUNCTION("Définition des états de sorties")
    this->states[j]->setTerminal();
    PRINT_END_FUNCTION()
}

void Grammar::reset(){
    PRINT_BEGIN_FUNCTION("Reset")
	actualState = initState;
    word.clear();
    PRINT_END_FUNCTION()
}

int Grammar::newLetter(){
    PRINT_BEGIN_FUNCTION("Nouvelle lettre")
    int c = this->actualState->newLetter(actualState);
    this->word.push_back(c);
    PRINT_END_FUNCTION()
    return c;
}

void Grammar::createWord(){
    PRINT_BEGIN_FUNCTION("Création d'un mot")
    reset();
    while(!actualState->isTerminal()){
        int c = this->actualState->newLetter(actualState);
        this->word.push_back(c);
    }
    PRINT_END_FUNCTION()
}

string Grammar::stringWord(){
    PRINT_BEGIN_FUNCTION("Recupération du mot sous forme de string")
    ostringstream convert;
    for(int i = 0; i < this->word.size(); i++){
        convert << this->letters[this->word[i]];
    }
    PRINT_END_FUNCTION()
    return convert.str();
}

void Grammar::printWord(){
    PRINT_BEGIN_FUNCTION("Affichage du mot")
    for(int i = 0; i < this->word.size(); i++){
        cout << this->letters[this->word[i]];
    }
    PRINT_END_FUNCTION()
}

int* Grammar::inputWord(){
    PRINT_BEGIN_FUNCTION("Récupération du mot sous forme de tableau")
	int n = this->word.size();
	int* res = new int[n];
	for(int i = 0; i < n; i++){
		res[i] = this->word[i];
	}
    PRINT_END_FUNCTION()
	return res;
}

int Grammar::inputSize(){
    PRINT_BEGIN_FUNCTION("Récupération de la taille du mot")
    PRINT_END_FUNCTION()
    return this->word.size();
}

int Grammar::getState(){
    PRINT_BEGIN_FUNCTION("Récupération de l'état actuelle du mot")
    PRINT_END_FUNCTION()
    return actualState->getId();
}

double* Grammar::getProba(){
    PRINT_BEGIN_FUNCTION("Récupération de la répartition des probabilités de l'état actuelle")
    int n = this->actualState->getSize();
    int* weight = this->actualState->getWeight();
    int* letters = this->actualState->getLetters();

    double* proba = new double[stateCount];
    for(int i = 0; i < stateCount; i++){
        proba[i] = 0;
    }

    double s = 0;
    for(int i = 0; i < n; i++){
        s += weight[i];
    }
    for(int i = 0; i < n; i++){
        proba[letters[i]] = weight[i]/s;
    }

    PRINT_END_FUNCTION()
    return proba;
}

bool Grammar::isTerminal(){
    PRINT_BEGIN_FUNCTION("Test de terminaison")
    PRINT_END_FUNCTION()
    return actualState->isTerminal();
}