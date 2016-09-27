//
//  console.hpp
//  PinaPL
//

#ifndef DEF_CLI
#define DEF_CLI

enum Command {DEFAULT, EXIT, LIST};

class Console {
private:
public:
    Console();

    void greeting();
    void goodbye();

    void interactive();
    bool listFolderContent();
};

#endif // DEF_CLI
