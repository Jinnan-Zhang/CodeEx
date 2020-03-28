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

int ELout()
{
    // TChain tE_vis("evt");
    TChain tE_vis("prmtrkdep");
    TChain tE_true("geninfo");
    for (int nn = 10000; nn < 10999; nn++)
    {
        tE_vis.Add(Form("%s%d.root", HXD, nn));
        tE_true.Add(Form("%s%d.root", HXD, nn));
    }
    // tE_vis.Add(HXD2);
    // tE_true.Add(HXD1);
    // tE_true.Add(HXD2);
    // tE_vis.MakeSelector("E_vis_r");

    tE_vis.SetBranchStatus("*", 0);
    tE_true.SetBranchStatus("*", 0);
    int nPhotons;
    float E_dep;
    // tE_vis.SetBranchStatus("nPhotons", 1);
    // tE_vis.SetBranchAddress("nPhotons", &nPhotons);
    tE_vis.SetBranchStatus("edep", 1);
    tE_vis.SetBranchAddress("edep", &E_dep);

    int PDGid[2];
    float Px[2], Py[2], Pz[2];
    tE_true.SetBranchStatus("InitPDGID", 1);
    tE_true.SetBranchStatus("InitPX", 1);
    tE_true.SetBranchAddress("InitPDGID", &PDGid);
    tE_true.SetBranchAddress("InitPX", &Px);
    tE_true.SetBranchAddress("InitPZ", &Py);
    tE_true.SetBranchAddress("InitPY", &Pz);

    double E_true(0), E_vis(0);
    // TH1D *h_true = new TH1D("E_True", "True Eernergy",NBiny, Ran_vis[0], Ran_vis[1]);
    // TH1D *h_vis = new TH1D("E_vis", "Visible Eernergy", NBinx, Ran_true[0], Ran_true[1]);
    // TH2D *h_el = new TH2D("EnergyProfile", "Simulation", NBinx, Ran_true[0], Ran_true[1], NBiny, Ran_vis[0], Ran_vis[1]);
    // h_el->SetXTitle("True Energy (MeV)");
    // h_el->SetYTitle("Visible Energy(nPhotons/1200)");
    // h_el->SetYTitle("Deposited Energy(MeV)");
    // h_vis->SetXTitle("E (MeV)");
    TH1D *h_ra = new TH1D("Eratio", "", 200, 0.6, 1.1);
    double E_ratio(0);
    for (int i = 0; i < tE_vis.GetEntries(); i++)
    {
        tE_vis.GetEntry(i);
        tE_true.GetEntry(i);
        E_true = TMath::Sqrt(Px[0] * Px[0] + Py[0] * Py[0] + Pz[0] * Pz[0] + M_electron_sq) + M_e;
        // if ( E_dep < E_true)
        // {
            E_ratio = E_dep / E_true;
            h_ra->Fill(E_ratio, 1);
            // printf("which: %0.15f\n", E_ratio);
            // h_vis->Fill(E_true, E_ratio);
        // }
        // h_true->Fill(E_true);

        // E_vis = nPhotons / LightYeild - n_capture;
        // h_el->Fill(E_true, E_vis);
        // h_el->Fill(E_true, E_dep);

        // printf("this entry: %e\n", E_vis);
        // h_vis->Fill(E_vis);
    }
    TFile *ff_EL = TFile::Open("JUNOEnergyLeakage.root", "RECREATE");
    ff_EL->cd();
    // h_true->Write();
    // h_vis->Write();
    // h_el->Write();
    h_ra->Write();

    ff_EL->Close();

    return 0;
}