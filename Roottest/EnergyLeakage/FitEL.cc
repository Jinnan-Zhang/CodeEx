#include <TFile.h>
#include <TH1.h>
#include <TF1.h>

TF1 *f_EL=new TF1("f_EL","[0]+[1]*TMath::Exp([2]+[3]*x)+[4]*x",0,2);

int FitEL()
{
    TFile *ff_EL=TFile::Open("JUNOEnergyLeakage.root","READ");
    TH1 *h_EL=(TH1*)ff_EL->Get("Eratio");
    f_EL->SetParameters(0,);

}