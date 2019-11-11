#include "OscillationFunction.hh"
#include <TMath.h>
#include <iostream>
#include <fstream>
#include <TF1.h>
#include "JunoARCon.hh"

using namespace std;


OscillationFunction::OscillationFunction()
{
    L_Baseline=52.5e3;//in m
    DeltaM21_sq=7.39e-5;//in eV^2
    Sin_sqTheta21=0.310;// independent of mass order
    Sin_sqTheta31=0.02240;//default normal order

}
OscillationFunction::~OscillationFunction()
{}

double OscillationFunction::GetOsciProbability(double *E_nu,double *par)
//par:DeltaM31_sq
{
    if(par[0]>0)//from Ivan Esteban JHEP01(2019)106
    {
        Sin_sqTheta31=0.02240;
    }
    else if (par[0]<0)//invert orderi
    {
        Sin_sqTheta31=0.02263;
    }
    double E=E_nu[0];//in MeV
    DeltaM31_sq=par[0];
    DeltaM32_sq=DeltaM31_sq-DeltaM21_sq;
    Delta21=1.267*DeltaM21_sq*L_Baseline/E;//eV^2 ,MeV ,m
    Delta31=1.267*DeltaM31_sq*L_Baseline/E;
    Delta32=1.267*DeltaM32_sq*L_Baseline/E;//eV^2 ,MeV ,m
    //cout<<"DeltaM31_sq "<<DeltaM31_sq<<endl;
    //cout<<"Sin_sqTheta31 "<<Sin_sqTheta31<<endl;

    double prob;
    prob=1.-
        4.*Sin_sqTheta31*(1.-Sin_sqTheta31)* ((1.-Sin_sqTheta21)*
        TMath::Power(TMath::Sin(Delta31),2)+Sin_sqTheta21*TMath::Power(TMath::Sin(Delta32),2)) -
        TMath::Power((1.-Sin_sqTheta31),2)*4.*Sin_sqTheta21*
        (1.-Sin_sqTheta21)*TMath::Power(TMath::Sin(Delta21),2);
    //cout<<"prob "<<prob<<" E_nu :"<<E_nu[0]<<endl;
    return prob;
}

void OscillationFunction::SetOscillationParameters(double *par)
//dm21sq,sin_sqTheta21,sin_sqTheta31
{
    DeltaM21_sq=par[0];
    Sin_sqTheta21=par[1];
    Sin_sqTheta31=par[2];
}

