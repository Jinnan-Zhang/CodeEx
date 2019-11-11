#ifndef OscillationFunction_hh
#define OscillationFunction_hh
#include <TF1.h>

class TF1;

class OscillationFunction
{
    public:
        OscillationFunction();
        ~OscillationFunction();
        void SetOscillationParameters(double *par);//dm21sq,sin_sqTheta21,sin_sqTheta31
        void SetBaseline(double L_inkm){L_Baseline=L_inkm*1.e3;}//L in km, turn into m
        double GetOsciProbability(double *E_nu,double *par);
        double operator()(double *E,double *par)
        {
            return this->GetOsciProbability(E,par);
        }

    private:
        double L_Baseline;//in m
        double DeltaM21_sq;
        double Sin_sqTheta21;
        double Sin_sqTheta31;
        double DeltaM31_sq;
        double DeltaM32_sq;
        double Delta21;
        double Delta31;
        double Delta32;
};


#endif