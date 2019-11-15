#ifndef NeutrinoSpectrum_hh
#define NeutrinoSepctrum_hh
#include <TF1.h>
class TF1;

class NeutrinoSpectrum
{
    public:
        NeutrinoSpectrum();
        ~NeutrinoSpectrum();
        //void SetEnergyResolution(double E_Re){Energy_resolution=E_Re;}
        void SetProtonMassRatio(double ra){MassRatioOfProton=ra;}
        void SetRunTime(double RTinDay){RunTime=RTinDay;}
        void SetLSMass(double m_inkg){MassOfLS=m_inkg;}
        void SetBaseLine(double L_inkm){BaseLine=L_inkm;}//L in km
        double GetBaseLine(){return BaseLine;}
        double GetEfficiency(double *E_nu,double *par={0});
        double Spectrum0(double *E_nu,double *par);
        double operator()(double *E_nu,double *par);
        
        // {
        //     ReactorNuFlux *myflux=new ReactorNuFlux();
        //     IBDCrossSection *myCS=new IBDCrossSection();
        //     OscillationFunction *myOSP=new OscillationFunction();
        //     TF1* EnergySmearing=new TF1("EnergySmearing","gaus",-100.,100.);
        //     EnergySmearing->SetParameters(1./(sqrt(2.*TMath::Pi()*E[0])*Energy_resolution),0,Energy_resolution*sqrt(E[0]));
            
        // }
        
    private:
        double RunTime;
        //double Energy_resolution;
        double DetectionEfficiency;
        double MassOfLS;//in kg
        double MassOfPronton_kg;

        double MassRatioOfProton;
        double DeltaM31_sq;
        double BaseLine;//in km
        double NumOfProton;
};



#endif