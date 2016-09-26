#include <math.h>

#include "neuron.hpp"

//Definition

Neuron::Neuron(unsigned long in, double compositionFunction(double[], unsigned long), double activationFunction(double)){

    inputCount = in;
    weight = new double[in];
    input = new double[in];
    activation = activationFunction;
    composition = compositionFunction;
    initWeight();
    reset();
}

void Neuron::reset(){

    for(int i = 0; i < inputCount; i++){
        input[i] = 0;
    }
    output = 0;
}

void Neuron::compute(){

    double y[inputCount];

    for(unsigned long i = 0; i < inputCount; i++)
    {
        y[i] = input[i] * weight[i];
    }
    output = activation(composition(y, inputCount));
}

//Weight

void Neuron::setWeight(const double x[]){

    for(unsigned long i = 0; i < inputCount; i++)
    {
        weight[i] = x[i];
    }
}

const double* Neuron::getWeight(){

    return weight;
}

void Neuron::initWeight(){

    double a = 1/((double)inputCount);
    for(unsigned long i = 0; i < inputCount; i++)
    {
        weight[i] = a;
    }
}

//Input-Output

void Neuron::setInput(const double x[]){

    for(unsigned long i = 0; i < inputCount; i++)
    {
        input[i] = x[i];
    }
}

const double Neuron::getOutput(){

    return output;
}

//Fonction d'activation

double Neuron::activationSigmoid(double x){

    double a = 1+exp(-x);
    return (1/a);
}

double Neuron::activationHeavyside(double x){

    if(x < 0){
        return 0;
    }
    else{
        return 1;
    }
}

double Neuron::activationArctan(double x){

    return atan(x);
}

//Fonction de composition

double Neuron::compositionSum(double x[], unsigned long n){

    double sum = 0;
    for(unsigned long i = 0; i < n; i++)
    {
        sum += x[i];
    }
    return sum;
}

double Neuron::compositionDist(double x[], unsigned long n){

    return 0;
}
