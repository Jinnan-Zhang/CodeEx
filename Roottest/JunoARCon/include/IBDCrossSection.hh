#ifndef IBDCrossSection_hh
#define IBDCrossSection_hh
#include <TF1.h>

class TF1;

class IBDCrossSection
{
    public:
        IBDCrossSection(/* args */);
        ~IBDCrossSection();
        double GetIBDCrossSection(double *E_nu, double *par={0});
        double operator()(double *E_nu,double *par)
        {
            return this->GetIBDCrossSection(E_nu);
        }
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