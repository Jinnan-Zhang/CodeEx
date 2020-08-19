#include <math.h>
#include <TF1.h>
#include <TH1.h>
#include <iostream>
#include <TCanvas.h>
#include <TLegend.h>

using namespace std;

double E_Lower = 0.8; //energy threshold of IBD
double E_Upper = 16.; //energy cut for neutrino energy
double simpleEres(double *Es, double *par);
double ThreeEres(double *Es, double *par);
double a_res = 2.62 ; //stochastic term a/sqrt(E)
double b_res = 0.73 ; //constant term b
double c_res = 1.38 ; //noise term c/E
int Nbins = 20000;
//purpose: to see the three factors energy resolution function
//and one factor resolution model for E_Cal
int EresFea()
{
    // TF1 *f0 = new TF1("f0", simpleEres, E_Lower, E_Upper, 0);
    TH1D *f0 = new TH1D("f0", "", Nbins, E_Lower, E_Upper);
    // TF1 *f1 = new TF1("f1", ThreeEres, E_Lower, E_Upper, 0);
    TH1D *f1 = new TH1D("f1", "", Nbins, E_Lower, E_Upper);
    double w = f0->GetBinWidth(1);
    double xe(0);
    for (int i = 0; i < Nbins; i++)
    {
        xe = E_Lower + i * w;
        f0->SetBinContent(i + 1, simpleEres(&xe, &xe));
        f1->SetBinContent(i + 1, ThreeEres(&xe, &xe));
    }
    f0->SetLineColor(kRed);
    f1->SetLineColor(kBlue);
    f0->SetLineWidth(3.5);
    f1->SetLineWidth(3.5);
    f1->SetYTitle("#sigma (MeV)");
    f1->SetXTitle("E (MeV)");
    f0->SetYTitle("#sigma (MeV)");
    f0->SetXTitle("E (MeV)");
    f1->Draw("");

    f0->Draw("SAME");

    TLegend leg(20, 30);
    leg.AddEntry(f0, "#sigma/#sqrt{E}=3%");
    leg.AddEntry(f1, Form("#sigma/E=#sqrt{(%0.3f/#sqrt{E})^{2}+%0.3f^{2}+(%0.3f/E)^{2}} %%", a_res, b_res, c_res));
    leg.DrawClone("SAME");
    // c1->Draw();
    return 0;
}

double simpleEres(double *Es, double *par)
{
    double sigma;
    double E_vis(Es[0]);
    sigma = sqrt(E_vis) * 0.03;
    return sigma;
}
double ThreeEres(double *Es, double *par)
{
    double E_vis = Es[0];

    double sigma = E_vis * sqrt(a_res * a_res / E_vis + b_res * b_res + c_res * c_res / (E_vis * E_vis))/100;
    return sigma;
}

//目的：查看能量分辨函数的特征