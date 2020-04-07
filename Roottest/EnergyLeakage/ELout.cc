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
#include <TVector3.h>
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

double Ran_x[2] = {0, 5300};
double Ran_y[2] = {-1, 1};
int NBinx = 50;
int NBiny = 20;

int ELout()
{
    TChain tE_vis("evt");
    // TChain tE_vis("prmtrkdep");
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
    // float E_dep[2], edepX[2], edepY[2], edepZ[2];
    float edep;
    tE_vis.SetBranchStatus("nPhotons", 1);
    tE_vis.SetBranchAddress("nPhotons", &nPhotons);
    tE_vis.SetBranchStatus("edep", 1);
    tE_vis.SetBranchAddress("edep", &edep);
    // tE_vis.SetBranchStatus("edepX", 1);
    // tE_vis.SetBranchAddress("edepX", &edepX);
    // tE_vis.SetBranchStatus("edepY", 1);
    // tE_vis.SetBranchAddress("edepY", &edepY);
    // tE_vis.SetBranchStatus("edepZ", 1);
    // tE_vis.SetBranchAddress("edepZ", &edepZ);

    // int PDGid[2];
    // float Px[2], Py[2], Pz[2];
    float InitX[2], InitY[2], InitZ[2];
    // tE_true.SetBranchStatus("InitPDGID", 1);
    // tE_true.SetBranchStatus("InitPX", 1);
    tE_true.SetBranchStatus("InitX", 1);
    tE_true.SetBranchStatus("InitY", 1);
    tE_true.SetBranchStatus("InitZ", 1);
    // tE_true.SetBranchAddress("InitPDGID", &PDGid);
    // tE_true.SetBranchAddress("InitPX", &Px);
    // tE_true.SetBranchAddress("InitPZ", &Py);
    // tE_true.SetBranchAddress("InitPY", &Pz);
    tE_true.SetBranchAddress("InitX", &InitX);
    tE_true.SetBranchAddress("InitY", &InitY);
    tE_true.SetBranchAddress("InitZ", &InitZ);

    double E_true(0), E_vis(0);
    // TH1D *h_true = new TH1D("E_True", "True Eernergy",NBiny, Ran_x[0], Ran_x[1]);
    // TH1D *h_vis = new TH1D("E_vis", "Visible Eernergy", NBinx, Ran_y[0], Ran_y[1]);
    TH2F *h_ep = new TH2F("EnergyProfile", "Simulation", NBinx, Ran_x[0], Ran_x[1], NBiny, Ran_y[0], Ran_y[1]);
    h_ep->SetXTitle("R^{3} (m^{3})");
    // h_ep->SetYTitle("nPhotons/MeV");
    h_ep->SetYTitle("cos#theta");
    // h_ep->SetYTitle("Deposited Energy(MeV)");
    // h_vis->SetXTitle("E (MeV)");
    // TH1D *h_ra = new TH1D("Eratio", "", 400, 0.1, 1.01);
    // h_ra->SetXTitle("E_{dep}/E_{true}");
    // TH2D *h_ra2R = new TH2D("ratio2R", "", NBinx, 0, 18, NBiny, 0, 1.01);
    // h_ra2R->SetYTitle("E_{dep}/E_{true}");
    // h_ra2R->SetXTitle("");
    double E_ratio(0), R_cubic(0);
    double Photon2edep(0), Costheta(0);
    double SE_true(0), SE_dep(0);
    // int ELnum(0), Tnum(0);
    int TotalBIN = h_ep->GetSize();
    int BinArray[TotalBIN];
    float BinValue[TotalBIN];
    for (int i = 0; i < TotalBIN; i++)
    {
        BinArray[i] = 0;
        BinValue[i] = 0;
    }
    int ithBIN(0);
    for (int i = 0; i < tE_vis.GetEntries(); i++)
    {
        tE_vis.GetEntry(i);
        tE_true.GetEntry(i);
        // E_true = TMath::Sqrt(Px[0] * Px[0] + Py[0] * Py[0] + Pz[0] * Pz[0] + M_electron_sq) + M_e;
        // if ( E_dep < E_true)
        // {
        // E_ratio = E_dep[0] / E_true;
        // R_cubic = sqrt(edepX[0] * edepX[0] + edepY[0] * edepY[0] + edepZ[0] * edepZ[0]) / 1000.; //to meter
        // h_ra2R->Fill(R_cubic, E_ratio);
        // R_cubic = pow((InitX[0] * InitX[0] + InitY[0] * InitY[0] + InitZ[0] * InitZ[0]), 1.5) / 1e9;
        TVector3 EvtPos(InitX[0] / 1e3, InitY[0] / 1e3, InitZ[0] / 1e3);
        Photon2edep = nPhotons / edep;
        R_cubic = pow(EvtPos.Mag2(), 1.5);
        Costheta = EvtPos.CosTheta();
        // h_ep->Fill(R_cubic, Costheta, Photon2edep);
        // h_ep->Fill(R_cubic, Costheta);
        ithBIN = h_ep->Fill(R_cubic, Costheta, Photon2edep);
        // ithBIN = h_ep->FindBin(R_cubic, Costheta);
        // if (ithBIN > 1000)
        // printf("x:%f\ty:%f\tz:%f\tIthBIN:%d\n", R_cubic, Costheta, Photon2edep, ithBIN);
        if (ithBIN > 0 && ithBIN <= TotalBIN)
        {
            BinArray[ithBIN - 1] += 1;
            // printf("i:%d\tnum:%d\n", ithBIN, BinArray[ithBIN]);
        }

        // h_ra->Fill(E_ratio, 1);
        // printf("which: %0.15f\n", E_ratio);
        // h_vis->Fill(E_true, E_ratio);
        // }
        // h_true->Fill(E_true);

        // E_vis = nPhotons / LightYeild - n_capture;
        // h_ep->Fill(E_true, E_vis);
        // h_ep->Fill(E_true, E_dep);

        // printf("this entry: %e\n", E_vis);
        // h_vis->Fill(E_vis);
        // if (E_dep[0] < E_true)
        //     ELnum++;
        // SE_true += E_true;
        // SE_dep += E_dep[0];
        // Tnum++;
    }
    for (int i = 0; i < TotalBIN; i++)
    {
        SE_dep = h_ep->GetBinContent(i + 1);
        // printf("i:%d\tnum:%f\n", i, h_ep->GetBinContent(956));

        if (BinArray[i] > 1)
        {
            SE_dep /= BinArray[i]; //average of ith bin
            h_ep->SetBinContent(i + 1, SE_dep);
            // printf("i:%d\tnum:%d\tthese:%f\n", i, BinArray[i], SE_dep);
        }
    }
    // printf("Total leakage: %f\n", 1. - SE_dep / SE_true);
    // printf("total Leakage NUM:%f\n", (float)ELnum / Tnum);
    TFile *ff_EL = TFile::Open("JUNOEnergyLeakage.root", "RECREATE");
    ff_EL->cd();
    // h_true->Write();
    // h_vis->Write();
    h_ep->Write();
    // h_ra->Scale(1 / h_ra->Integral());
    // h_ra->Write();
    // h_ra2R->Write();

    ff_EL->Close();

    return 0;
}
