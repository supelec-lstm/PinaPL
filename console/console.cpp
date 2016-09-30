//
//  console.cpp
//  PinaPL
//

#include <iostream>
#include <fstream>
#include <map>
#include <dirent.h>
#include <algorithm>
#include <iterator>
#include <sstream>

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
    // lists content of folder ./savedNetworks

    DIR *directory;
    struct dirent *ent;
    if ((directory = opendir ("./savedNetworks")) != NULL) {
        // print all the files and directories within ./savedNetworks
        while ((ent = readdir(directory)) != NULL) {
            cout << ent->d_name << endl;
        }
        closedir(directory);
        return true;
    } else {
        // could not open directory
        cout << "Error : could not open directory ./savedNetworks" << endl;
        return false;
    }
}

vector<string> Console::parseCommandString(string rawInput) {
    // parses a command string, outputs a vector of commands/arguments

    istringstream iss(rawInput);
    vector<string> commands{istream_iterator<string>{iss}, istream_iterator<string>{}};

    return commands;
}

void Console::scriptExecution(string scriptPath) {

    string path = scriptPath;
    ifstream input(path);
    for (string line; getline(input, line);)
    {
        vector<string> parsedLine = parseCommandString(line);
        commandExecution(parsedLine);
    }
    return;
}


void Console::commandExecution(vector<string> parsedInput) {

    map<string,Command> commands = {
        {"list", LIST},
        {"script", SCRIPT}
    };

	switch(commands[parsedInput[0]])
    {
        case LIST:
    	    listFolderContent();
      	    break;
        case SCRIPT:
            scriptExecution(parsedInput[1]);
            break;
        default:
            cout << "Error : invalid command" << endl;
            break;
    }
}

void Console::interactive() {
    // interactive method

	bool interactiveEnabled = true;
    string rawInput;

	while (interactiveEnabled) {
		cout << ">> ";
		getline(cin, rawInput);

        vector<string> parsedInput = parseCommandString(rawInput);

        if (parsedInput[0] == "exit" || parsedInput[0] == "quit") {
            goodbye();
            return;
        }

        commandExecution(parsedInput);
    }
    return;
}
