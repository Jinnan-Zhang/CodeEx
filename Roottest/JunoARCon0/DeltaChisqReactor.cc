#include "DeltaChisqReactor.hh"
#include "JunoARCon.hh"
#include "ReaNeutrinoSpectrum.hh"
#include "Convolution.hh"
#include <time.h>
#include <TFile.h>
#include <TF1.h>
#include <TF2.h>
#include <TH1.h>
#include <TH2.h>
#include <TMath.h>
#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "TRandom3.h"
#include "TError.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "omp.h"

using namespace std;


double bkgratio[5] = {0.015, 1.1 / 60, 0.1 / 60, 1.6 / 60, 0.05 / 60};

//correlated reactor uncertainty,
// uncorrelated reactor uncertainty,
// spectrum shape uncertainty,
// detector-related uncertainty
double errors_sigma[4]={0.02, 0.008, 0.01, 0.01};
vector<vector<double>> alpha_ik;
double intNUM = 7.;

void GeDataHist(double *DefaultSinsq31, double RUNTIME)
//DefaultSinsq31: 0 for normal order, 1 for invert order
{
    TH1::SetDefaultSumw2();
    double tSum = 0.;
    double COfBin = 0;
    ReaNeutrinoSpectrum *reas2 = new ReaNeutrinoSpectrum();
    reas2->SetRunTime_d(RUNTIME);
    reas2->SetOscillationParameters(parameterset);
    TF2 *f_smearspec = new TF2("f_smearspec", reas2, &ReaNeutrinoSpectrum::GetSmearedAbsNuSpectrum, E_Lower, E_Upper, E_LP, E_UP, 1, "ReaNeutrinoSpectrum", "GetSmearedAbsNuSpectrum");

    TH1D *h_NormalOrder = new TH1D("h_NormalOrder", "NormalOrderData", NumOfBins, E_LP, E_UP);
    f_smearspec->SetParameter(0, DefaultSinsq31[0]);
    

    //#pragma omp parallel for
    for (int i = 0; i < NumOfBins; i++)
    {
        COfBin = E_LP + (0.5 + (double)i) * BinWidth;
        Eres_sigma = sqrt(COfBin) * EnergyResolution;
        if((COfBin - intNUM * Eres_sigma)<E_Lower)
        {
            tSum = f_smearspec->Integral(E_Lower, COfBin + intNUM * Eres_sigma, (E_LP + (double)i * BinWidth), (E_LP + ((double)(i + 1)) * BinWidth));
        }
        else
        {
            tSum = f_smearspec->Integral(COfBin - intNUM * Eres_sigma, COfBin + intNUM * Eres_sigma, (E_LP + (double)i * BinWidth), (E_LP + ((double)(i + 1)) * BinWidth)); //,integralinterval);
        }
        h_NormalOrder->Fill(COfBin, tSum);
    }

    TFile *file_bkg = TFile::Open("../data/JunoBkg.root", "READ");
    TH1 *h_Acc = 0;    //Accidental bkg
    TH1 *h_Fn = 0;     //Fast neutron bkg
    TH1 *h_Li9 = 0;    //9Li8He bkg
    TH1 *h_AlphaN = 0; //alpha n bkg
    TH1 *h_GeoNu = 0;  //Geo-nus bkg
    file_bkg->GetObject("AccBkgHistogramAD", h_Acc);
    file_bkg->GetObject("FnBkgHistogramAD", h_Fn);
    file_bkg->GetObject("Li9BkgHistogramAD", h_Li9);
    file_bkg->GetObject("AlphaNBkgHistogramAD", h_AlphaN);
    file_bkg->GetObject("GeoNuHistogramAD", h_GeoNu);
    double sumbkg = 0;
    double tbkg[5];
    tbkg[0] = h_Acc->Integral();
    tbkg[1] = h_Fn->Integral();
    tbkg[2] = h_Li9->Integral();
    tbkg[3] = h_AlphaN->Integral();
    tbkg[4] = h_GeoNu->Integral();
    tSum = h_NormalOrder->Integral(); //total events num of signal
    h_Acc->Scale(tSum * bkgratio[0] / tbkg[0]);
    h_Fn->Scale(tSum * bkgratio[1] / tbkg[1]);
    h_Li9->Scale(tSum * bkgratio[2] / tbkg[2]);
    h_AlphaN->Scale(tSum * bkgratio[3] / tbkg[3]);
    h_GeoNu->Scale(tSum * bkgratio[4] / tbkg[4]);

    for (int i = 0; i < NumOfBins; i++)
    {

        COfBin = E_LP + (0.5 + (double)i) * BinWidth;
        tbkg[0] = h_Acc->GetBinContent(i + 1);
        tbkg[1] = h_Fn->GetBinContent(i + 1);
        tbkg[2] = h_Li9->GetBinContent(i + 1);
        tbkg[3] = h_AlphaN->GetBinContent(i + 1);
        tbkg[4] = h_GeoNu->GetBinContent(i + 1);
        sumbkg = 0;
        for (int j = 0; j < 4; j++)
        {
            sumbkg += (tbkg[j]);
        }
        h_NormalOrder->Fill(COfBin, sumbkg);
    }

    TH1D *h_InvertOrder = new TH1D("h_InvertOrder", "InvertOrderData", NumOfBins, E_LP, E_UP);
    f_smearspec->SetParameter(0, DefaultSinsq31[1]);
    

    for (int i = 0; i < NumOfBins; i++)
    {
        COfBin = E_LP + (0.5 + (double)i) * BinWidth;
        Eres_sigma = sqrt(COfBin) * EnergyResolution;
        if((COfBin - intNUM * Eres_sigma)<E_Lower)
        {
            tSum = f_smearspec->Integral(E_Lower, COfBin + intNUM * Eres_sigma, (E_LP + (double)i * BinWidth), (E_LP + ((double)(i + 1)) * BinWidth));
        }
        else
        {
            tSum = f_smearspec->Integral(COfBin - intNUM * Eres_sigma, COfBin + intNUM * Eres_sigma, (E_LP + (double)i * BinWidth), (E_LP + ((double)(i + 1)) * BinWidth)); //,integralinterval);
        }
        h_InvertOrder->Fill(COfBin, tSum);
    }
    tbkg[0] = h_Acc->Integral();
    tbkg[1] = h_Fn->Integral();
    tbkg[2] = h_Li9->Integral();
    tbkg[3] = h_AlphaN->Integral();
    tbkg[4] = h_GeoNu->Integral();
    tSum = h_InvertOrder->Integral(); //total events num of signal
    h_Acc->Scale(tSum * bkgratio[0] / tbkg[0]);
    h_Fn->Scale(tSum * bkgratio[1] / tbkg[1]);
    h_Li9->Scale(tSum * bkgratio[2] / tbkg[2]);
    h_AlphaN->Scale(tSum * bkgratio[3] / tbkg[3]);
    h_GeoNu->Scale(tSum * bkgratio[4] / tbkg[4]);
    for (int i = 0; i < NumOfBins; i++)
    {
        COfBin = E_LP + (0.5 + (double)i) * BinWidth;
        tbkg[0] = h_Acc->GetBinContent(i + 1);
        tbkg[1] = h_Fn->GetBinContent(i + 1);
        tbkg[2] = h_Li9->GetBinContent(i + 1);
        tbkg[3] = h_AlphaN->GetBinContent(i + 1);
        tbkg[4] = h_GeoNu->GetBinContent(i + 1);
        sumbkg = 0;
        for (int j = 0; j < 4; j++)
        {
            sumbkg += (tbkg[j]);
        }
        h_InvertOrder->Fill(COfBin, sumbkg);
    }

    TFile *file0 = TFile::Open("SoCallData.root", "RECREATE");
    gFile = file0; //shfit the default rootsystem
    h_NormalOrder->Write();
    //h_InvertOrder->Scale(h_NormalOrder->Integral() / h_InvertOrder->Integral()); //set same number of events for IO and NO
    h_InvertOrder->Write();
    h_Acc->Write();
    h_Fn->Write();
    h_Li9->Write();
    h_AlphaN->Write();
    h_GeoNu->Write();
    file0->Close();
    file_bkg->Close();
}

