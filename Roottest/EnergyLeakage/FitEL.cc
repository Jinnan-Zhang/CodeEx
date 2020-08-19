#include <TFile.h>
#include <TH1.h>
#include <TF1.h>
#include <TLegend.h>
#include <iostream>
#include<TROOT.h>
using namespace std;

TF1 *f_EL = new TF1("f_EL", "[0]+[1]*TMath::Exp([2]*x*x+[3]*x+[4])", 0, 1);

int FitEL()
{
    TFile *ff_EL = TFile::Open("JUNOEnergyLeakage.root", "READ");
    TH1 *h_EL = (TH1 *)ff_EL->Get("Eratio");
    f_EL->SetParameters(0,1,3.95,-1.17,-5.6);
    TH1D *h_dat=new TH1D("data","",390,0.1,0.998);
    for (int i = 0; i < h_dat->GetNbinsX(); i++)
    {
        // cout << h_EL->GetBinCenter(i + 1) << "  " << h_EL->GetBinContent(i + 1) << endl;
        h_dat->SetBinContent(i+1,h_EL->GetBinContent(i+1));
    }
    h_dat->SetLineColor(kRed);
    // h_dat->Fit(f_EL);
    h_EL->Draw("CO");
    gPad->SetLogy();
    TLegend leg0(1,0.5);
    leg0.AddEntry(f_EL,"Fit function");
    leg0.AddEntry(h_dat,"Data");
    // leg0.DrawClone("SAME");

    return 0;
}