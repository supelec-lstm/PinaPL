#!/bin/sh
# clang++ compilation script

# object files generation
# PERCEPTRON
#clang++ -std=c++11 -Ofast -c perceptron/mathFunctions.cpp -o mathFunctions.o
#clang++ -std=c++11 -Ofast -c perceptron/neuronNetwork.cpp -o neuronNetwork.o

#RTRL
#clang++ -std=c++11 -c rtrl/mathFunctions.cpp -o mathFunctions.o
#clang++ -std=c++11 -c rtrl/neuronNetwork.cpp -o neuronNetwork.o

#BPTT
g++ -I /usr/local/include/Eigen -std=c++11 -c bptt/mathFunctions.cpp -o mathFunctions.o
g++ -I /usr/local/include/Eigen -std=c++11 -c bptt/neuronNetwork.cpp -o neuronNetwork.o

# PARSER
#clang++ -std=c++11 -Ofast -c idxParser/idxParser.cpp -o idxParser.o

# GRAMMAR
g++ -std=c++11 -Ofast -c grammar/state.cpp -o state.o
g++ -std=c++11 -Ofast -c grammar/grammar.cpp -o grammar.o

# TESTS
clang++ -std=c++11 -Ofast -c test/test.cpp -o test.o
clang++ -std=c++11 -Ofast -c test/bptt.cpp -o bptt.o
#clang++ -std=c++11 -Ofast -c test/mnist.cpp -o mnist.o
#clang++ -std=c++11 -c test/xor.cpp -o xor.o

# linking and building
# -lz option is necessary to interact with .gz files (IDX parser)
# -Weverything option shows all warnings
# -std=c++11 option forces c++11 compatibility
g++ -I /usr/local/include/Eigen -std=c++11 -lz -Ofast -o testBuild main.cpp mathFunctions.o neuronNetwork.o state.o grammar.o test.o bptt.o
# cleaning object files
rm *.o
