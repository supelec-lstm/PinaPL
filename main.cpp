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

#include "neuronNetwork/neuronNetwork.hpp"
#include "idxParser/idxParser.hpp"


using namespace std;

double sigmoid(double x);
double sigmoidDerivate(double x);
double relu(double x);
double reluDerivate(double x);
double randomizer(double m, double M);
int maximum(double* tab, int n);

void testXOR();
void testMNIST(int nbreData, int nbreLearn, int nbreTest);

int main(int argc, const char * argv[]) {
    srand(unsigned(short(time(NULL))));

    /*vector<string> stringedArgv = vector<string>(unsigned(argc));

    for (int i = 0; i < argc; i++) {
        unsigned long length = strlen(argv[i]);
        string argument;
        argument.assign(argv[i], length);
        stringedArgv[unsigned(i)] = argument;
    }



    if (isArgumentPresent("--log", &stringedArgv)) {
    }

    if (isArgumentPresent("--interactive", &stringedArgv)) {
        // if there is a single argument and it is "--interactive"
        Console console;
        console.greeting();
        console.interactive();
        console.goodbye();
    } else {
        testMINST();
    }*/
    //testMNIST(60000, 1, 1000);
    testXOR();
    return 0;
}

double randomizer(double m, double M){
    int a = rand();
    double b = static_cast<double>(a)/RAND_MAX * (M - m) + m;
    return b;
}

double relu(double x){
    if(x < 0){
        return 0;
    }
    return x;
}

double reluDerivate(double x){
    if(x > 0){
        return 1;
    }
    return 0;
}

double sigmoid(double x){
    double a = exp(-x);
    return 1/(1+a);
}

double sigmoidDerivate(double x){
    return x*(1-x);
}

void testXOR(){
    NeuronNetwork network(2, 1, 3, 0.3);

    vector<vector<bool> > relation(3);
    for(int i = 0; i < 3; i++){
        vector<bool> v(5, false);
        relation[i] = v;
    }
    relation[0][0] = true;
    relation[0][1] = true;
    relation[1][0] = true;
    relation[1][1] = true;
    relation[2][2] = true;
    relation[2][3] = true;
    network.setRelation(relation);

    vector<vector<double> > weight(3);
    for(int i = 0; i < 3; i++){
        vector<double> v(5, 0);
        weight[i] = v;
    }
    weight[0][0] = randomizer(-2, 2);
    weight[0][1] = randomizer(-2, 2);
    weight[1][0] = randomizer(-2, 2);
    weight[1][1] = randomizer(-2, 2);
    weight[2][2] = randomizer(-2, 2);
    weight[2][3] = randomizer(-2, 2);
    network.setWeight(weight);

    vector<double> bias(3, 0);
    network.setBias(bias);
    bias[0] = randomizer(-2, 2);
    bias[1] = randomizer(-2, 2);
    bias[2] = randomizer(-2, 2);

    //vector<ActivationFunctionMain> functions(3, &sigmoid);
    vector<ActivationFunctionMain> functions(3, &relu);
    network.setActivation(functions);

    //vector<ActivationFunctionDerivative> functionsDerivate(3, &sigmoidDerivate);
    vector<ActivationFunctionDerivative> functionsDerivate(3, &reluDerivate);
    network.setActivationDerivate(functionsDerivate);
    network.init();

    double** input = static_cast<double**>(malloc(4 * sizeof(double*)));
    for(int i = 0; i < 4; i++){
        input[i] = new double[2];
    }
    input[0][0] = 0; input[0][1] = 0;
    input[1][0] = 0; input[1][1] = 1;
    input[2][0] = 1; input[2][1] = 0;
    input[3][0] = 1; input[3][1] = 1;

    double** output = static_cast<double**>(malloc(4 * sizeof(double*)));
    for(int i = 0; i < 4; i++){
        output[i] = new double[2];
    }
    output[0][0] = 0;
    output[1][0] = 1;
    output[2][0] = 1;
    output[3][0] = 0;

    network.batchLearning(input, output, 4, 100);

    network.reset();
    for(int i = 0; i < 4; i++){
        network.setInput(input[i]);
        network.calculate();
        cout << network.getOutput()[0] << endl;
    }
}

