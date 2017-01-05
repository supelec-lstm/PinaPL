#ifndef DEF_GRAMMAR
#define DEF_GRAMMAR

#include <vector>
#include <string>

#include "state.hpp"

class Grammar{

    int stateCount;
    int letterCount;

    State** states;
    State* actualState;
    State* initState;

    char* letters;

    std::vector<int> word;

public:

    Grammar(int stateCount, int letterCount, char* letters);
    ~Grammar();
    void setState(int j, ...);
    void setTerminated(int j);
    void reset();
    int newLetter();

    void createWord();
    std::string stringWord();
    void printWord();
    int* inputWord();
    int inputSize();

    int getState();
    double* getProba();
    bool isTerminal();
};

#endif //DEF_GRAMMAR
