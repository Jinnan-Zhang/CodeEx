#include "NeutrinoSepctrum.hh"
#include "ReactorNuFlux.hh"
#include "IBDCrossSection.hh"
#include "OscillationFunction.hh"
#include "JunoARCon.hh"
#include <TMath.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TF1Convolution.h>
#include <iostream>


using namespace std;


NeutrinoSpectrum::NeutrinoSpectrum()
{
    //DetectionEfficiency=0.8 ;//default constant efficiency
    
   
    MassOfPronton_kg=1.67262192e-27;//kg
    MassOfLS=2.e7; //kg
    MassRatioOfProton=0.1201;//12.01%
    //Energy_resolution=0.03;//3%
    BaseLine=52.5;//default base line in km
    NumOfProton=MassOfLS*MassRatioOfProton/MassOfPronton_kg;
    RunTime=365.*4.;
    // TF1* EnergySmearing=new TF1("EnergySmearing","gaus",-100.,100.);
    // TF1 *Spec0=new TF1("Spec0",Spectrum0,E_Lower,E_Upper,1);
    // TF1Convolution *SpecConvolution=new TF1Convolution(Spec0,EnergySmearing);
    // TF1 * SpecFinal=new TF1("SpecFinal",*SpecConvolution,E_Lower,E_Upper,SpecConvolution->GetNpar());
    
}

NeutrinoSpectrum::~NeutrinoSpectrum()
{
}
double NeutrinoSpectrum::operator()(double *E_nu,double *par)
{
    ReactorNuFlux *myflux=new ReactorNuFlux();
    IBDCrossSection *myCS=new IBDCrossSection();
    OscillationFunction *myOSP=new OscillationFunction();
    
    myOSP->SetBaseline(BaseLine);
    myflux->SetBaseLine(BaseLine);
    
    double s;
    myflux->SetRunTime(RunTime);
    s=(myflux->GetFlux(E_nu)) *( myCS->GetIBDCrossSection(E_nu) ) *( myOSP->GetOsciProbability(E_nu,par))*NumOfProton*GetEfficiency(E_nu);
    //cout<<" s :"<< s<<"  E_nu :"<<E_nu[0]<<endl;
    delete myCS,myflux,myOSP;
    return s;
}

// double NeutrinoSpectrum::(double *E_nu,double *par)
// {
    
//     TF1* EnergySmearing=new TF1("EnergySmearing","gaus",-100.,100.);
//     EnergySmearing->SetParameters(1./(sqrt(2.*TMath::Pi()*E_nu[0])*Energy_resolution),0,Energy_resolution*sqrt(E_nu[0]));
//     TF1 *Spec0=new TF1("Spec0",this->Spectrum0,E_Lower,E_Upper,1);
//     TF1Convolution *SpecConvolution=new TF1Convolution(Spec0,EnergySmearing);
//     TF1 * SpecFinal=new TF1("SpecFinal",*SpecConvolution,0.,E_Upper,SpecConvolution->GetNpar());
//     SpecFinal->SetParameters(par[0],1./(sqrt(2.*TMath::Pi()*E_nu[0])*Energy_resolution),0,Energy_resolution*sqrt(E_nu[0]));
//     return ((*SpecFinal)(E_nu[0])*GetEfficiency(E_nu));
// }

double NeutrinoSpectrum::GetEfficiency(double *E_nu,double *par)
{
    double ee;
    ee=1.-TMath::Exp(-0.3*E_nu[0]*E_nu[0]);
    return ee;
}
