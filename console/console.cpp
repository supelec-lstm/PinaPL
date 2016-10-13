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

///////////////////////////////////////////////////////////////////////////////////////////////////
// Command parsing methods

bool Console::argumentCountCheck(int argumentCount, int desiredCount) {
    if (argumentCount != desiredCount) {
        cout << "Error: wrong argument count" << endl;
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

void Console::networkBuilderCommandExecution(vector<string> parsedInput, NeuronNetworkBuilder *builder) {
    // executes a command

    int argumentCount = parsedInput.size();

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
        case ADDNEURON:
            if(argumentCountCheck(argumentCount, 2)) {
                builder->addNeurons(stoi(parsedInput[1]));
            }
            break;
        case SETPROPERTY:
            if(argumentCountCheck(argumentCount, 4)) {
                string iOProperty = parsedInput[1];
                int from = stoi(parsedInput[2]);
                int to = stoi(parsedInput[3]);

                if (iOProperty == "input") {
                    builder->setPropertiesForNeuronRange(NeuronProportyInput, from, to);
                    cout << "property input set" << endl;
                } else if (iOProperty == "output") {
                    builder->setPropertiesForNeuronRange(NeuronProportyOutput, from, to);
                    cout << "property output set" << endl;
                }
            }
            break;
        case ADDCONNECTION:
            if(argumentCountCheck(argumentCount, 3)) {
                string from = parsedInput[1];
                string to = parsedInput[2];
                vector<string> parsedFrom = splitString(from, "-");
                vector<string> parsedTo = splitString(to, "-");

                if(parsedFrom.size()==1 && parsedTo.size()==1) {
                    builder->addConnection(stoi(parsedFrom[0]), stoi(parsedTo[0]));
                } else if (parsedFrom.size()==2 && parsedTo.size()==1) {
                    cout << "many to one" << endl;
                } else if (parsedFrom.size()==1 && parsedTo.size()==2) {
                    cout << "one to many" << endl;
                } else if (parsedFrom.size()==2 && parsedTo.size()==2){
                    cout << "many to many" << endl;
                } else {
                    cout << "Error : invalid input" << endl;
                }
            }
            break;
        case BUILD:
            if(argumentCountCheck(argumentCount, 4)) {
                bool randomWeights = false;
                if(parsedInput[1] == "Y" || parsedInput[1] == "y" || parsedInput[1] == "yes") {
                    randomWeights = true;
                }
                int minWeight = stoi(parsedInput[2]);
                int maxWeight = stoi(parsedInput[3]);

                builder->buildNeurons(randomWeights, minWeight, maxWeight);
            }
            break;
        default:
            cout << "Error: unrecognized command" << endl;
            break;
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
            if (argumentCountCheck(argumentCount, 1)) {
                NeuronNetwork network = networkBuilderInteractive();
            }
            break;
        default:
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
    cout << "Generated network named: " << builder.getName() << endl;
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

        if (parsedInput[0] == "exit" || parsedInput[0] == "quit") {
            goodbye();
            interactiveEnabled = false;
            return;
        }

        commandExecution(parsedInput);
    }
    return;
}
