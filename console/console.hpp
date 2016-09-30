//
//  console.hpp
//  PinaPL
//

#ifndef DEF_CLI
#define DEF_CLI

#include<vector>

enum Command {DEFAULT, LIST, SCRIPT};

class Console {
private:
public:
    Console();

    void greeting();
    void goodbye();
    std::vector<std::string> parseInput(std::string rawInput);
    bool listFolderContent();
    void scriptExecution(std::string scriptPath);
    void commandExecution(std::vector<std::string> input);
    void interactive();

};

#endif // DEF_CLI
