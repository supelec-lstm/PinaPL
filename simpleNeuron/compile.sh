g++ -c console/console.cpp -o console.o
g++ -c simpleNeuron/neuron.cpp -o neuron.o
g++ -c neuronNetwork/neuronNetwork.cpp -o neuronNetwork.o
g++ -o testBuild main.cpp console.o neuron.o neuronNetwork.o
rm *.o
