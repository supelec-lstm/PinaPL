#include <iostream>
#include <map>

#include "console.hpp"

using namespace std;

Console::Console()
{

}

void Console::greeting() {
	// greeting
	cout << "-----PinaPL Neuronal Network Simulation-----" << endl;
	cout << "--------------------------------------------" << endl;
	return;
}

void Console::goodbye() {
	// goodbye
	cout << "--------------------------------------------" << endl;
	return;
}

void Console::interactive() {

	bool interactiveEnabled = true;
	string userInput = "";

	map<string,Command> commands = {
		{"exit", EXIT},
		{"quit", EXIT},
		{"test", TEST}
	};

	while (interactiveEnabled) {
		// Prompt
		cout << ">>";
		cin >> userInput;
		cout << endl;

		// Interpretation
		switch(commands[userInput])
        {
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
