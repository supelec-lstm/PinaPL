#ifndef DEF_STATE
#define DEF_STATE

#include <vector>
#include <string>

class State{

    int id;
    int nbState;

    int* letters;
    State** states;
    int* weight;
    int weightTotal;

    bool terminal;

    int random();

public:

    State(int id, int nbState, int* letters, State** states, int* weight);
    State(int id, int nbState);
    State(int id);
    ~State();

    int newLetter(State* &state);

    void setTerminal();
    void setSize(int nbState);
    void setData(int* letters, State** states, int* weight);

    int getSize();
    int getId();
    int* getWeight();
    State** getStates();
    int* getLetters();
    bool isTerminal();
};

#endif //DEF_GRAMMAR
