#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TROOT.h>
#include <TTreeReaderArray.h>
#include <TBranch.h>
#include <iostream>
#define HXD1 "/junofs/users/huangx/production/J19v1r0-Pre3bk/IBD/uniform/IBD/detsim/user-detsim-10939.root"
#define HXD2 "/junofs/users/huangx/production/J19v1r0-Pre3bk/IBD/uniform/IBD/detsim/user-detsim-10938.root"

using namespace std;

int ELout()
{
    TChain tE_vis("evt");
    TChain tE_true("geninfo");
    tE_vis.Add(HXD1);
    tE_vis.Add(HXD2);
    tE_true.Add(HXD1);
    tE_true.Add(HXD2);
    
    // tE_vis.MakeSelector("E_vis_r");

    return 0;
}