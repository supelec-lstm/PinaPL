//
//  console.cpp
//  PinaPL
//

#include <iostream>
#include <map>
#include <dirent.h>

#include "console.hpp"


using namespace std;

Console::Console() {

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

bool Console::listFolderContent() {
    DIR *directory;
    struct dirent *ent;
    if ((directory = opendir ("./savedNetworks")) != NULL) {
        // print all the files and directories within ./
        while ((ent = readdir(directory)) != NULL) {
            cout << ent->d_name << endl;
        }
        closedir(directory);
        return true;
    } else {
        // could not open directory
        return false;
    }
}

void Console::interactive() {
	bool interactiveEnabled = true;
	string userInput = "";

	map<string,Command> commands = {
		{"exit", EXIT},
		{"quit", EXIT},
		{"list", LIST}
	};

	while (interactiveEnabled) {
		// Prompt
		cout << ">> ";
		cin >> userInput;

		// Interpretation
		switch(commands[userInput])
        {
            case LIST:
            	listFolderContent();
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
