#include <math.h>
#include <TF1.h>
#include <TH1.h>
#include <iostream>
#include <TCanvas.h>

using namespace std;

double E_Lower = 1; //energy threshold of IBD
double E_Upper = 10.;    //energy cut for neutrino energy
double simpleEres(double *Es, double *par);
double ThreeEres(double *Es, double *par);

//purpose: to see the three factors energy resolution function
//and one factor resolution model for E_Cal
int EresFea()
{
    TF1 *f0 = new TF1("f0", simpleEres, E_Lower, E_Upper, 1);
    TF1 *f1 = new TF1("f1", ThreeEres, E_Lower, E_Upper, 0);
    f0->SetParameter(0, 0.03);
    // f1->SetParameters(1, 1, 1);
    f0->SetLineColor(kRed);
    // f1->SetLineColor(kBlue);
    // TCanvas *c1 = new TCanvas("c1", "multipads", 900, 700);
    // c1->Divide(2, 1);
    // c1->cd(1);
    // f0->Draw();
    // c1->cd(2);
    f1->Draw();
    // c1->Draw();
    return 0;
}

double simpleEres(double *Es, double *par)
{
    double sigma;
    double res;
    // = par[0];
    res = sqrt(Es[0]);
    return par[0];
}
double ThreeEres(double *Es, double *par)
{
    double E_vis=Es[0];
    double a_res = 3.;  //stochastic term a/sqrt(E)
    double b_res = 0.7; //constant term b
    double c_res = 0;    //noise term c/E
    return sqrt(a_res * a_res / E_vis + b_res * b_res + c_res * c_res / (E_vis * E_vis));
}

//目的：查看能量分辨函数的特征