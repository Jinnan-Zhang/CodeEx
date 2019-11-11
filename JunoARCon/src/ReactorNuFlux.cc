#include <iostream>
#include "ReactorNuFlux.hh"
#include "JunoARCon.hh"
#include <TMath.h>
#include <TF1.h>

using namespace std;

ReactorNuFlux::ReactorNuFlux()
{
    //default power
    Power_inGW=2.9; 

    RunTime=1.;//default runtime :1 day
    BaseLine=52.5e5;//in cm

    //default neutrino flux	
    mFraction235U  = 0.58;
    mFraction239Pu = 0.3;
    mFraction238U  = 0.07;
    mFraction241Pu = 0.05;

    //fission total energy in MeV
    mFissionE235U = 202.36;//pm 0.26
    mFissionE238U = 205.99;//pm 0.52
    mFissionE239Pu = 211.12;//pm 0.34
    mFissionE241Pu = 214.26;//pm 0.33

    //based on Mueller's theory
    mMuellerCoeff235U[0] = 3.217;
    mMuellerCoeff235U[1] = -3.111;
    mMuellerCoeff235U[2] = 1.395;
    mMuellerCoeff235U[3] = -3.690e-1;
    mMuellerCoeff235U[4] = 4.445e-2;
    mMuellerCoeff235U[5] = -2.053e-3;

	     
    mMuellerCoeff238U[0] = 4.833e-1;
    mMuellerCoeff238U[1] = 1.927e-1;
    mMuellerCoeff238U[2] = -1.283e-1;
    mMuellerCoeff238U[3] = -6.762e-3;
    mMuellerCoeff238U[4] = 2.233e-3;
    mMuellerCoeff238U[5] = -1.536e-4;

    mMuellerCoeff239Pu[0] = 6.413;
    mMuellerCoeff239Pu[1] = -7.432;
    mMuellerCoeff239Pu[2] = 3.535;
    mMuellerCoeff239Pu[3] = -8.820e-1;
    mMuellerCoeff239Pu[4] = 1.025e-1;
    mMuellerCoeff239Pu[5] = -4.550e-3;

    mMuellerCoeff241Pu[0] = 3.251;
    mMuellerCoeff241Pu[1] = -3.204;
    mMuellerCoeff241Pu[2] = 1.428;
    mMuellerCoeff241Pu[3] = -3.675e-1;
    mMuellerCoeff241Pu[4] = 4.254e-2;
    mMuellerCoeff241Pu[5] = -1.896e-3;

    GetAverageE();
}

ReactorNuFlux::~ReactorNuFlux()
{}

double ReactorNuFlux::GetFlux(double *nuE,double *par)
{
    
    double E_nu=nuE[0];
    double u235 = mMuellerCoeff235U[0] 
              + mMuellerCoeff235U[1]*E_nu 
              + mMuellerCoeff235U[2]*E_nu*E_nu 
              + mMuellerCoeff235U[3]*E_nu*E_nu*E_nu
              + mMuellerCoeff235U[4]*E_nu*E_nu*E_nu*E_nu
              + mMuellerCoeff235U[5]*E_nu*E_nu*E_nu*E_nu*E_nu;
    u235 = TMath::Exp(u235);
    //cout<<"u235 :"<<u235<<"  "<<E_nu<<endl;

    double u238 = mMuellerCoeff238U[0]
              + mMuellerCoeff238U[1]*E_nu 
	        + mMuellerCoeff238U[2]*E_nu*E_nu
            + mMuellerCoeff238U[3]*E_nu*E_nu*E_nu
            + mMuellerCoeff238U[4]*E_nu*E_nu*E_nu*E_nu
            + mMuellerCoeff238U[5]*E_nu*E_nu*E_nu*E_nu*E_nu;
    u238 = TMath::Exp(u238);

    double pu239 = mMuellerCoeff239Pu[0]  
               + mMuellerCoeff239Pu[1]*E_nu 
               + mMuellerCoeff239Pu[2]*E_nu*E_nu
               + mMuellerCoeff239Pu[3]*E_nu*E_nu*E_nu
               + mMuellerCoeff239Pu[4]*E_nu*E_nu*E_nu*E_nu
               + mMuellerCoeff239Pu[5]*E_nu*E_nu*E_nu*E_nu*E_nu;
    pu239 = TMath::Exp(pu239);

    double pu241 = mMuellerCoeff241Pu[0] 
               + mMuellerCoeff241Pu[1]*E_nu 
               + mMuellerCoeff241Pu[2]*E_nu*E_nu 
               + mMuellerCoeff241Pu[3]*E_nu*E_nu*E_nu
               + mMuellerCoeff241Pu[4]*E_nu*E_nu*E_nu*E_nu
               + mMuellerCoeff241Pu[5]*E_nu*E_nu*E_nu*E_nu*E_nu;
    pu241 = TMath::Exp(pu241);

    double Total_flux;
    Total_flux=u235*mFraction235U 
                + pu239*mFraction239Pu 
                + u238*mFraction238U 
	            + pu241*mFraction241Pu;
    
    double normalize;
    //neurinos per second per fission
    //for a day, 
    normalize=RunTime * 24.*3600.*1.e9/1.e6/1.602e-19;//GW to W,MeV to eV ,eV to J for T days

    Total_flux=Total_flux*Power_inGW/Average_Energy*normalize;
    Total_flux=Total_flux/(4.*TMath::Pi()*BaseLine*BaseLine);
    //cout<<"E_nu "<<E_nu<<" Total_flux "<<Total_flux<<endl;
    
    return Total_flux;
}

double ReactorNuFlux::GetAverageE()
{
    //fission average energy in MeV
    mFissionE235U = 202.36;//pm 0.26
    mFissionE238U = 205.99;//pm 0.52
    mFissionE239Pu = 211.12;//pm 0.34
    mFissionE241Pu = 214.26;//pm 0.33
    
    Average_Energy = mFissionE235U * mFraction235U
                    + mFissionE238U * mFraction238U
                    + mFissionE239Pu * mFraction239Pu
                    + mFissionE241Pu * mFraction241Pu;
    
    return Average_Energy;
}

void ReactorNuFlux::SetFissionFraction(double * FiFrac)
 //order: 235U,238U,239Pu,241Pu
{
    //fission total energy in MeV
    mFissionE235U = FiFrac[0];
    mFissionE238U = FiFrac[1];
    mFissionE239Pu = FiFrac[2];
    mFissionE241Pu = FiFrac[3];
}

double ReactorNuFlux::operator()(double *E_nu,double *par)
{
    return this->GetFlux(E_nu,par);
}

