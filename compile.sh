g++ -c console/console.cpp -o console.o
g++ -c simpleNeuron/neuron.cpp -o neuron.o
g++ -c neuronNetwork/neuronNetwork.cpp -o neuronNetwork.o
g++ -c neuronNetwork/neuronNetworkBuilder.cpp -o neuronNetworkBuilder.o
g++ -c idxParser/idxParser.cpp -o idxParser.o
g++ -o testBuild main.cpp console.o neuron.o neuronNetwork.o neuronNetworkBuilder.o idxParser.o -lz
rm *.o
