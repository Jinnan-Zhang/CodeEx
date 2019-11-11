#ifndef NeutrinoSpectrum_hh
#define NeutrinoSepctrum_hh
#include <TF1.h>
class TF1;

class NeutrinoSpectrum
{
    public:
        NeutrinoSpectrum();
        ~NeutrinoSpectrum();
        double MassOfLS;//in kg
        double MassOfProtonkg;//in kg
        double NumOfProton;
        double MassRatioOfProton;
        void SetEnergyResolution(double E_Re){Energy_resolution=E_Re;}
        void SetProtonMassRatio(double ra){MassOfProton=ra;}
        void SetLSMass(double m){MassOfLS=m;}
        void SetBaseLine(double L){BaseLine=L;}//L in km
        double GetBaseLine(){return BaseLine;}
        TF1* GetNeutrinoSpectrumFunction(double *par);
        double GetNeutrinoSpectrum(double *E_nu,double *par);
        //double Spectrum0(double *,double *);//spectrum before the energy smearing
        //double DetectionEfficiency;
        
    private:
        double Energy_resolution;
        //double DetectionEfficiency;
        // double MassOfLS;//in kg
        // double MassOfPronton;
        // double NumOfProton;//in kg
        // double MassRatioOfProton;
        //double DeltaM31_sq;
        double BaseLine;//in km
        TF1 * mySpectrumFunc;

};
extern double Spectrum0(double *E_nu,double *par);

extern double GetSpecFunc_new(double *,double *);

extern  double GetEfficiency(double *,double *par={0});

#endif