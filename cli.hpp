#ifndef DEF_CLI
#define DEF_CLI

enum Command {DEFAULT, EXIT, TEST};

class Cli {
    private:
    public:
    Cli();

    void greeting();
    void interactive();
    void goodbye();
};

#endif
