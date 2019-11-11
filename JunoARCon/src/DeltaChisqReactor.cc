#include "DeltaChisqReactor.hh"
#include <iostream>
#include "ReactorNuFlux.hh"
#include "IBDCrossSection.hh"
#include "OscillationFunction.hh"
#include "NeutrinoSepctrum.hh"
//#include "JunoARCon.hh"
#include <TFile.h>
#include <TF1.h>
#include <TH1.h>
#include <TCanvas.h>

using namespace std;



double GeDataDeltaChisqReactor(double *dm31,double *par)
{
    
    double tSum;
    double CofBin=0;
    TF1 *f_0=new TF1("f1",SmearedNeutrinoSpectrum,E_Lower,E_Upper,1);
    f_0->SetParameter(0,dm31[0]);
    TH1D * h_NormalOrder=new TH1D("h_NormalOrder","NormalOrderData",NumOfBins,E_Lower,E_Upper);
    for(int i=0;i<NumOfBins;i++)
    {
        CofBin=E_Lower + (0.5+(double)i) * BinWidth;
        tSum=f_0->Integral((E_Lower + i * BinWidth ),(E_Lower + (i + 1) * BinWidth ),intgreralinterval);
        h_NormalOrder->Fill(CofBin,tSum);
        //cout<<tSum<<endl;
    }
    
    TH1D *h_InvertOrder=new TH1D("h_InvertOrder","InvertOrderData",NumOfBins,E_Lower,E_Upper);
    f_0->SetParameter(0,-dm31[0]);
    for(int i=0;i<NumOfBins;i++)
    {
        CofBin=E_Lower + (0.5+(double)i) * BinWidth;
        tSum=f_0->Integral((E_Lower + i * BinWidth ),(E_Lower + (i + 1) * BinWidth ),intgreralinterval);
        h_InvertOrder->Fill(CofBin,tSum);
        //cout<<tSum<<endl;
    }
    TFile *file0=TFile::Open("SoCallData.root","RECREATE");
    h_NormalOrder->Write();
    h_InvertOrder->Write();
    file0->Close();
    return 0;
}

double CalculateDeltaChisqRea(double *dm31sq,double *pullpar)
// pullpar:1-4:{correlated reactor uncertainty, 
// uncorrelated r u, 
// spectrum shape uncertainty, 
// detector-related uncertainty}
{
    TFile * f_readdata=TFile::Open("SoCallData.root");
    TH1 *h1_NO=0;//normal order "true data"
    TH1 *h2_IO=0;//invert order "true data"
    f_readdata->GetObject("NormalOrder",h1_NO);
    f_readdata->GetObject("InvertOrder",h2_IO);
    double Chisq_Rea=0;
    double D_i=0;
    double sumpull=0,sumpullsq=0;
    double TheoEvt[NumOfBins];
    TF1 *f_0=new TF1("f1",SmearedNeutrinoSpectrum,E_Lower,E_Upper,1);
    f_0->SetParameter(0,dm31sq[0]);
    double tSum=0;
    for(int i=0;i<NumOfBins;i++)
    {
        tSum=f_0->Integral((E_Lower + i * BinWidth ),(E_Lower + (i + 1) * BinWidth ),intgreralinterval);
        TheoEvt[i]=tSum;
        //cout<<tSum<<endl;
    }

    for(int j=0;j<4;j++)
    {
        sumpull += pullpar[j];
        sumpullsq += pullpar[j]  * pullpar[j];
    }
    for(int i=0;i<NumOfBins;i++)
    {
        D_i = h2_IO->GetBinContent(i);
        TheoEvt[i] *= (1. + sumpull);
        Chisq_Rea += (2. * (TheoEvt[i] - D_i + D_i * TMath::Log(D_i / TheoEvt[i])) + sumpullsq);
        //Poisson chi^2 above, should be same as Gaussian Chi^2, 
        //It should be Delta chi^2 here, but since the "data" was generated 
        //by the same procedure as fit theory, one of the term in delta chi^2 is 0
    }

    return Chisq_Rea;
}


// void Ini_EB()
// {
//     double t=E_Lower;
//     for(int i=0;i<NumOfBins;i++)
//     {
//         EnergyBin_Rea[i]=t + i * BinWidth;
//     }
// }
