#!/bin/sh
# clang++ compilation script

# object files generation
clang++ -std=c++11 -c neuronNetwork/neuronNetwork.cpp -o neuronNetwork.o
clang++ -std=c++11 -c idxParser/idxParser.cpp -o idxParser.o

# linking and building
# -lz option is necessary to interact with .gz files (IDX parser)
# -Weverything option shows all warnings
# -std=c++11 option forces c++11 compatibility
clang++ -std=c++11 -Weverything -o testBuild main.cpp neuronNetwork.o idxParser.o -lz

# cleaning object files
rm *.o
