#include <string>

#include "grammar.hpp"

using namespace std;

Grammar::Grammar(int nbState, int** nextStateData, int** weight, char** nextLetter){
	stateCount = nbState;

	nextState = nextStateData;
	weight = weightData;
	nextLetter = nextLetterData;
}

Grammar::~Grammar(){
	delete(nextStateData);
	delete(weightData);
}

char Grammar::random(int* proba){

}

void Grammar::reset(){
	state = 0;
}

char Grammar::nextLetter(){

}

string Grammar::word(){
	
}