void testMNIST(int nbreData, int nbreLearn, int nbreTest){

    cout << "=== Importation des images ===" << endl;

    IdxParser parser;
    string imagesLearnPath = "./idxs/train-images-idx3-ubyte.gz";
    string labelsLearnPath = "./idxs/train-labels-idx1-ubyte.gz";
    string imagesTestPath = "./idxs/t10k-images-idx3-ubyte.gz";
    string labelsTestPath = "./idxs/t10k-labels-idx1-ubyte.gz";
    vector<vector<int> > imgLearn = parser.importMNISTImages(imagesLearnPath);
    vector<int> labelLearn = parser.importMNISTLabels(labelsLearnPath);
    vector<vector<int> > imgTest = parser.importMNISTImages(imagesTestPath);
    vector<int> labelTest = parser.importMNISTLabels(labelsTestPath);

    cout << "=== Traitement des inputs ===" << endl;

    double** inputData = static_cast<double**>(malloc(nbreData * sizeof(double*)));
    for(int i = 0; i < nbreData; i++){
        inputData[i] = new double[784];
        for(int j = 0; j < 784; j++){
            inputData[i][j] = (double)imgLearn[i][j]/255;
        }
    }
    imgLearn = (vector<vector<int> >)0;

    double** inputTest = static_cast<double**>(malloc(nbreTest * sizeof(double*)));
    for(int i = 0; i < nbreTest; i++){
        inputTest[i] = new double[784];
        for(int j = 0; j < 784; j++){
            inputTest[i][j] = (double)imgTest[i][j]/255;
        }
    }
    imgTest = (vector<vector<int> >)0;

    cout << "=== Traitement des outputs ===" << endl;

    double** outputData = static_cast<double**>(malloc(nbreData * sizeof(double*)));
    for(int i = 0; i < nbreData; i++){
        outputData[i] = new double[10];
        for(int j = 0; j < 10; j++){
            outputData[i][j] = 0;
        }
        outputData[i][labelLearn[i]] = 1;
    }
    labelLearn = (vector<int>)0;

    int* outputTest = new int[nbreTest];
    for(int i = 0; i < nbreTest; i++){
        outputTest[i] = labelTest[i];
    }
    labelTest = (vector<int>)0;

    cout << "=== Création du réseau ===" << endl;

    NeuronNetwork network(784, 10, 20, 0.3);

    cout << "=== Matrice de relation ===" << endl;

    vector<vector<bool> > relation(20);
    for(int i = 0; i < 20; i++){
        vector<bool> v(804, false);
        relation[i] = v;
    }
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 784; j++){
            relation[i][j] = true;
        }
    }
    for(int i = 10; i < 20; i++){
        for(int j = 784; j < 794; j++){
            relation[i][j] = true;
        }
    }
    network.setRelation(relation);

    cout << "=== Création des poids ===" << endl;

    vector<vector<double> > weight(20);
    for(int i = 0; i < 20; i++){
        vector<double> v(784);
        weight[i] = v;
        for(int j = 0; j < 784; j++){
            weight[i][j] = randomizer(-0.01, 0.01);
        }
    }
    network.setWeight(weight);

    cout << "=== Création des biais ===" << endl;

    vector<double> bias(20, 0);
    network.setBias(bias);

    cout << "=== Création des fonctions d'activation ===" << endl;

    vector<ActivationFunctionMain> functions(20, &sigmoid);
    network.setActivation(functions);

    cout << "=== Création des dérivées ===" << endl;

    vector<ActivationFunctionDerivative> functionsDerivate(20, &sigmoidDerivate);
    network.setActivationDerivate(functionsDerivate);

    cout << "=== Initialisation du réseau ===" << endl;

    network.init();

    cout << "=== Apprentissage ===" << endl;

    network.batchLearning(inputData, outputData, nbreData, nbreLearn);

    cout << "=== Test ===" << endl;

    for(int i = 0; i < nbreTest; i++){
        network.reset();
        network.setInput(inputTest[i]);
        network.calculate();
        int a = maximum(network.getOutput(), 10);
        cout << a << " - " << outputTest[i] << endl; 
    }

    cout << endl;
}

int maximum(double* tab, int n){
    int result = 0;
    for(int j = 0; j < n; j++){
        if(tab[result] < tab[j]){
            result = j;
        }
    }
    return result;
}
