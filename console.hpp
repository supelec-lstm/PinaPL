#ifndef DEF_CLI
#define DEF_CLI

enum Command {DEFAULT, EXIT, TEST};

class Console {
    private:
    public:
    Console();

    void greeting();
    void interactive();
    void goodbye();
};

#endif
