#include <tFCN.h>
#include <TH1.h>
#include <TCanvas.h>

//* @param x[0]: x
double GetXsq(double *x)
{
    return x[0] * x[0] + 1;
}

void ShowTH1()
{
    TH1 *h0 = new TH1D("h0", "", 100, -10, 10);
    h0->FillRandom("gaus",10000);
    TCanvas c0;
    h0->Draw();
    c0.SaveAs("th.png");
}