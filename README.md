# PinaPL
PinaPL Is Not A Projet Long [![Build Status](https://travis-ci.org/supelec-lstm/PinaPL.svg?branch=rtrl)](https://travis-ci.org/supelec-lstm/PinaPL)

## Git Usage Guide
Do not forget to configure and update your .gitignore to keep the repository clean from any project file.

## Syntax conventions
Naming: variableName
        ClassName
Indentation: 4 spaces

## How to draw graphs
- Enable the GRAPH tag and disable all the others
- write the output into a file (`./testBuild > graph.log`)
- put `graph.log` into dot (a command from the graphviz package) : `cat graph.log | dot -Tpng > mnist.png`
- enjoy
