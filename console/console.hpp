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
    NETWORKBUILDERSCRIPT = 5,
    NETWORKBUILDER = 6
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
    std::string status;

public:
    Console();
    void greeting();
    void goodbye();
    void interactive();

private:
    bool listSavedNetworks();
    bool listScripts();
    bool listIdxs();
    void scriptExecution(std::string scriptPath);
    NeuronNetwork networkBuilderScriptExecution(std::string scriptPath);
    bool argumentCountCheck(unsigned long argumentCount, unsigned long desiredCount, bool errorReport);
    void commandExecution(std::vector<std::string> parsedInput);
    void networkBuilderCommandExecution(std::vector<std::string> parsedInput, NeuronNetworkBuilder *builder);
    NeuronNetwork networkBuilderInteractive();
    std::vector<std::string> splitString(const std::string &input, std::string delim);
    std::vector<int> splitStringToInt(const std::string &input, std::string delim);
};

#endif // DEF_CONSOLE
