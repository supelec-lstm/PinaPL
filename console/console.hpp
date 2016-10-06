//
//  console.hpp
//  PinaPL
//

#ifndef DEF_CONSOLE
#define DEF_CONSOLE

#include<vector>

enum Command {DEFAULT, LISTSAVEDNETWORKS, LISTSCRIPTS, LISTIDXS, SCRIPT};

class Console {

private:
    std::string status;

    std::vector<std::string> parseCommandString(std::string rawInput);
    bool listSavedNetworks();
    bool listScripts();
    bool listIdxs();
    void scriptExecution(std::string scriptPath);
    void commandExecution(std::vector<std::string> input);

public:
    Console();
    void greeting();
    void goodbye();
    void interactive();
};

#endif // DEF_CONSOLE
