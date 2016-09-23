#ifndef DEF_NEURONE
#define DEF_NEURONE

#include <string>

class Neurone
{
    public:

    private:

    int nbin;
    int nbout;
    Neurone next[];
    double (*comp) (double);
    double (*activ) (double);
};


#endif
