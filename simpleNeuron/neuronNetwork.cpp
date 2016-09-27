#include <string>
#include <stdlib.h>

#include "neuron.hpp"
#include "neuronNetwork.hpp"

using namespace std;

NeuronNetwork::NeuronNetwork(string givenName, string givenDate, unsigned long nbin, unsigned long nbout, unsigned long ntot){

    name = givenName;
    date = givenDate;
    inputCount = nbin;
    outputCount = nbout;
    neuronsCount = ntot;
    relation = (bool**)malloc(ntot*sizeof(bool*)); //#magic trick for 2-dimensional array
    for(unsigned long i = 0; i < ntot; i++){
        relation[i] = new bool[ntot];
    }
    inputNeurons = new unsigned long[nbin];
    outputNeurons = new unsigned long[nbout];
    neurons = new Neuron[ntot]();
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


