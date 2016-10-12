//
//  console.hpp
//  PinaPL
//

#ifndef DEF_CONSOLE
#define DEF_CONSOLE

#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <dirent.h>
#include <algorithm>
#include <iterator>
#include <sstream>

#include "../simpleNeuron/neuron.hpp"
#include "../neuronNetwork/neuronNetwork.hpp"
#include "../neuronNetwork/neuronNetworkBuilder.hpp"
#include "../idxParser/idxParser.hpp"

enum Command {
    DEFAULT,
    LISTSAVEDNETWORKS,
    LISTSCRIPTS,
    LISTIDXS,
    SCRIPT,
    NETWORKBUILDER
};

enum NetworkBuilderCommand {
    DEFAULTNB,
    SETNAME,
    SETDATE,
    SETDEFCOMPFUNC,
    SETDEFACTFUNC,
    ADDNEURONS,
    SETPROPERTY,
    ADDONE2MANY,
    ADDMANY2ONE
};

class Console {

private:
    std::string status;

    std::vector<std::string> parseCommandString(std::string rawInput);
    bool listSavedNetworks();
    bool listScripts();
    bool listIdxs();
    void scriptExecution(std::string scriptPath);
    bool argumentCountCheck(int argumentCount, int desiredCount);
    void commandExecution(std::vector<std::string> parsedInput);
    void networkBuilderCommandExecution(std::vector<std::string> parsedInput, NeuronNetworkBuilder *builder);
    NeuronNetwork networkBuilderInteractive();


public:
    Console();
    void greeting();
    void goodbye();
    void interactive();
};

#endif // DEF_CONSOLE