double CalculateDeltaChisqRea_Poisson(const double *pullparandvar, const double RUNTIME)
// pullparandvar:0-4:{correlated reactor uncertainty,
// uncorrelated r u,
// spectrum shape uncertainty,
// detector-related uncertainty,dmsq31}
{
    TH1::SetDefaultSumw2();
    double dmsq31 = pullparandvar[NumOfPullPar];
    TFile *file_readdata = TFile::Open("SoCallData.root", "READ");
    if (!file_readdata)
    {
        cerr << "ERROR: File \"SoCallData.root\" not found!" << endl;
    }
    TH1 *h1_NO = 0; //normal order "true data"
    TH1 *h2_IO = 0; //invert order "true data"
    file_readdata->GetObject("h_NormalOrder", h1_NO);
    file_readdata->GetObject("h_InvertOrder", h2_IO);
    //cout<<h1_NO->Integral()<<"  "<<h2_IO->Integral()<<endl;
    double Chisq_Rea = 0;
    double D_i = 0;
    double sumpull = 0, sumpullsq = 0;
    double TheoEvt[NumOfBins];

    ReaNeutrinoSpectrum *reas2 = new ReaNeutrinoSpectrum();
    reas2->SetRunTime_d(RUNTIME);
    reas2->SetOscillationParameters(parameterset);
    //TF2 * f_smearspec=new TF2("f_smearspec",SmearedEpromptSpectrum2D,E_LP,E_UP,E_LP,E_UP,2);
    TF2 *f_0 = new TF2("f_0", reas2, &ReaNeutrinoSpectrum::GetSmearedAbsNuSpectrum, E_Lower, E_Upper, E_LP, E_UP, 1, "ReaNeutrinoSpectrum", "GetSmearedAbsNuSpectrum");
    f_0->SetParameter(0, dmsq31);

    double tSum = 0;
    double COfBin = 0;

    for (int i = 0; i < NumOfBins; i++)
    {
        COfBin = E_LP + (0.5 + (double)i) * BinWidth;
        Eres_sigma = sqrt(COfBin) * EnergyResolution;
        if((COfBin - intNUM * Eres_sigma)<E_Lower)
            TheoEvt[i] = f_0->Integral(E_Lower, COfBin + intNUM * Eres_sigma, (E_LP + (double)i * BinWidth), (E_LP + ((double)(i + 1)) * BinWidth)); //,integralinterval);
        else
            TheoEvt[i] = f_0->Integral(COfBin - intNUM * Eres_sigma, COfBin + intNUM * Eres_sigma, (E_LP + (double)i * BinWidth), (E_LP + ((double)(i + 1)) * BinWidth));
        tSum += TheoEvt[i];
    }

    TH1 *h_Acc = 0;    //Accidental bkg
    TH1 *h_Fn = 0;     //Fast neutron bkg
    TH1 *h_Li9 = 0;    //9Li8He bkg
    TH1 *h_AlphaN = 0; //alpha n bkg
    TH1 *h_GeoNu = 0;  //Geo-nus bkg
    file_readdata->GetObject("AccBkgHistogramAD", h_Acc);
    file_readdata->GetObject("FnBkgHistogramAD", h_Fn);
    file_readdata->GetObject("Li9BkgHistogramAD", h_Li9);
    file_readdata->GetObject("AlphaNBkgHistogramAD", h_AlphaN);
    file_readdata->GetObject("GeoNuHistogramAD", h_GeoNu);
    double sumbkg = 0;
    double tbkg[5];

    //bkg normalizing
    // tbkg[0] = h_Acc->Integral();
    // tbkg[1] = h_Fn->Integral();
    // tbkg[2] = h_Li9->Integral();
    // tbkg[3] = h_AlphaN->Integral();
    // tbkg[4] = h_GeoNu->Integral();
    //tSum=h_NormalOrder->Integral();//total events num of signal
    // h_Acc->Scale(tSum * bkgratio[0] / tbkg[0]);
    // h_Fn->Scale(tSum * bkgratio[1] / tbkg[1]);
    // h_Li9->Scale(tSum * bkgratio[2] / tbkg[2]);
    // h_AlphaN->Scale(tSum * bkgratio[3] / tbkg[3]);
    // h_GeoNu->Scale(tSum * bkgratio[4] / tbkg[4]);
    tSum = 0;
    for (int i = 0; i < NumOfBins; i++)
    {
        tbkg[0] = h_Acc->GetBinContent(i + 1);
        tbkg[1] = h_Fn->GetBinContent(i + 1);
        tbkg[2] = h_Li9->GetBinContent(i + 1);
        tbkg[3] = h_AlphaN->GetBinContent(i + 1);
        tbkg[4] = h_GeoNu->GetBinContent(i + 1);
        sumbkg = 0;
        for (int j = 0; j < 4; j++)
        {
            sumbkg += (tbkg[j]);
        }
        TheoEvt[i] += sumbkg;
        tSum += TheoEvt[i];
    }
    // for (int i = 0; i < NumOfBins; i++)
    //     TheoEvt[i] *= (tSum / h1_NO->Integral()); //normalizing
    Ini_alpha_ik();                               // initialize the coefficient vector
    for (int j = 0; j < NumOfPullPar; j++)
    {
        sumpullsq += (pullparandvar[j]/errors_sigma[j] * pullparandvar[j]/errors_sigma[j]);
    }
    for (int i = 0; i < NumOfBins; i++)
    {
        if (dmsq31 > 0)
            D_i = h2_IO->GetBinContent(i + 1);
        else if (dmsq31 < 0)
            D_i = h1_NO->GetBinContent(i + 1);
        for (int j = 0; j < NumOfPullPar; j++)
            sumpull += (alpha_ik[i][j] * pullparandvar[j]);
        //cout<<TheoEvt[i]<<"  "<<D_i<<endl;
        TheoEvt[i] *= (1. + sumpull);
        Chisq_Rea += (2. * (TheoEvt[i] - D_i + D_i * TMath::Log(D_i / TheoEvt[i])));

        //Poisson chi^2 above, should be same as Gaussian Chi^2,
        //It should be Delta chi^2 here, but since the "data" was generated
        //by the same procedure as fit theory, one of the term in delta chi^2 is 0
    }
    Chisq_Rea += sumpullsq;

    file_readdata->Close();
    cout << "pallpar i: ";
    for (int i = 0; i < NumOfPullPar + 1; i++)
    {
        cout << "  " << pullparandvar[i] << "  ";
    }
    cout << Chisq_Rea << endl;
    f_0->Delete();
    delete reas2;
    return Chisq_Rea;
}

