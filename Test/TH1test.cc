#include <TH1.h>
#include <TFile.h>
#include <iostream>

using namespace std;

void changeit(TH1 * h1,int n);
int TH1test()
{
    TH1D *hh=new TH1D("hh","hh",50,-10,10);
    hh->FillRandom("gaus",20);

    hh->Draw();
    changeit(hh,10);
    hh->SetLineColor(kGreen);
    hh->Draw("SAME");
    return 0;
}
void changeit(TH1 *h1,int n)
{
    TFile *f1=TFile::Open("f.root","RECREATE");
    for(int i=0;i<n;i++)
        h1->Fill(1);
    h1->Write();
    f1->Close();
}