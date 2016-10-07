//
//  console.hpp
//  PinaPL
//

#ifndef DEF_CONSOLE
#define DEF_CONSOLE

#include<vector>

enum Command {
    LISTSAVEDNETWORKS = 1,
    LISTSCRIPTS = 2,
    LISTIDXS = 3,
    SCRIPT = 4
};

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
