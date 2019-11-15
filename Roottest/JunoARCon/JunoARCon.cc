#include <iostream>
#include "ReactorNuFlux.hh"
#include "IBDCrossSection.hh"
#include "OscillationFunction.hh"
#include "NeutrinoSepctrum.hh"
#include "JunoARCon.hh"
#include "DeltaChisqReactor.hh"
#include <TF1.h>
#include <TF1Convolution.h>
#include <TCanvas.h>
//#include "omp.h"
#define PI 3.1415926

using namespace std;

double E_Lower=1.9;
double E_Upper=9.;
double EnergyResolution=0.03;
int NumOfBins=200;


int main()
{
    //NeutrinoSpectrum* myNeuSpec=new NeutrinoSpectrum(0.1);
    //myNeuSpec->SetEnergyResolution(0.1);
    double eee[]={4.};
    double mmm[]={2.525e-3};
    double c=GeDataDeltaChisqReactor(mmm);
    // OscillationFunction oss;
    // oss.SetBaseline(52.3);
    // ReactorNuFlux nnn;
    // IBDCrossSection iii;
    // NeutrinoSpectrum sss;
    // TF1 *f1=
    // //new TF1("f1",sss,1.9,E_Upper,1);
    // new TF1("f1",SmearedNeutrinoSpectrum,E_Lower,E_Upper,1);
    // TF1 *f0=new TF1("f0",sss,E_Lower,E_Upper,1);
    // f0->SetParameter(0,mmm[0]);
    // f1->SetParameter(0,mmm[0]);
    // TCanvas a;
    // //f0->Draw();
    // //cout<<(*f1)(2.5)<<endl;
    // f1->SetLineColor(kBlue);
    // f1->SetNpx(400);
    // f1->Draw();
    // f0->SetNpx(400);
    // f0->Draw("SAME");
    // a.SaveAs("aa.png");
    
    return 0;
}

double SmearedNeutrinoSpectrum(double *E_nu,double *par)
//par: {Delta31sq,}
{
    NeutrinoSpectrum nnns;
    nnns.SetBaseLine(52.5);
    nnns.SetRunTime(365*4);

    TF1* EnergySmearing=new TF1("EnergySmearing","gaus",-100.,100.);
    EnergySmearing->SetParameters(1. / ( sqrt( 2. * PI * E_nu[0]) * EnergyResolution),0,EnergyResolution * sqrt(E_nu[0]));
    TF1 *Spec0=new TF1("Spec0",nnns,E_Lower,E_Upper,1);
    Spec0->SetParameter(0,par[0]);
    TF1Convolution *SpecConvolution=new TF1Convolution(Spec0,EnergySmearing);
    TF1 * SpecFinal=new TF1("SpecFinal",*SpecConvolution,E_Lower,E_Upper,SpecConvolution->GetNpar());
    SpecFinal->SetParameters(par[0],1. / (sqrt(2. * PI * E_nu[0]) * EnergyResolution),0,EnergyResolution *sqrt(E_nu[0]));
    //cout<<(*SpecFinal)(E_nu[0])<<endl;
    double en;
    en=(*SpecFinal)(E_nu[0]);
    delete EnergySmearing,Spec0,SpecFinal;
    return en;

}