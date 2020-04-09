#include <TChain.h>
#include <TTree.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TROOT.h>
#include <TTreeReaderArray.h>
#include <TBranch.h>
#include <TH1.h>
#include <TH2.h>
#include <TMath.h>
#include <cmath>
#include <iostream>
#define HXD1 "/junofs/users/huangx/production/J19v1r0-Pre3bk/IBD/uniform/IBD/detsim/user-detsim-10939.root"
#define HXD2 "/junofs/users/huangx/production/J19v1r0-Pre3bk/IBD/uniform/IBD/detsim/user-detsim-10938.root"
#define HXD "/junofs/users/huangx/production/J19v1r0-Pre3bk/IBD/uniform/IBD/detsim/user-detsim-"

double M_electron_sq = 0.26111993;
double M_e = 0.51099895;
double n_capture = 2.2; //MeV
double LightYeild = 1200.;
using namespace std;

double Ran_vis[2] = {0, 13};
double Ran_true[2] = {0, 13};
int NBinx = 400;
int NBiny = 400;

int ReaderEL()
{
    TH1::AddDirectory(false);
    // TFile *ff_LY = TFile::Open((char *)HXD1, "READ");
    // TH2 *h_LY=(TH2D*)ff_LY->Get("EnergyProfile");
    TChain *evt = new TChain("evt");
    // (TTree *)ff_LY->Get("evt");
    for (int nn = 10000; nn < 10001; nn++)
    {
        evt->Add(Form("%s%d.root", HXD, nn));
    }
    evt->SetBranchStatus("*", 0);
    int totalPE(0);
    int nPhotons(0);
    evt->SetBranchStatus("totalPE", 1);
    evt->SetBranchAddress("totalPE", &totalPE);
    // evt->SetBranchStatus("nPhotons", 1);
    // evt->SetBranchAddress("nPhotons", &nPhotons);
    // evt->SetBranchAddress("nPhotons", &nPhotons);
    evt->SetBranchStatus("hitTime", 1);

    // for (int i = 0; i < 1; i++)
    // {
    int i = 19;
    double *hitTime;
    evt->SetBranchAddress("hitTime", hitTime);
    evt->GetEntry(i);
    for (int j = 0; j < totalPE; j++)
    {
        if (hitTime[j] > 40000)
            printf("totalPE:%d\t hitTime:%f\n", totalPE, hitTime[j]);
    }
    // if (nPhotons != totalPE)
    // {
    //     printf("totalPE:%d\tnPhotons:%d\n", totalPE, nPhotons);
    // }
    // }

    return 0;
}