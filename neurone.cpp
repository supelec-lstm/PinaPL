#include <math.h>

#include "neurone.h"

Neurone::Neurone(int in, int out, ActiveFunc activFunc, CompFunc compFunc)
{
    nbin = in;
    nbout = out;
    weight = new double[in];
    switch(activFunc)
    {
    case SIG:
        activ = &actSig;
        break;
    case HEA:
        activ = &actHea;
        break;
    case ARCT:
        activ = &actArct;
        break;
    }
    switch(compFunc)
    {
    case SUM:
        comp = &compSum;
        break;
    case DIST:
        comp = &compDist;
        break;
    }
}

double Neurone::calcul(double x[])
{
    double y[nbin];

    for(int i = 0; i < nbin; i++)
    {
        y[i] = x[i] * weight[i];
    }
    return activ(comp(y, nbin));
}

void Neurone::setWeight(double x[])
{
    for(int i = 0; i < nbin; i++)
    {
        weight[i] = x[i];
    }
}

void Neurone::initWeight()
{
    a = 1/((double)nbin);
    for(int i = 0; i < nbin; i++)
    {
        weight[i] = a;
    }
}

double Neurone::actSig(double x)
{
    double a = 1+exp(-x);
    return (1/a);
}

double Neurone::actHea(double x)
{

}

double Neurone::actArct(double x)
{

}

double Neurone::compSum(double x[], int n)
{
    double s = 0;
    for(int i = 0; i < n; i++)
    {
        s += x[i];
    }
    return s;
}

double Neurone::compDist(double x[], int n)
{

}
