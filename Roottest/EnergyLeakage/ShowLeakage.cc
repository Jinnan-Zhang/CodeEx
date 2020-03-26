#include <TH1.h>
#include <TH2.h>
#include <iostream>
#include <TFile.h>

double Ran_vis[2] = {0, 13};
double Ran_true[2] = {0, 13};
int NBinx = 400;
int NBiny = 400;
using namespace std;

int ShowLeakage()
{
    TFile *ff_el = TFile::Open("JUNOEnergyLeakage.root", "READ");
    TH2 *h_source = (TH2 *)ff_el->Get("EnergyProfile");
    TH1D *h_ra = new TH1D("Y2X", "",NBinx,Ran_true[0],Ran_true[1]);
    for(int i=0;i<NBinx;i++)
    {
        for(int j=0;j<NBinx;j++)
        {
            
        }
    }

}