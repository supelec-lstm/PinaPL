#include <math.h>

#include "neuron.h"

Neuron::Neuron(int in, int out, ActivationFunction activationFunction, CompositionFunction compositionFunction)
{
    inputCount = in;
    outputCount = out;
    weight = new double[in];
    switch(activationFunction)
    {
    case SIG:
        activation = &activationSigmoid;
        break;
    case HEA:
        activation = &activationHeavyside;
        break;
    case ARCT:
        activation = &activationArctan;
        break;
    }
    switch(compositionFunction)
    {
    case SUM:
        composition = &compositionSum;
        break;
    case DIST:
        composition = &compositionDist;
        break;
    }
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

}

double Neuron::activationArctan(double x)
{

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
