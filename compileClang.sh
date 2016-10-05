clang++ -std=c++11 -c console/console.cpp -o console.o
clang++ -std=c++11 -c simpleNeuron/neuron.cpp -o neuron.o
clang++ -std=c++11 -c neuronNetwork/neuronNetwork.cpp -o neuronNetwork.o
clang++ -std=c++11 -c neuronNetwork/neuronNetworkBuilder.cpp -o neuronNetworkBuilder.o
clang++ -std=c++11 -c idxParser/idxParser.cpp -o idxParser.o
clang++ -std=c++11 -Weverything -o testBuild main.cpp console.o neuron.o neuronNetwork.o neuronNetworkBuilder.o idxParser.o -lz
rm *.o