double wrappercalChi_Poisson(const double *pullparandvar)
{

    double Chisq_Rea = CalculateDeltaChisqRea_Poisson(pullparandvar, JunoRuntime);
    ofstream outfile;
    outfile.open("pullparandVar_minimum.txt", ios::app);
    for (int i = 0; i < NumOfPullPar + 1; i++)
    {
        outfile << "  " << pullparandvar[i] << "  ";
    }
    outfile << Chisq_Rea << endl;
    outfile.close();

    return Chisq_Rea;
}
double wrappercalChi_Gaussian(const double *pullparandvar)
{
    double Chisq_Rea = CalculateDeltaChisqRea_Gaussian(pullparandvar, JunoRuntime);
    ofstream outfile;
    outfile.open("pullparandVar_minimum.txt", ios::app);
    for (int i = 0; i < NumOfPullPar + 1; i++)
    {
        outfile << "  " << pullparandvar[i] << "  ";
    }
    outfile << Chisq_Rea << endl;
    outfile.close();

    return Chisq_Rea;
}

void MinimizeChisq(int randomSeed,int Chistyle)
{
    ROOT::Math::Minimizer *miniChi = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");
    //set tolerance , etc...
    miniChi->SetMaxFunctionCalls(100000); // for Minuit/Minuit2
    miniChi->SetMaxIterations(1000);      // for GSL
    miniChi->SetTolerance(0.001);
    miniChi->SetPrintLevel(4);
    //create function wrapper for minimizer
    //a IMultiGenFunction type
    
    ROOT::Math::Functor fP(&wrappercalChi_Poisson, (NumOfPullPar + 1));
    ROOT::Math::Functor fG(&wrappercalChi_Gaussian, (NumOfPullPar + 1));
    if(Chistyle==0)
        miniChi->SetFunction(fP);
    else
        miniChi->SetFunction(fG);

    double step[NumOfPullPar + 1] = {0.01, 0.01, 0.01, 0.01, 1.e-5};
    //starting point
    double variable[NumOfPullPar + 1] = {0., 0., 0., 0., (dmsq31_up+dmsq31_low)/2.};//BestFitdm31sq[0]};
    if (randomSeed >= 0)
    {
        TRandom3 r(randomSeed);
        variable[0] = r.Uniform(-1, 1);
        variable[1] = r.Uniform(-1, 1);
        variable[2] = r.Uniform(-1, 1);
        variable[3] = r.Uniform(-1, 1);
        variable[4] = r.Uniform(dmsq31_low, dmsq31_up);
        r.Delete();
    }
    
    // Set the free variables to be minimized !
    miniChi->SetVariable(0, "Xi0", variable[0], step[0]);    //,-1,1);
    miniChi->SetVariable(1, "Xi1", variable[1], step[1]);    //,-1,1);
    miniChi->SetVariable(2, "Xi2", variable[2], step[2]);    //,-1,1);
    miniChi->SetVariable(3, "Xi3", variable[3], step[3]);    //,-1,1);
    miniChi->SetVariable(4, "dmsq31", variable[4], step[4]); //,-2.6e-3, -2.1e-3);
    // do the minimization
    miniChi->Minimize();
    const double *xs = miniChi->X();
    for (int i = 0; i < NumOfPullPar + 1; i++)
        cout << "minimum point coor: " << i << "  " << xs[i] << endl;
    cout << "minimum is : " << miniChi->MinValue() << endl;
    ofstream outfile;
    outfile.open("minimum.txt"); //,ios::app);
    for (int i = 0; i < NumOfPullPar + 1; i++)
        outfile << xs[i] <<endl;
    outfile << miniChi->MinValue() << endl;
    outfile.close();
}

