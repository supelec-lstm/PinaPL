//
//  main.cpp
//  PinaPL
//

#include <iostream>
#include <map>
#include <vector>
#include <typeinfo>
#include <random>
#include <string.h>
#include <time.h>

#include "idxParser/idxParser.hpp"

#include "test/mnist.hpp"
#include "test/xor.hpp"

#include "log.hpp"

int tab_log = 0;

using namespace std;

int main(int argc, const char *argv[]) {
    srand(time(NULL));
    /*vector<string> stringedArgv = vector<string>(unsigned(argc));
    bool log = isArgumentPresent("--log", stringedArgv);

    for (int i = 0; i < argc; i++) {
        unsigned long length = strlen(argv[i]);
        string argument;
        argument.assign(argv[i], length);
        stringedArgv[unsigned(i)] = argument;
    }
    if (isArgumentPresent("--log", &stringedArgv)) {
    }

    if (isArgumentPresent("--interactive", &stringedArgv)) {
        // if there is a single argument and it is "--interactive"
        Console console;
        console.greeting();
        console.interactive();
        console.goodbye();
    } else {
    }*/

    //testMNIST();
    Mnist test;
    test.learn();
    test.test();


    return 0;
}
