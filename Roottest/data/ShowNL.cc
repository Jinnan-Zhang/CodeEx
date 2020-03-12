#include <TFile.h>
#include <TGraph.h>
#include <iostream>
#include <TH1.h>
// using std::cout, std::endl;
#include <time.h>
double E_Lower = 1.807; //energy threshold of IBD
double E_Upper = 12.;   //energy cut for neutrino energy
double E_LP = 1.022;    //E_Lower-0.78233108;
double E_UP = E_Upper - 0.78233108;
int NBINS(20000);
double BINw((E_UP - E_LP) / NBINS);

int ShowNL()
{
    TH1::AddDirectory(false);
    TFile *ff = TFile::Open("energymodel_Apr2018_newE.root", "READ");
    // TFile *ff_h = TFile::Open("JunoFullNL.root", "RECREATE");
    TFile *ff_h = TFile::Open("JunoFullNL.root", "READ");
    // TH1D *h1 = new TH1D("positronFullNL", "Positron Full NL", NBINS, E_LP, E_UP);
    // ff_h->GetObject("h1",h1);

    // clock_t start, finish;
    // start=clock();
    // for(int i=0;i<1e7;i++)
    // {
    //     h1->Interpolate(4);
    // }
    // finish=clock();
    // printf( "%f seconds\n",(double)(finish - start)/1000.);

    TGraph *g0 = 0;
    ff->GetObject("positronFullNL", g0);
    // start=clock();
    // double c(0);
    // for (int i = 0; i < NBINS; i++)
    // {
    //     c = E_LP + i * (BINw);
    //     h1->SetBinContent(i+1,g0->Eval(c));
    // }
    // h1->Write();
    // ff_h->cd();
    // ff_h->Close();
    TH1D *h2 = 0;
    ff_h->GetObject("positronFullNL", h2);
    h2->SetLineColor(kRed);
    h2->Draw();
    g0->Draw("SAME");

    // finish=clock();
    // printf("%f seconds\n", (double)(finish - start) / 1000.);

    // g0->Draw();
    return 0;
}