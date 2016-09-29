clang++ -std=c++11 -c console/console.cpp -o console.o
clang++ -std=c++11 -c simpleNeuron/neuron.cpp -o neuron.o
clang++ -std=c++11 -c neuronNetwork/neuronNetwork.cpp -o neuronNetwork.o
clang++ -std=c++11 -o testBuild main.cpp console.o neuron.o neuronNetwork.o
rm *.o
