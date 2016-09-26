//
//  main.cpp
//  PINAPL
//

#include <iostream>
#include <map>
#include "simpleNeuron/neuron.hpp"
#include "console/console.hpp"

using namespace std;

int main(int argc, const char * argv[]) {

// console instantiation
Console console;
// greeting
console.greeting();
// interactive
console.interactive();
// goodbye
console.goodbye();

return 0;
}
