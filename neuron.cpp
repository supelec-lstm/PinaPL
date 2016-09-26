#include <math.h>

#include "neurone.h"

Neuron::Neuron(int in, int out, ActivationFunction activationFunction, CompositionFunction compositionFunction)
{
    inputCount = in;
    outputCount = out;
    weight = new double[in];
    switch(activationFunction)
    {
    case SIG:
        activation = &activationSignal;
        break;
    case HEA:
        activation = &activationHeavyside;
        break;
    case ARCT:
        activation = &activationArctan;
        break;
    }
    switch(compostionFunction)
    {
    case SUM:
        composition = &compostionSum;
        break;
    case DIST:
        composition = &compositionDist;
        break;
    }
}

double Neuron::compute(double x[])
{
    double y[nbin];

    for(int i = 0; i < nbin; i++)
    {
        y[i] = x[i] * weight[i];
    }
    return activation(composition(y, nbin));
}

void Neuron::setWeight(double x[])
{
    for(int i = 0; i < nbin; i++)
    {
        weight[i] = x[i];
    }
}

void Neuron::initWeight()
{
    a = 1/((double)nbin);
    for(int i = 0; i < nbin; i++)
    {
        weight[i] = a;
    }
}

double Neuron::activationSignal(double x)
{
    double a = 1+exp(-x);
    return (1/a);
}

double Neurone::activationHeavyside(double x)
{

}

double Neurone::activationArctan(double x)
{

}

double Neurone::compositionSum(double x[], int n)
{
    double sum = 0;
    for(int i = 0; i < n; i++)
    {
        sum += x[i];
    }
    return sum;
}

double Neurone::compositionDist(double x[], int n)
{

}
