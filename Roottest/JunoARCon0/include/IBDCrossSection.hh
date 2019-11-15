#ifndef IBDCrossSection_hh
#define IBDCrossSection_hh
#include <TMath.h>

class IBDCrossSection
{
    public:
        IBDCrossSection(/* args */);
        ~IBDCrossSection();
        double GetIBDCrossSection(double *E_nu, double *par);
    private:
        /* data */
        double SigmaTotal;
        double E_electron;
        double P_electron;
        double M_electron;
        double M_proton;
        double M_neutron;
        double A,B,C; //coefient in the exponent
};


#endif