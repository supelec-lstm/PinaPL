#ifndef DEF_GRAMMAR
#define DEF_GRAMMAR

#include <vector>
#include <string>

class Grammar{

	int stateCount;

	int state;
	char* letters;

	int** nextState;
	int** weight;
	int** nextLetter;
	int* nextSize;

	int random(int* proba, int n);

public:

	Grammar(int nbState, int** nextStateData, int* nextSizeData, int** weightData, int** nextLetterData, char* lettersData);
	~Grammar();
	void reset();
	int newLetter();
	std::vector<int> word();

	std::string stringWord(std::vector<int> word);
    void printWord(std::vector<int> word);
};

Grammar createReber();

#endif //DEF_GRAMMAR
