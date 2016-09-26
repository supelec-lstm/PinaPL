g++ -c console.cpp -o console.o
g++ -c simpleNeuron/neuron.cpp -o neuron.o
g++ -o output main.cpp console.o neuron.o
rm *.o
