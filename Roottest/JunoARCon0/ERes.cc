//目的：弄清楚能量分辨模型如何构建
#include <TChain.h>
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

int ERes()
{
    TChain t_evt("evt");
    t_evt.Add((char *)HXD1);
    // t_evt.MakeSelector("EvtSelector");
    t_evt.Process("EvtSelector.C");
    // int nPhotons = 0;
    // t_evt.SetBranchAddress("nPhotons", &nPhotons);
    // for (int i = 0; i < t_evt.GetEntries(); i++)
    // {
    //     t_evt.GetEntry(i);
    //     printf("nPhotons: %d\n", nPhotons);
    // }

    return 0;
}