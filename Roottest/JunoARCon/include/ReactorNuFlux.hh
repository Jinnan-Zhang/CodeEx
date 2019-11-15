#ifndef ReactorNuFlux_hh
#define ReactorNuFlux_hh
#include <TF1.h>

class TF1;

class ReactorNuFlux
{
    public:
        ReactorNuFlux();
        ~ReactorNuFlux();

    public:

        void SetPowerGW(double pGW){Power_inGW=pGW;}
        void SetFissionFraction(double *);
        void SetBaseLine(double L){BaseLine=L*1.e5;}//L in km, turn into cm 
        double GetFlux(double *E_nu,double *par={0});
        double GetRunTime(){return RunTime;}
        double GetAverageE();
        void SetRunTime(double T){RunTime=T;}//in day
        double operator()(double * ,double *);

    private:
        double Power_inGW;
        double Average_Energy;
        double RunTime;//in day
        double BaseLine;//in cm
        

        double mFissionE235U;
        double mFissionE239Pu;
        double mFissionE238U;
        double mFissionE241Pu;

        double mFraction235U;
        double mFraction239Pu;
        double mFraction238U;
        double mFraction241Pu;

        double mMuellerCoeff235U[6];
        double mMuellerCoeff239Pu[6];
        double mMuellerCoeff238U[6];
        double mMuellerCoeff241Pu[6];
};



#endif