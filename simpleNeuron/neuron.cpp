#include <math.h>

#include "neuron.hpp"

Neuron::Neuron(int in, double compositionFunction(double[], int), double activationFunction(double))
{
    inputCount = in;
    weight = new double[in];
    activation = activationFunction;
    composition = compositionFunction;
}

double Neuron::compute(double x[])
{
    double y[inputCount];

    for(int i = 0; i < inputCount; i++)
    {
        y[i] = x[i] * weight[i];
    }
    return activation(composition(y, inputCount));
}

void Neuron::setWeight(double x[])
{
    for(int i = 0; i < inputCount; i++)
    {
        weight[i] = x[i];
    }
}

void Neuron::initWeight()
{
    double a = 1/((double)inputCount);
    for(int i = 0; i < inputCount; i++)
    {
        weight[i] = a;
    }
}

double Neuron::activationSigmoid(double x)
{
    double a = 1+exp(-x);
    return (1/a);
}

double Neuron::activationHeavyside(double x)
{
    if(x < 0){
        return 0;
    }
    else{
        return 1;
    }
}

double Neuron::activationArctan(double x)
{
    return atan(x);
}

double Neuron::compositionSum(double x[], int n)
{
    double sum = 0;
    for(int i = 0; i < n; i++)
    {
        sum += x[i];
    }
    return sum;
}

double Neuron::compositionDist(double x[], int n)
{

}
