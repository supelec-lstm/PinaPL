#!/bin/sh
# clang++ compilation script

# object files generation
# PERCEPTRON
#clang++ -std=c++11 -Ofast -c perceptron/mathFunctions.cpp -o perceptronMathFunctions.o
#clang++ -std=c++11 -Ofast -c perceptron/neuronNetwork.cpp -o perceptronNeuronNetwork.o

# RTRL
clang++ -std=c++11 -c rtrl/mathFunctions.cpp -o rtrlMathFunctions.o
clang++ -std=c++11 -c rtrl/neuronNetwork.cpp -o rtrlNeuronNetwork.o

# GRAMMAR
clang++ -std=c++11 -c grammar/grammar.cpp -o grammar.o
clang++ -std=c++11 -c grammar/state.cpp -o state.o

# PARSER
#clang++ -std=c++11 -Ofast -c idxParser/idxParser.cpp -o idxParser.o

# TESTS
clang++ -std=c++11 -Ofast -c test/test.cpp -o test.o
#clang++ -std=c++11 -Ofast -c test/mnist.cpp -o mnist.o
clang++ -std=c++11 -c test/rtrl.cpp -o rtrl.o

# linking and building
# -lz option is necessary to interact with .gz files (IDX parser)
# -Weverything option shows all warnings
# -std=c++11 option forces c++11 compatibility
clang++ -std=c++11 -lz -o testBuild main.cpp rtrlMathFunctions.o rtrlNeuronNetwork.o grammar.o state.o test.o rtrl.o
# cleaning object files
rm *.o