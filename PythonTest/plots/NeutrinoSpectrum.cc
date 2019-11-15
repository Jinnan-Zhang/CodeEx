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
    
   
    MassOfProton=1.67262192e-27;//kg
    MassOfLS=2.e7; //kg
    MassRatioOfProton=0.1201;//12.01%
    Energy_resolution=0.03;//3%
    BaseLine=52.5;//default base line in km
    // TF1* EnergySmearing=new TF1("EnergySmearing","gaus",-100.,100.);
    // TF1 *Spec0=new TF1("Spec0",Spectrum0,E_Lower,E_Upper,1);
    // TF1Convolution *SpecConvolution=new TF1Convolution(Spec0,EnergySmearing);
    // TF1 * SpecFinal=new TF1("SpecFinal",*SpecConvolution,E_Lower,E_Upper,SpecConvolution->GetNpar());
    //mySpectrumFunc=SpecFinal;
}

NeutrinoSpectrum::~NeutrinoSpectrum()
{
}
double Spectrum0(double *E_nu,double *par)
{
    ReactorNuFlux *myflux=new ReactorNuFlux();
    IBDCrossSection *myCS=new IBDCrossSection();
    OscillationFunction *myOSP=new OscillationFunction();
    
    NeutrinoSpectrum myNeuSpec;
    myOSP->SetBaseline(myNeuSpec.GetBaseLine());
    myflux->SetBaseLine(myNeuSpec.GetBaseLine());
    myNeuSpec.NumOfProton=myNeuSpec.MassOfLS*myNeuSpec.MassRatioOfProton/myNeuSpec.MassOfProton;
    
    //NumOfProton=MassOfLS*MassRatioOfProton/MassOfProton;
    double s;
    myflux->SetRunTime(365.*4.);
    s=(myflux->GetFlux(E_nu)) *( myCS->GetIBDCrossSection(E_nu) ) *( myOSP->GetOsciProbability(E_nu,par))*myNeuSpec.NumOfProton;//(4.*TMath::Pi()*myNeuSpec.L_Baseline) ; 
    //cout<<" s "<< s<<" E_nu :"<<E_nu[0]<<endl;
    return s;
}
double NeutrinoSpectrum::GetNeutrinoSpectrum(double * E_nu,double *par)
//par: DeltaM31_sq
{
    TF1* EnergySmearing=new TF1("EnergySmearing","gaus",-100.,100.);
    EnergySmearing->SetParameters(1./(sqrt(2.*TMath::Pi()*E_nu[0])*Energy_resolution),0,Energy_resolution*sqrt(E_nu[0]));
    TF1 *Spec0=new TF1("Spec0",Spectrum0,E_Lower,E_Upper,1);
    Spec0->SetParameter(0,par[0]);
    TF1Convolution *SpecConvolution=new TF1Convolution(Spec0,EnergySmearing);
    TF1 * SpecFinal=new TF1("SpecFinal",*SpecConvolution,0.,E_Upper,SpecConvolution->GetNpar());
    SpecFinal->SetParameters(par[0],1./(sqrt(2.*TMath::Pi()*E_nu[0])*Energy_resolution),0,Energy_resolution*sqrt(E_nu[0]));
    // if(E_nu[0]<4.)
    // {
    //     TCanvas b;
    //     //cout<<(*f1)(5)<<endl;
    //     Spec0->Draw();
    //     b.SaveAs("bb.png");
    // }
    //cout<<"SpecFinal "<<(*SpecFinal)(E_nu[0])<<" E_nu :"<<E_nu[0]<<endl;
    //cout<<par[0]<<endl;
    return ((*SpecFinal)(E_nu[0])*GetEfficiency(E_nu));
}

double GetSpecFunc_new(double *E_nu,double *par)
{
    NeutrinoSpectrum nnn;
    
    return nnn.GetNeutrinoSpectrum(E_nu,par);
}
 TF1* NeutrinoSpectrum::GetNeutrinoSpectrumFunction(double *par)
 {
    mySpectrumFunc=new TF1("mySpectrumFunc",GetSpecFunc_new,0.,E_Upper,1);
    mySpectrumFunc->SetParameter(0,par[0]);
    
    return mySpectrumFunc;
 }

double GetEfficiency(double *E_nu,double *par)
{
    double ee;
    ee=1.-TMath::Exp(-0.3*E_nu[0]*E_nu[0]);
    return ee;
}
