#ifndef DEF_NEURONE
#define DEF_NEURONE

#include <string>

enum ActiveFunc {SIG1, SIG2, HEA, ARCT};
enum CompFunc {SUM, DIST};

class Neurone
{
    public:

    Neurone(int in, int out, ActiveFunc activFunc, CompFunc compFunc);
    double calcul(double x);

    private:

    int nbin;                      //Nombre d'entrées
    int nbout;                     //Nombre de sorties
    double* weight;                //Tableau des poids
    double (*comp) (double);       //Fonction de composition
    double (*activ) (double);      //Fonction d'activation

    static double actSig1(double x);
    static double actSig2(double x);
    static double actHea(double x);
    static double actArct(double x);

    static double compSum(double x[]);
    static double compDist(double x[]);
};


#endif

