//
//  console.hpp
//  PinaPL
//

#ifndef DEF_CONSOLE
#define DEF_CONSOLE

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
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
    LISTSAVEDNETWORKS = 1,
    LISTSCRIPTS = 2,
    LISTIDXS = 3,
    SCRIPT = 4,
    NETWORKBUILDER = 5
};

enum NetworkBuilderCommand {
    SETNAME = 1,
    SETDATE = 2,
    SETDEFCOMPFUNC = 3,
    SETDEFACTFUNC = 4,
    ADDNEURON = 5,
    SETPROPERTY = 6,
    ADDCONNECTION = 7,
    BUILD = 8
};

class Console {

private:
    std::string status;

    bool listSavedNetworks();
    bool listScripts();
    bool listIdxs();
    void scriptExecution(std::string scriptPath);
    bool argumentCountCheck(int argumentCount, int desiredCount);
    void commandExecution(std::vector<std::string> parsedInput);
    void networkBuilderCommandExecution(std::vector<std::string> parsedInput, NeuronNetworkBuilder *builder);
    NeuronNetwork networkBuilderInteractive();
    std::vector<std::string> splitString(const std::string &input, std::string delim);

public:
    Console();
    void greeting();
    void goodbye();
    void interactive();
};

#endif // DEF_CONSOLE