void Ini_alpha_ik()
{
    vector<double> a_k;
    double t_ki = 1.;
    for (int i = 0; i < NumOfPullPar; i++)
    {
        a_k.push_back(t_ki);
    }
    for (int i = 0; i < NumOfBins; i++)
    {
        alpha_ik.push_back(a_k);
    }
}

double CalculateDeltaChisqRea_Gaussian(const double *pullparandvar,const double RUNTIME)
{
    TH1::SetDefaultSumw2();
    double dmsq31 = pullparandvar[NumOfPullPar];
    TFile *file_readdata = TFile::Open("SoCallData.root", "READ");
    if (!file_readdata)
    {
        cerr << "ERROR: File \"SoCallData.root\" not found!" << endl;
    }
    TH1 *h1_NO = 0; //normal order "true data"
    TH1 *h2_IO = 0; //invert order "true data"
    file_readdata->GetObject("h_NormalOrder", h1_NO);
    file_readdata->GetObject("h_InvertOrder", h2_IO);
    //cout<<h1_NO->Integral()<<"  "<<h2_IO->Integral()<<endl;
    double Chisq_Rea = 0;
    double D_i = 0;
    double sumpull = 0, sumpullsq = 0;
    double TheoEvt[NumOfBins];

    ReaNeutrinoSpectrum *reas2 = new ReaNeutrinoSpectrum();
    reas2->SetRunTime_d(RUNTIME);
    reas2->SetOscillationParameters(parameterset);
    //TF2 * f_smearspec=new TF2("f_smearspec",SmearedEpromptSpectrum2D,E_LP,E_UP,E_LP,E_UP,2);
    TF2 *f_0 = new TF2("f_0", reas2, &ReaNeutrinoSpectrum::GetSmearedAbsNuSpectrum, E_Lower, E_UP, E_LP, E_UP, 1, "ReaNeutrinoSpectrum", "GetSmearedAbsNuSpectrum");
    f_0->SetParameter(0, dmsq31);

    double tSum = 0;
    double COfBin = 0;

    for (int i = 0; i < NumOfBins; i++)
    {
        COfBin = E_LP + (0.5 + (double)i) * BinWidth;
        Eres_sigma = sqrt(COfBin) * EnergyResolution;
        if((COfBin - intNUM * Eres_sigma)<E_Lower)
            TheoEvt[i] = f_0->Integral(E_Lower, COfBin + intNUM * Eres_sigma, (E_LP + (double)i * BinWidth), (E_LP + ((double)(i + 1)) * BinWidth)); //,integralinterval);
        else
            TheoEvt[i] = f_0->Integral(COfBin - intNUM * Eres_sigma, COfBin + intNUM * Eres_sigma, (E_LP + (double)i * BinWidth), (E_LP + ((double)(i + 1)) * BinWidth));
        tSum += TheoEvt[i];
    }

    TH1 *h_Acc = 0;    //Accidental bkg
    TH1 *h_Fn = 0;     //Fast neutron bkg
    TH1 *h_Li9 = 0;    //9Li8He bkg
    TH1 *h_AlphaN = 0; //alpha n bkg
    TH1 *h_GeoNu = 0;  //Geo-nus bkg
    file_readdata->GetObject("AccBkgHistogramAD", h_Acc);
    file_readdata->GetObject("FnBkgHistogramAD", h_Fn);
    file_readdata->GetObject("Li9BkgHistogramAD", h_Li9);
    file_readdata->GetObject("AlphaNBkgHistogramAD", h_AlphaN);
    file_readdata->GetObject("GeoNuHistogramAD", h_GeoNu);
    double sumbkg = 0;
    double tbkg[5];
    tbkg[0] = h_Acc->Integral();
    tbkg[1] = h_Fn->Integral();
    tbkg[2] = h_Li9->Integral();
    tbkg[3] = h_AlphaN->Integral();
    tbkg[4] = h_GeoNu->Integral();
    //tSum=h_NormalOrder->Integral();//total events num of signal
    h_Acc->Scale(tSum * bkgratio[0] / tbkg[0]);
    h_Fn->Scale(tSum * bkgratio[1] / tbkg[1]);
    h_Li9->Scale(tSum * bkgratio[2] / tbkg[2]);
    h_AlphaN->Scale(tSum * bkgratio[3] / tbkg[3]);
    h_GeoNu->Scale(tSum * bkgratio[4] / tbkg[4]);
    tSum = 0;
    for (int i = 0; i < NumOfBins; i++)
    {
        tbkg[0] = h_Acc->GetBinContent(i + 1);
        tbkg[1] = h_Fn->GetBinContent(i + 1);
        tbkg[2] = h_Li9->GetBinContent(i + 1);
        tbkg[3] = h_AlphaN->GetBinContent(i + 1);
        tbkg[4] = h_GeoNu->GetBinContent(i + 1);
        sumbkg = 0;
        for (int j = 0; j < 4; j++)
        {
            sumbkg += (tbkg[j]);
        }
        TheoEvt[i] += sumbkg;
        tSum += TheoEvt[i];
    }
    // for (int i = 0; i < NumOfBins; i++)
        // TheoEvt[i] *= (tSum / h1_NO->Integral()); //normalizing
    Ini_alpha_ik();                               // initialize the coefficient vector
    for (int j = 0; j < NumOfPullPar; j++)
    {
        sumpullsq += (pullparandvar[j]/errors_sigma[j] * pullparandvar[j]/errors_sigma[j]);
    }
    for (int i = 0; i < NumOfBins; i++)
    {
        if (dmsq31 > 0)
            D_i = h2_IO->GetBinContent(i + 1);
        else if (dmsq31 < 0)
            D_i = h1_NO->GetBinContent(i + 1);
        for (int j = 0; j < NumOfPullPar; j++)
            sumpull += (alpha_ik[i][j] * pullparandvar[j]);
        //cout<<TheoEvt[i]<<"  "<<D_i<<endl;
        TheoEvt[i] *= (1. + sumpull);
        Chisq_Rea += ((TheoEvt[i] - D_i)*(TheoEvt[i] - D_i) / D_i);
        //cout<<Chisq_Rea<<endl;
        //Gaussian chi^2 above, should be same as Poisson Chi^2,
        //It should be Delta chi^2 here, but since the "data" was generated
        //by the same procedure as fit theory, one of the term in delta chi^2 is 0
    }
    Chisq_Rea += sumpullsq;
    file_readdata->Close();
    cout << "pallpar i: ";
    for (int i = 0; i < NumOfPullPar + 1; i++)
    {
        cout << "  " << pullparandvar[i] << "  ";
    }
    cout << Chisq_Rea << endl;
    f_0->Delete();
    delete reas2;
    return Chisq_Rea;
}

