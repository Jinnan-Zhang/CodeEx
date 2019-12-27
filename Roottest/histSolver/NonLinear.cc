#include <iostream>
#include <TFile.h>
#include <TH1.h>

double E_low = 1.806;
double E_up = 10;
using namespace std;

int NonLinear()
{
    TFile *fl = TFile::Open("JunoNonL.root", "RECREATE");
    TH1D *h1 = new TH1D("JunoNonL", "Nonlinear data", 200, )
}