g++ -c cli.cpp -o cli.o
g++ -c neuron.cpp -o neuron.o
g++ -o output main.cpp cli.o neuron.o
rm cli.o neuron.o
