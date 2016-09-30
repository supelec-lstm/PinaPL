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

vector<string> Console::parseInput(string argRawInput) {
    string sentence = argRawInput;
    istringstream iss(sentence);
    vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};

    return tokens;
}

void Console::interactive() {
    // interactive method

	bool interactiveEnabled = true;

    string userRawInput = "";

	while (interactiveEnabled) {

		cout << ">> ";
		getline(cin, userRawInput);

        vector<string> parsedInput = parseInput(userRawInput);

        if (parsedInput[0] == "exit" || parsedInput[0] == "quit") {
            goodbye();
            return;
        }
        commandExecution(parsedInput);
    }
    return;
}

void Console::scriptExecution(string scriptPath) {

    string path = scriptPath;
    ifstream input(path);
    for (string line; getline(input, line);)
    {
        vector<string> parsedLine = parseInput(line);
        commandExecution(parsedLine);
    }
    return;
}


void Console::commandExecution(vector<string> input) {


    map<string,Command> commands = {
        {"list", LIST},
        {"script", SCRIPT}
    };

	switch(commands[input[0]])
    {
        case LIST:
    	    listFolderContent();
      	    break;
        case SCRIPT:
            scriptExecution(input[1]);
            break;
        default:
            cout << "Error : invalid command" << endl;
            break;
    }
}
