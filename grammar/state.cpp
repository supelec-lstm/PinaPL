#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "state.hpp"

#define NLOG
#define FILE_NAME "state.cpp\t\t"
#include "../log.hpp"

using namespace std;

State::State(int id, int nbState, int* letters, State** states, int* weight){
    PRINT_BEGIN_FUNCTION("Création de l'état")

    this->id = id;
    this->terminal = false;
    this->setSize(nbState);
    this->setData(letters, states, weight);

    PRINT_END_FUNCTION()
}

State::State(int id, int nbState){
    PRINT_BEGIN_FUNCTION("Création de l'état")

    this->id = id;
    this->terminal = false;
    this->setSize(nbState);

    PRINT_END_FUNCTION()
}

State::State(int id){
    PRINT_BEGIN_FUNCTION("Création de l'état")

    this->id = id;
    this->terminal = false;

    PRINT_END_FUNCTION()
}

State::~State(){
    PRINT_BEGIN_FUNCTION("Destruction de l'état")
	delete(weight);
	delete(letters);
	delete(states);
    PRINT_END_FUNCTION()
}

int State::random(){
    PRINT_BEGIN_FUNCTION("Choix d'une direction aléatoire dans la grammaire")
    int a = rand()%weightTotal - this->weight[0];
    int j = 0;
    while(a >= 0){
        j ++;
        a -= this->weight[j];
    }
    PRINT_END_FUNCTION()
    return j;
}

void State::setTerminal(){
    PRINT_BEGIN_FUNCTION("Set de l'état en terminal")
    this->terminal = true;
    PRINT_END_FUNCTION()
}

void State::setSize(int nbState){
    PRINT_BEGIN_FUNCTION("Set du nombre d'état suivant")
    this->nbState = nbState;

    this->letters = new int[nbState];
    this->states = new State*[nbState];
    this->weight = new int[nbState];
    PRINT_END_FUNCTION()
}

void State::setData(int* letters, State** states, int* weight){
    PRINT_BEGIN_FUNCTION("Set des données des états suivants")
    int s = 0;
    for(int i = 0; i < this->nbState; i++){
        this->letters[i] = letters[i];
        this->states[i] = states[i];
        this->weight[i] = weight[i];
        s += weight[i];
    }

    this->weightTotal = s;
    PRINT_END_FUNCTION()
}

int State::getSize(){
    return this->nbState;
}

int State::getId(){
    return this->id;
}

int* State::getWeight(){
    return this->weight;
}

State** State::getStates(){
    return this->states;
}

int* State::getLetters(){
    return this->letters;
}


int State::newLetter(State* &state){
    PRINT_BEGIN_FUNCTION("Création d'une nouvelle lettre")
    if(!terminal){
        int j = random();
        state = this->states[j];
        PRINT_END_FUNCTION()
        return this->letters[j];
    }
    else{
        PRINT_END_FUNCTION()
        return -1;
    }
    
}

bool State::isTerminal(){
    return this->terminal;
}