#ifndef DEF_NEURONE
#define DEF_NEURONE

#include <string>

enum ActiveFunc {SIG, HEA, ARCT};
enum CompFunc {SUM, DIST};

class Neurone
{
    public:

    Neurone(int in, int out, ActiveFunc activFunc, CompFunc compFunc);
    double calcul(double x[]);

    private:

    int nbin;                               //Nombre d'entr�es
    int nbout;                              //Nombre de sorties
    double* weight;                         //Tableau des poids
    double (*comp) (double[], int);         //Fonction de composition
    double (*activ) (double);               //Fonction d'activation

    static double actSig(double x);
    static double actHea(double x);
    static double actArct(double x);

    static double compSum(double x[], int n);
    static double compDist(double x[], int n);
};


#endif

