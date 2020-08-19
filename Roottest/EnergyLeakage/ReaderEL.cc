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
void AddFile2TChain(TChain &tree, int NFiles = 1)
{
    for (int i = 10000; i < 10000 + NFiles; i++)
    {
        tree.Add(Form("%s%d.root", HXD, i));
    }
}

int ReaderEL()
{
    TChain evt("evt");
    TChain prmtrkdep("prmtrkdep");
    TChain geninfo("geninfo");
    TChain nCapture("nCapture");
    int NFiles = 5;
    AddFile2TChain(evt, NFiles);
    AddFile2TChain(prmtrkdep, NFiles);
    AddFile2TChain(geninfo, NFiles);
    AddFile2TChain(nCapture, NFiles);
    evt.AddFriend("prmtrkdep");
    evt.AddFriend("geninfo");
    evt.AddFriend("nCapture");
    evt.Process("GetPE2R3.C+", "prmtrkdep geninfo nCapture");

    return 0;
}