double E_0[1], par_wrapper[1], par_for_gaus[2]; //global variable for lambda function
ReaNeutrinoSpectrum *reas_smear = new ReaNeutrinoSpectrum();
double SmearedEpromptSpectrum1(double *E_pr, double *par)
//par:dmsq31, runtime_d
{

    reas_smear->SetRunTime_d(par[1]);
    GaussLegendreIntegrator integrator(1000);
    double r;
    par_wrapper[0] = par[0];
    par_for_gaus[0] = E_pr[0];
    par_for_gaus[1] = sqrt(E_pr[0]) * EnergyResolution;
    r = integrator.DoIntegral(E_LP * 0.9, E_UP, [](double x) -> double {
        E_0[0]=x;
        double temp;
        temp=reas_smear->GetPromptEnergySpectrum(E_0,par_wrapper);
        return (temp*mygaussian(E_0,par_for_gaus)); });
    return r;
}
double SmearedEpromptSpectrumFFT(double *E_pr, double *par)
{
    Eres_mu = 0.;
    Eres_sigma = sqrt(E_pr[0]) * EnergyResolution;
    reas_smear->SetRunTime_d(par[1]);
    par_wrapper[0] = par[0];
    Convolution *EprompCfft = new Convolution(-20., 20, E_LP * 0.95, E_UP,
                                              [](double E) -> double {
                                                  E_0[0] = E;
                                                  double temp;
                                                  temp = reas_smear->GetPromptEnergySpectrum(E_0, par_wrapper);
                                                  return temp;
                                              },
                                              true, 1000);
    return EprompCfft->DoConvolutionFFT(E_pr, par);
}

double SmearedEpromptSpectrum2D(double *Ex, double *par)
//Ex:E_pr,Evis; par: dmsq31
{
    ReaNeutrinoSpectrum *res2D = new ReaNeutrinoSpectrum();
    res2D->SetRunTime_d(365 * 4.);
    double a = res2D->GetPromptEnergySpectrum(&Ex[0], &par[0]);
    double b = 1. / (sqrt(2. * TMath::Pi() * Ex[1]) * EnergyResolution);
    double c = TMath::Exp(-0.5 * TMath::Power((Ex[0] - Ex[1]) / (sqrt(Ex[1]) * EnergyResolution), 2));
    //if(Ex[1]<E_LP+BinWidth && Ex[0]<1.82)
    //cout<<rsm<<"  0  "<<Ex[0]<<" 1 "<<Ex[1]<<endl;
    delete res2D;
    return (a * b * c);
}
