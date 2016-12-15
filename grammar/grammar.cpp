#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "grammar.hpp"

using namespace std;

Grammar::Grammar(int nbState, int** nextStateData, int* nextSizeData, int** weightData, int** nextLetterData, char* lettersData){
	stateCount = nbState;

	nextState = nextStateData;
	weight = weightData;
	nextLetter = nextLetterData;

	letters = lettersData;

	nextSize = nextSizeData;
}

Grammar::~Grammar(){
	delete(nextState);
	delete(weight);
	delete(letters);
	delete(nextSize);
}

int Grammar::random(int* proba, int n){
    int s = 0;
    for(int i = 0; i < n; i++){
        s += proba[i];
    }
    int a = rand()%s - proba[0];
    int j = 0;
    while(a >= 0){
        j ++;
        a -= proba[j];
    }
    return j;
}

void Grammar::reset(){
	state = 0;
}

int Grammar::newLetter(){
    int i = state;
    int j = random(weight[i], nextSize[i]);
    state = nextState[i][j];
    return nextLetter[i][j];
}

vector<int> Grammar::word(){
    vector<int> res;
    reset();
    while(state != stateCount - 1){
        res.push_back(newLetter());
    }
    return res;
}

string Grammar::stringWord(){
	vector<int> word = this->word();
    ostringstream convert;
    for(int i = 0; i < word.size(); i++){
        convert << letters[word[i]];
    }
    return convert.str();
}

void Grammar::printWord(){
	vector<int> word = this->word();
    for(int i = 0; i < word.size(); i++){
        cout << letters[word[i]];
    }
}

int* Grammar::inputWord(){
	vector<int> word = this->word();
	int n = word.size();
	int* res = new int[n];
	for(int i = 0; i < n; i++){
		res[i] = word[i];
	}
	return res;
}

int* Grammar::inputWord(vector<int> word){
	int n = word.size();
	int* res = new int[n];
	for(int i = 0; i < n; i++){
		res[i] = word[i];
	}
	return res;
}

Grammar createReber(){
    int nbState = 8;
    int nbLetter = 7;

    char* letters = new char[nbLetter];
    letters[0] = 'B';
    letters[1] = 'E';
    letters[2] = 'P';
    letters[3] = 'S';
    letters[4] = 'T';
    letters[5] = 'V';
    letters[6] = 'X';

    int** nextState = new int*[nbState];
    nextState[0] = new int[1];
    nextState[0][0] = 1;
    nextState[1] = new int[2];
    nextState[1][0] = 2;
    nextState[1][1] = 4;
    nextState[2] = new int[2];
    nextState[2][0] = 2;
    nextState[2][1] = 3;
    nextState[3] = new int[2];
    nextState[3][0] = 4;
    nextState[3][1] = 6;
    nextState[4] = new int[2];
    nextState[4][0] = 4;
    nextState[4][1] = 5;
    nextState[5] = new int[2];
    nextState[5][0] = 3;
    nextState[5][1] = 6;
    nextState[6] = new int[1];
    nextState[6][0] = 7;
    nextState[7] = new int[0];

    int** nextLetter = new int*[nbState];
    nextLetter[0] = new int[1];
    nextLetter[0][0] = 0;
    nextLetter[1] = new int[2];
    nextLetter[1][0] = 4;
    nextLetter[1][1] = 2;
    nextLetter[2] = new int[2];
    nextLetter[2][0] = 3;
    nextLetter[2][1] = 6;
    nextLetter[3] = new int[2];
    nextLetter[3][0] = 6;
    nextLetter[3][1] = 3;
    nextLetter[4] = new int[2];
    nextLetter[4][0] = 4;
    nextLetter[4][1] = 5;
    nextLetter[5] = new int[2];
    nextLetter[5][0] = 2;
    nextLetter[5][1] = 5;
    nextLetter[6] = new int[1];
    nextLetter[6][0] = 1;
    nextLetter[7] = new int[0];

    int** weight = new int*[nbState];
    weight[0] = new int[1];
    weight[0][0] = 1;
    weight[1] = new int[2];
    weight[1][0] = 1;
    weight[1][1] = 1;
    weight[2] = new int[2];
    weight[2][0] = 1;
    weight[2][1] = 1;
    weight[3] = new int[2];
    weight[3][0] = 1;
    weight[3][1] = 1;
    weight[4] = new int[2];
    weight[4][0] = 1;
    weight[4][1] = 1;
    weight[5] = new int[2];
    weight[5][0] = 1;
    weight[5][1] = 1;
    weight[6] = new int[1];
    weight[6][0] = 1;
    weight[7] = new int[0];

    int* nextSize = new int[nbState];
    nextSize[0] = 1;
    nextSize[1] = 2;
    nextSize[2] = 2;
    nextSize[3] = 2;
    nextSize[4] = 2;
    nextSize[5] = 2;
    nextSize[6] = 1;
    nextSize[7] = 0;

    Grammar res(nbState, nextState, nextSize, weight, nextLetter, letters);
    return res;
}

