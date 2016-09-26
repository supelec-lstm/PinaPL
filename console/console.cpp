#include <iostream>
#include <map>
#include <dirent>

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

void Console::listFolderContent() {
    // lists content of folder networkStorage

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("./")) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL) {
       printf ("%s\n", ent->d_name);
     }
     closedir (dir);
    } else {
     /* could not open directory */
     perror ("");
     return EXIT_FAILURE;
    }

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
