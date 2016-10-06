#!/bin/sh
# g++ compilation script

# object files generation
g++ -c console/console.cpp -o console.o
g++ -c simpleNeuron/neuron.cpp -o neuron.o
g++ -c neuronNetwork/neuronNetwork.cpp -o neuronNetwork.o
g++ -c neuronNetwork/neuronNetworkBuilder.cpp -o neuronNetworkBuilder.o
g++ -c idxParser/idxParser.cpp -o idxParser.o

# linking and building
# -lz option is necessary to interact with .gz files (IDX parser)
# -std=c++11 option forces c++11 compatibility
g++ -o testBuild main.cpp console.o neuron.o neuronNetwork.o neuronNetworkBuilder.o idxParser.o -lz

# cleaning object files
rm *.o
