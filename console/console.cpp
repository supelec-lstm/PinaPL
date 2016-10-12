//
//  console.cpp
//  PinaPL
//

#include "console.hpp"

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

NeuronNetwork Console::networkBuilderInteractive() {
    // calls NeuronNetworkBuilder methods interactively

    bool networkBuilderMode = true;
    string rawInput;
    status = "network builder";

    NeuronNetworkBuilder builder = NeuronNetworkBuilder();

    while (networkBuilderMode == true) {
        cout << status << ">> ";
		getline(cin, rawInput);

        vector<string> parsedInput = parseCommandString(rawInput);
        if (parsedInput[0] == "exit" || parsedInput[0] == "quit") {
            status = "";
            break;
        }

        networkBuilderCommandExecution(parsedInput, &builder);
    }

    cout << "Generated network named: " << builder.getName() << endl;
    return(builder.generateComputationalNetwork());
}

bool Console::argumentCountCheck(int argumentCount, int desiredCount) {
    if (argumentCount != desiredCount) {
        cout << "Error: wrong argument count" << endl;
        return false;
    } else {
        return true;
    }

}

void Console::commandExecution(vector<string> parsedInput) {
    // executes a command

    int argumentCount = parsedInput.size();

    map<string,Command> commands = {
        {"list-saved-networks", LISTSAVEDNETWORKS},
        {"list-scripts", LISTSCRIPTS},
        {"list-idxs", LISTIDXS},
        {"script", SCRIPT},
        {"network-builder",NETWORKBUILDER}
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
            if (argumentCountCheck(argumentCount, 2)) {
                scriptExecution(parsedInput[1]);
            }
            break;
        case NETWORKBUILDER:
            networkBuilderInteractive();
            break;
        default:
            cout << "Error: unrecognized command" << endl;
            break;
    }
}

void Console::networkBuilderCommandExecution(vector<string> parsedInput, NeuronNetworkBuilder *builder) {
    // executes a command

    int argumentCount = parsedInput.size();

    map<string,NetworkBuilderCommand> commands = {
        {"set-name", SETNAME},
        {"set-date", SETDATE},
        {"set-default-composition-function", SETDEFCOMPFUNC},
        {"set-default-activation-function", SETDEFACTFUNC},
        {"add-neurons", ADDNEURONS},
        {"set-property", SETPROPERTY},
        {"add-one2many-connection", ADDONE2MANY},
        {"add-many2one-connection", ADDMANY2ONE}
    };

	switch(commands[parsedInput[0]])
    {
        case SETNAME:
            if(argumentCountCheck(argumentCount, 2)) {
                builder->setName(parsedInput[1]);
            }
            break;
        case SETDATE:
            if(argumentCountCheck(argumentCount, 2)) {
                builder->setDate(parsedInput[1]);
            }
            break;
        case SETDEFCOMPFUNC:
            if(argumentCountCheck(argumentCount, 2)) {
                if(parsedInput[1] == "sum") {
                    builder->setDefaultCompositionFunction(compositionFunctionSum);
                }
            }
            break;
        case SETDEFACTFUNC:
            if(argumentCountCheck(argumentCount, 2)) {
                if(parsedInput[1] == "sigmoid") {
                    builder->setDefaultActivationFunction(activationFunctionSigmoid);
                }
            }
            break;
        case ADDNEURONS:
             if(argumentCountCheck(argumentCount, 2)) {
                builder->addNeurons(stoi(parsedInput[1]));
            }
            break;
        case SETPROPERTY:
            break;
        default:
            cout << "Error: unrecognized command" << endl;
            break;
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
