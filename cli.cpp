//
//  cli.cpp
//  PinaPL
//

#include <iostream>
#include <map>

#include "cli.hpp"


using namespace std;

Cli::Cli() {

}

void Cli::greeting() {
	// greeting
	cout << "-----PinaPL Neuronal Network Simulation-----" << endl;
	cout << "--------------------------------------------" << endl;
	return;
}

void Cli::goodbye() {
	// goodbye
	cout << "--------------------------------------------" << endl;
	return;
}

void Cli::interactive() {

	bool interactiveEnabled = true;
	string userInput = "";

	map<string,Command> commands = {
		{"exit", EXIT},
		{"quit", EXIT},
		{"test", TEST}
	};

	while (interactiveEnabled) {
		// Prompt
		cout << ">> ";
		cin >> userInput;

		// Interpretation
		switch(commands[userInput]) {
            case TEST:
            	cout << "test" << endl;
            	break;
   			case EXIT:
	           	interactiveEnabled = false;
                break;
            default:
           	    cout << "command not recognized" << endl;
           	    break;
        }
    }
    return;
}
