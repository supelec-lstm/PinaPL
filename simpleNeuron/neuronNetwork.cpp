#include <string>
#include <stdlib.h>

#include "neuron.hpp"
#include "neuronNetwork.hpp"

using namespace std;

// Initialisation

NeuronNetwork::NeuronNetwork(string givenName, string givenDate, unsigned long nbin, unsigned long nbout, unsigned long ntot){

    name = givenName;
    date = givenDate;
    inputCount = nbin;
    outputCount = nbout;
    neuronsCount = ntot;

    input = new double[nbin];
    output = new double[ntot];

    relation = (bool**)malloc(ntot*sizeof(bool*)); //#magic trick for 2-dimensional array
    for(unsigned long i = 0; i < ntot; i++){
        relation[i] = new bool[ntot];
    }

    inputNeurons = new unsigned long[nbin];
    outputNeurons = new unsigned long[nbout];
    neurons = new Neuron[ntot]();
}

void NeuronNetwork::reset(){

    input = new double[inputCount];
    output = new double[neuronsCount];
    for(unsigned long i; i < neuronsCount; i++){
        neurons[i].reset();
    }
}

void NeuronNetwork::setRelation(bool** tab){

    relation = tab;
}

void NeuronNetwork::setInputNeurons(unsigned long* tab){

    inputNeurons = tab;
}

void NeuronNetwork::setOutputNeurons(unsigned long* tab){

    outputNeurons = tab;
}

void NeuronNetwork::setNeurons(Neuron* tab){

    neurons = tab;
}

// Calcul

void NeuronNetwork::setInput(double* data){

    reset();
    for(unsigned long i = 0; i < inputCount; i++){
        double x[1];
        x[0] = data[i];
        neurons[inputNeurons[i]].setInput(x);
    }
}

void NeuronNetwork::calculate(){

    double y[neuronsCount];
    for(unsigned long i = 0; i < neuronsCount; i++){
        y[i] = neurons[inputNeurons[i]].getOutput();
    }
}
