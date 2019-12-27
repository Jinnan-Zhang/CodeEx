#include <iostream>
#include <TFile.h>
#include <TH1.h>
#include <math.h>

double E_low = 1.806;
double E_up = 10;
const int BinNUM = 500;
using namespace std;
double Sfunc(double x);

int NonLinear()
{
    TFile *fl = TFile::Open("JunoNonL.root", "RECREATE");
    TH1D *h1 = new TH1D("JunoNonL", "Nonlinear data", BinNUM, E_low, E_up);
    double xi, yi;
    double width = (E_up - E_low) / BinNUM;
    for (int i = 0; i < BinNUM; i++)
    {
        xi = E_low + i * width;
        yi = Sfunc(xi);
        h1->SetBinContent(i + 1, yi);
    }
    h1->Draw();
    h1->Write();
    // fl->Close();
    return 0;
}
double Sfunc(double x)
{
    double K = 0.15;
    double a = 1;
    double b = 0.5;
    double inp = 0.9;
    return inp + K / (1 + exp(a - b * x));
}