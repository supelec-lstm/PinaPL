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

#include "../simpleNeuron/neuron.hpp"
#include "../neuronNetwork/neuronNetwork.hpp"
#include "../neuronNetwork/neuronNetworkBuilder.hpp"
#include "console.hpp"
#include "../idxParser/idxParser.hpp"

using namespace std;

Console::Console() {
// Console constructor
}

void Console::greeting() {
	// greeting message
	cout << "-----PinaPL Neuronal Network Simulation-----" << endl;
	cout << "--------------------------------------------" << endl;
	return;
}

void Console::goodbye() {
	// goodbye message
	cout << "--------------------------------------------" << endl;
	return;
}

bool Console::listSavedNetworks() {
    // lists content of folder ./savedNetworks

    DIR *directory;
    if ((directory = opendir ("./savedNetworks")) != NULL) {
        struct dirent *ent;
        while ((ent = readdir(directory)) != NULL) {
            cout << ent->d_name << endl;
        }
        closedir(directory);
        return true;
    } else {
        cout << "Error: could not open directory ./savedNetworks" << endl;
        return false;
    }
}

bool Console::listScripts() {
    // lists content of folder ./scripts

    DIR *directory;
    if ((directory = opendir ("./scripts")) != NULL) {
        struct dirent *ent;
        while ((ent = readdir(directory)) != NULL) {
            cout << ent->d_name << endl;
        }
        closedir(directory);
        return true;
    } else {
        cout << "Error: could not open directory ./scripts" << endl;
        return false;
    }
}

bool Console::listIdxs() {
    // lists content of folder ./idxs

    DIR *directory;
    if ((directory = opendir ("./idxs")) != NULL) {
        struct dirent *ent;
        while ((ent = readdir(directory)) != NULL) {
            cout << ent->d_name << endl;
        }
        closedir(directory);
        return true;
    } else {
        cout << "Error: could not open directory ./idxs" << endl;
        return false;
    }
}

vector<string> Console::parseCommandString(string rawInput) {
    // parses a command string, outputs a vector of arguments

    istringstream iss(rawInput);
    vector<string> commands{istream_iterator<string>{iss}, istream_iterator<string>{}};
    return commands;
}

void Console::scriptExecution(string scriptPath) {
    // executes a script

    string scriptRoot = "scripts/";
    string path = scriptRoot.append(scriptPath);
    ifstream input(path);
    for (string line; getline(input, line);)
    {
        vector<string> parsedLine = parseCommandString(line);
        commandExecution(parsedLine);
    }
    return;
}


void Console::commandExecution(vector<string> parsedInput) {
    // executes a command

    map<string,Command> commands = {
        {"list-saved-networks", LISTSAVEDNETWORKS},
        {"list-scripts", LISTSCRIPTS},
        {"list-idxs", LISTIDXS},
        {"script", SCRIPT}
    };

	switch(commands[parsedInput[0]])
    {
        case LISTSAVEDNETWORKS:
    	    listSavedNetworks();
      	    break;
      	case LISTSCRIPTS:
            listScripts();
      	    break;
      	case LISTIDXS:
      	    listIdxs();
      	    break;
        case SCRIPT:
            scriptExecution(parsedInput[1]);
            break;
//        default:
//            cout << "Error: unrecognized command" << endl;
//            break;
    }
}

void Console::interactive() {
    // interactive method

	bool interactiveEnabled = true;
    string rawInput;

	while (interactiveEnabled) {
		cout << status << ">> ";
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
