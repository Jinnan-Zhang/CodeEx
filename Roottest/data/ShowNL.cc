#include <TFile.h>
#include <TGraph.h>
#include <iostream>
#include <TH1.h>
#include<TLegend.h>
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
    TFile *ff_h = TFile::Open("JunoFullNL.root", "RECREATE");
    // TFile *ff_h = TFile::Open("JunoFullNL.root", "READ");
    TH1D *h1 = new TH1D("positronFullNL", "Positron Full NL", NBINS, E_LP, E_UP);
    int nform = 0;
    TH1D *h2 = new TH1D(Form("NLpull%d", nform++), "Positron Full NL", NBINS, E_LP, E_UP);
    TH1D *h3 = new TH1D(Form("NLpull%d", nform++), "Positron Full NL", NBINS, E_LP, E_UP);
    TH1D *h4 = new TH1D(Form("NLpull%d", nform++), "Positron Full NL", NBINS, E_LP, E_UP);
    TH1D *h5 = new TH1D(Form("NLpull%d", nform++), "Positron Full NL", NBINS, E_LP, E_UP);

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
    TGraph *g1 = 0;
    TGraph *g2 = 0;
    TGraph *g3 = 0;
    TGraph *g4 = 0;

    ff->GetObject("positronFullNL", g0);
    nform = 0;
    ff->GetObject(Form("pull%d", nform++), g1);
    ff->GetObject(Form("pull%d", nform++), g2);
    ff->GetObject(Form("pull%d", nform++), g3);
    ff->GetObject(Form("pull%d", nform++), g4);

    // start=clock();
    double c(0);
    for (int i = 0; i < NBINS; i++)
    {
        c = E_LP + i * (BINw);
        h1->SetBinContent(i + 1, g0->Eval(c));
        h2->SetBinContent(i + 1, g1->Eval(c));
        h3->SetBinContent(i + 1, g2->Eval(c));
        h4->SetBinContent(i + 1, g3->Eval(c));
        h5->SetBinContent(i + 1, g4->Eval(c));
    }
    ff_h->cd();

    h1->Write();
    h2->Write();
    h3->Write();
    h4->Write();
    h5->Write();

    h2->SetLineColor(kBlue);
    h3->SetLineColor(kRed);
    h4->SetLineColor(kGreen);
    h5->SetLineColor(kYellow);
    
    h1->SetXTitle("E(MeV)");
    h1->Draw();
    h2->Draw("SAME");
    h3->Draw("SAME");
    h4->Draw("SAME");
    h5->Draw("SAME");
    TLegend leg(3,2);
    leg.AddEntry(h1,"Nominal");
    nform=0;
    leg.AddEntry(h2,Form("pull%d", nform++));
    leg.AddEntry(h3,Form("pull%d", nform++));
    leg.AddEntry(h4,Form("pull%d", nform++));
    leg.AddEntry(h5,Form("pull%d", nform++));
    leg.DrawClone("SAME");

    ff_h->Close();
    // TH1D *h2 = 0;
    // ff_h->GetObject("positronFullNL", h2);
    // h2->SetLineColor(kRed);
    // h2->Draw();
    // g0->Draw("SAME");

    // finish=clock();
    // printf("%f seconds\n", (double)(finish - start) / 1000.);

    // g0->Draw();
    return 0;
}