//
//  console.cpp
//  PinaPL
//

#include "console.hpp"

using namespace std;

Console::Console() {
// Console constructor
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Text output methods

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
        cout << "./savedNetworks/ contents: " << endl;
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
        cout << "./scripts/ contents: " << endl;
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
        cout << "./idxs/ contents: " << endl;
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

///////////////////////////////////////////////////////////////////////////////////////////////////
// Command parsing methods

bool Console::argumentCountCheck(unsigned long argumentCount, unsigned long desiredCount, bool errorReport) {
    if (argumentCount != desiredCount) {
        if (errorReport) {
            if (desiredCount == 1) {
                cout << "Error: wrong argument count, none expected" << endl;
            } else {
                cout << "Error: wrong argument count, " << desiredCount - 1 << " expected" << endl;
            }
        }
        return false;
    } else {
        return true;
    }
}

vector<string> Console::splitString(const string &input, string delim) {
    char delimChar = delim[0];
    vector<string> elements;
    stringstream ss;
    ss.str(input);
    string item;
    while (getline(ss, item, delimChar)) {
        elements.push_back(item);
    }
    return elements;
}

vector<int> Console::splitStringToInt(const string &input, string delim) {
    char delimChar = delim[0];
    vector<int> elements;
    stringstream ss;
    ss.str(input);
    string item;
    while (getline(ss, item, delimChar)) {
        elements.push_back(stoi(item));
    }
    return elements;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Execution methods

void Console::scriptExecution(string scriptPath) {
    // executes a script

    string scriptRoot = "scripts/";
    string path = scriptRoot.append(scriptPath);
    ifstream input(path);
    for (string line; getline(input, line);)
    {
        vector<string> parsedLine = splitString(line, " ");
        commandExecution(parsedLine);
    }
    return;
}

NeuronNetwork Console::networkBuilderScriptExecution(string scriptPath) {
    // executes a network-builder mode script
    NeuronNetworkBuilder builder;
    string scriptRoot = "scripts/";
    string path = scriptRoot.append(scriptPath);
    ifstream input(path);
    for (string line; getline(input, line);)
    {
        vector<string> parsedLine = splitString(line, " ");
        networkBuilderCommandExecution(parsedLine, &builder);
    }
    return(builder.generateComputationalNetwork());
}

void Console::networkBuilderCommandExecution(vector<string> parsedInput, NeuronNetworkBuilder *builder) {
    // executes a command

    unsigned long argumentCount = parsedInput.size();

    map<string,NetworkBuilderCommand> commands = {
        {"set-name", SETNAME},
        {"set-date", SETDATE},
        {"set-default-composition-function", SETDEFCOMPFUNC},
        {"set-default-activation-function", SETDEFACTFUNC},
        {"add-neuron", ADDNEURON},
        {"set-property", SETPROPERTY},
        {"add-connection", ADDCONNECTION},
        {"build", BUILD}
    };

	switch(commands[parsedInput[0]])
    {
        case SETNAME:
            if (argumentCountCheck(argumentCount, 2, true)) {
                builder->setName(parsedInput[1]);
            }
            break;
        case SETDATE:
            if (argumentCountCheck(argumentCount, 2, true)) {
                builder->setDate(parsedInput[1]);
            }
            break;
        case SETDEFCOMPFUNC:
            if (argumentCountCheck(argumentCount, 2, true)) {
                if (parsedInput[1] == "sum") {
                    builder->setDefaultCompositionFunction(compositionFunctionSum);
                } else {
                    cout << "Error: unrecognized composition function" << endl;
                }
            }
            break;
        case SETDEFACTFUNC:
            if (argumentCountCheck(argumentCount, 2, true)) {
                if (parsedInput[1] == "sigmoid") {
                    builder->setDefaultActivationFunction(activationFunctionSigmoid);
                } else {
                    cout << "Error: unrecognized activation function" << endl;
                }
            }
            break;
        case ADDNEURON:
            if (argumentCountCheck(argumentCount, 2, true)) {
                builder->addNeurons(stoi(parsedInput[1]));
            }
            break;
        case SETPROPERTY:
            if (argumentCountCheck(argumentCount, 4, true)) {
                string iOProperty = parsedInput[1];
                int from = stoi(parsedInput[2]);
                int to = stoi(parsedInput[3]);

                if (iOProperty == "input") {
                    builder->setPropertiesForNeuronRange(NeuronProportyInput, from, to);
                    cout << "property input set" << endl;
                } else if (iOProperty == "output") {
                    builder->setPropertiesForNeuronRange(NeuronProportyOutput, from, to);
                    cout << "property output set" << endl;
                } else {
                    cout << "Error: unrecognized property" << endl;
                }
            }
            break;
        case ADDCONNECTION:
            if (argumentCountCheck(argumentCount, 3, true)) {
                string from = parsedInput[1];
                string to = parsedInput[2];
                vector<int> parsedFrom = splitStringToInt(from, "-");
                vector<int> parsedTo = splitStringToInt(to, "-");

                if (parsedFrom.size()==1 && parsedTo.size()==1) {
                    builder->addConnection(parsedFrom[0], parsedTo[0]);
                } else if (parsedFrom.size()==2 && parsedTo.size()==1) {
                    cout << "many to one" << endl;
                } else if (parsedFrom.size()==1 && parsedTo.size()==2) {
                    cout << "one to many" << endl;
                } else if (parsedFrom.size()==2 && parsedTo.size()==2) {
                    cout << "many to many" << endl;
                } else {
                    cout << "Error: invalid arguments" << endl;
                }
            }
            break;
        case BUILD:
            if (argumentCountCheck(argumentCount, 4, true)) {
                bool randomWeights = false;
                if (parsedInput[1] == "Y" || parsedInput[1] == "y" || parsedInput[1] == "yes") {
                    randomWeights = true;
                }
                int minWeight = stoi(parsedInput[2]);
                int maxWeight = stoi(parsedInput[3]);

                builder->buildNeurons(randomWeights, minWeight, maxWeight);
                cout << "Neuron network built" << endl;
            }
            break;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"
        default:
#pragma clang diagnostic pop
            cout << "Error: unrecognized command" << endl;
            break;
    }
}

void Console::commandExecution(vector<string> parsedInput) {
    // executes a command

    unsigned long argumentCount = parsedInput.size();

    map<string,Command> commands = {
        {"list-saved-networks", LISTSAVEDNETWORKS},
        {"list-scripts", LISTSCRIPTS},
        {"list-idxs", LISTIDXS},
        {"script", SCRIPT},
        {"network-builder-script", NETWORKBUILDERSCRIPT},
        {"network-builder",NETWORKBUILDER}
    };

	switch(commands[parsedInput[0]])
    {
        case LISTSAVEDNETWORKS:
    	    if (argumentCountCheck(argumentCount, 1, true)) {
    	        listSavedNetworks();
    	    }
      	    break;
      	case LISTSCRIPTS:
            if (argumentCountCheck(argumentCount, 1, true)) {
                listScripts();
            }
      	    break;
      	case LISTIDXS:
      	    if (argumentCountCheck(argumentCount, 1, true)) {
      	        listIdxs();
      	    }
      	    break;
        case SCRIPT:
            if (argumentCountCheck(argumentCount, 2, true)) {
                scriptExecution(parsedInput[1]);
            }
            break;
        case NETWORKBUILDERSCRIPT:
            if (argumentCountCheck(argumentCount, 2, true)) {
                NeuronNetwork network = networkBuilderScriptExecution(parsedInput[1]);
            }
            break;
        case NETWORKBUILDER:
            if (argumentCountCheck(argumentCount, 1, true)) {
                NeuronNetwork network = networkBuilderInteractive();
            }
            break;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"
       default:
#pragma clang diagnostic pop
            cout << "Error: unrecognized command" << endl;
            break;
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// Interactive methods

NeuronNetwork Console::networkBuilderInteractive() {
    // calls NeuronNetworkBuilder methods interactively

    bool networkBuilderMode = true;
    string rawInput;
    status = "network builder";

    NeuronNetworkBuilder builder = NeuronNetworkBuilder();

    while (networkBuilderMode == true) {
        cout << status << ">> ";
		getline(cin, rawInput);

        vector<string> parsedInput = splitString(rawInput, " ");

        if (parsedInput[0] == "exit" || parsedInput[0] == "quit") {
            status = "";
            networkBuilderMode = false;
            break;
        }

        networkBuilderCommandExecution(parsedInput, &builder);
    }
    return(builder.generateComputationalNetwork());
}

void Console::interactive() {
    // interactive method

	bool interactiveEnabled = true;
    string rawInput;

	while (interactiveEnabled) {
		cout << status << ">> ";
		getline(cin, rawInput);

        vector<string> parsedInput = splitString(rawInput, " ");
        
        if (parsedInput.size() < 1)
            parsedInput.push_back("");

        if (parsedInput[0] == "exit" || parsedInput[0] == "quit") {
            goodbye();
            interactiveEnabled = false;
            return;
        }

        commandExecution(parsedInput);
    }
    return;
}
