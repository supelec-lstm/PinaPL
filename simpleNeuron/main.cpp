//
//  main.cpp
//  PinaPL
//

#include <iostream>
#include <map>

#include "neuron.hpp"
#include "cli.hpp"


using namespace std;

int main(int argc, const char * argv[]) {
// CLI instantiation
    Cli cli;
// greeting
    cli.greeting();
// interactive
    cli.interactive();
// goodbye
    cli.goodbye();
    
    return 0;
}
