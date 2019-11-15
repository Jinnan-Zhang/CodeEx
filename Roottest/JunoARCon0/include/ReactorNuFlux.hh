#ifndef ReactorNuFlux_hh
#define ReactorNuFlux_hh

class ReaNuFlux
{
    public:
        ReaNuFlux();
        ~ReaNuFlux();

    public:

        void SetPowerGW(double pGW){Power_inGW=pGW};
        void SetFissionFraction(double *)
        double GetFlux(double *E_nu,double *par);
        double GetAverageE();
    private:
        double Power_inGW;
        double Average_Energy;
        

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
}


#endif