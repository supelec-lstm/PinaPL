#ifndef DEF_GRAMMAR
#define DEF_GRAMMAR

class Grammar{

	int stateCount;

	int state;

	int** nextState;
	int** weight;
	char** nextLetter;

	int* random(int* proba);

public:

	Grammar(int nbState, int** nextStateData, int** weight, char** nextLetter);
	~Grammar();
	void reset();
	char nextLetter();
	std::string word();


};

#endif //DEF_GRAMMAR
