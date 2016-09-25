#include "neurone.h"

Neurone::Neurone(int in, int out, ActiveFunc activFunc, CompFunc compFunc)
{
    nbin = in;
    nbout = out;
    weight = new double[in];
    switch(activFunc)
    {
    case SIG1:
        activ = &actSig1;
        break;
    case SIG2:
        activ = &actSig2;
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
        break;
    case DIST:
        break;
    }
}

double Neurone::actSig1(double x)
{

}

double Neurone::actSig2(double x)
{

}

double Neurone::actHea(double x)
{

}

double Neurone::actArct(double x)
{

}

double Neurone::compSum(double x)
{

}

double Neurone::compDist(double x)
{

}
