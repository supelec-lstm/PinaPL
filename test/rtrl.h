#ifndef RTRL_H
#define RTRL_H


class RTRL : public Test
{
    int inputCount;
    int neuronCount;
    int outputCount;

    double** weight;
    public:

    RTRL();
    virtual ~RTRL();
};

#endif // RTRL_H
