//
//  main.cpp
//  PinaPL
//

#include <iostream>
#include <map>
#include <vector>
#include <typeinfo>
#include <random>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <algorithm>

#include "log.hpp"
#include "test/bptt.hpp"

#include <Eigen/Dense>
using namespace Eigen;

int tab_log = 0;

using namespace std;

int main(int argc, char **argv) {
    /*srand(time(NULL));

    int opt;
    int nbreData  = 60000;
    int nbreLearn = 1;
    int nbreTest  = 10000;
    double learningRate = 0.3;
    int nbreLayout = 1;
    int nbreNeuronPerLayout = 20;

    while ((opt = getopt (argc, argv, "d:l:t:r:L:N:h")) != -1) {
        switch (opt) {
        case 'd':
            nbreData = atoi(optarg);
            break;
        case 'l':
            nbreLearn = atoi(optarg);
            break;
        case 't':
            nbreTest = atoi(optarg);
            break;
        case 'L':
            nbreLayout = atoi(optarg);
            break;
        case 'N':
            nbreNeuronPerLayout = atoi(optarg);
            break;
        case 'r':
            learningRate = stod(optarg);
            break;
        case 'h':
            cout << "Arguments:" << endl;
            cout << "-d : number of data to import from learning set (integer)(default: 60000)" << endl;
            cout << "-l : number of learns per input (integer)(default: 1)" << endl;
            cout << "-t : number of data to import from test set (integer)(default: 10000)" << endl;
            cout << "-r : learning rate (double)(default: 0.3)" << endl;
            cout << "-L : number of network hidden layouts, does not include output layer (integer)(default: 1)" << endl;
            cout << "-N : number of neurons per hidden layout (integer)(default: 20)" << endl;
            return 0;
            break;
        }
    }

    /*int nbreNeuron[nbreLayout+1];
    std::fill_n(nbreNeuron, nbreLayout, nbreNeuronPerLayout);
    nbreNeuron[nbreNeuronPerLayout] = 10;

    Mnist test = Mnist(nbreData, nbreLearn, nbreTest, learningRate, nbreLayout, nbreNeuron);
    test.learn();
    test.test();
*/

	Bptt* test = new Bptt();
	test->learn();
	test->test();



	system("PAUSE");

    return 0;
}
