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
int NBinx = 100;
int NBiny = 50;

int ELout()
{
    // TH1::AddDirectory(false);
    TChain evt("evt");
    TChain prmtrkdep("prmtrkdep");
    TChain genifo("geninfo");
    for (int nn = 10000; nn < 10001; nn++)
    {
        if (nn != 10216)
        {
            evt.Add(Form("%s%d.root", HXD, nn));
            prmtrkdep.Add(Form("%s%d.root", HXD, nn));
            genifo.Add(Form("%s%d.root", HXD, nn));
        }
    }
    // evt.MakeSelector("E_vis_r");
    evt.SetBranchStatus("*", 0);
    prmtrkdep.SetBranchStatus("*", 0);
    genifo.SetBranchStatus("*", 0);

    int totalPE;
    // float E_dep[2], edepX[2], edepY[2], edepZ[2];
    float edep;
    evt.SetBranchStatus("totalPE", 1);
    evt.SetBranchAddress("totalPE", &totalPE);
    // evt.SetBranchStatus("edep", 1);
    // evt.SetBranchAddress("edep", &edep);
    evt.SetBranchStatus("hitTime", 1);
    double *hitTime;
    evt.SetBranchAddress("hitTime", hitTime);

    // evt.SetBranchStatus("edepX", 1);
    // evt.SetBranchAddress("edepX", &edepX);
    // evt.SetBranchStatus("edepY", 1);
    // evt.SetBranchAddress("edepY", &edepY);
    // evt.SetBranchStatus("edepZ", 1);
    // evt.SetBranchAddress("edepZ", &edepZ);

    // int PDGid[2];
    float InitPX[2], InitPY[2], InitPZ[2];
    float InitX[2], InitY[2], InitZ[2];
    // genifo.SetBranchStatus("InitPDGID", 1);
    // genifo.SetBranchStatus("InitPX", 1);
    // genifo.SetBranchStatus("InitPY", 1);
    // genifo.SetBranchStatus("InitPZ", 1);
    genifo.SetBranchStatus("InitX", 1);
    genifo.SetBranchStatus("InitY", 1);
    genifo.SetBranchStatus("InitZ", 1);
    // genifo.SetBranchAddress("InitPDGID", &PDGid);
    // genifo.SetBranchAddress("InitPX", &InitPX);
    // genifo.SetBranchAddress("InitPZ", &InitPY);
    // genifo.SetBranchAddress("InitPY", &InitPZ);
    genifo.SetBranchAddress("InitX", &InitX);
    genifo.SetBranchAddress("InitY", &InitY);
    genifo.SetBranchAddress("InitZ", &InitZ);

    double E_true(0), E_vis(0);
    // TH1D *h_true = new TH1D("E_True", "True Eernergy",NBiny, Ran_x[0], Ran_x[1]);

    // light yield curve
    // TH1D *h_LY = new TH1D("h_LY", "Light Yield Curve", NBinx, Ran_x[0], Ran_x[1]);
    // TFile *ff_LY = TFile::Open("R3CosThetaNphotons.root", "READ");
    //light yield profile
    // TH2D *h_LY = (TH2D *)ff_LY->Get("EnergyProfile");
    // h_LY->SetXTitle("R^{3} (m^{3})");
    // h_LY->SetYTitle("totalPE/MeV");
    //totalPE curve
    // TH1D *h_nPho = new TH1D("Eratio", "", NBinx, Ran_x[0], Ran_x[1]);

    TH2F *h_ep = new TH2F("EnergyProfile", "Simulation", NBinx, Ran_x[0], Ran_x[1], NBiny, Ran_y[0], Ran_y[1]);
    h_ep->SetXTitle("R^{3} (m^{3})");
    // h_ep->SetYTitle("totalPE/MeV");
    h_ep->SetYTitle("cos#theta");
    // h_ep->SetYTitle("True Energy(MeV)");

    // h_nPho->SetXTitle("E_{dep}/E_{true}");
    // TH2D *h_xy = new TH2D("EnergyProfile", "", NBinx, -18, 18, NBinx, -18, 18);
    // h_xy->SetXTitle("x (m)");
    // h_xy->SetYTitle("z (m)");
    double E_ratio(0), R_cubic(0);
    double Photon2edep(0), Costheta(0);
    double SE_true(0), SE_dep(0);
    // int ELnum(0), Tnum(0);
    int TotalBIN = h_ep->GetSize();
    int BinArray[TotalBIN];
    // float BinValue[TotalBIN];
    for (int i = 0; i < TotalBIN; i++)
    {
        BinArray[i] = 0;
        // BinValue[i] = 0;
    }
    int ithBIN(0);
    int PromptCount(0);
    for (int i = 0; i < evt.GetEntries(); i++)
    {

        evt.GetEntry(i);
        genifo.GetEntry(i);
        printf("yes\n"); //can't reach here
        // E_true = TMath::Sqrt(InitPX[0] * InitPX[0] + InitPY[0] * InitPY[0] + InitPZ[0] * InitPZ[0] + M_electron_sq) + M_e;
        // if ( E_dep < E_true)
        // {
        // E_ratio = E_dep[0] / E_true;
        // R_cubic = sqrt(edepX[0] * edepX[0] + edepY[0] * edepY[0] + edepZ[0] * edepZ[0]) / 1000.; //to meter
        // h_xy->Fill(R_cubic, E_ratio);
        // R_cubic = pow((InitX[0] * InitX[0] + InitY[0] * InitY[0] + InitZ[0] * InitZ[0]), 1.5) / 1e9;
        TVector3 EvtPos(InitX[0] / 1e3, InitY[0] / 1e3, InitZ[0] / 1e3);
        PromptCount = 0;
        for (int j = 0; j < totalPE; j++)
        {
            if (hitTime[j] > 1200)
            {
                PromptCount++;
                printf("which: %f\n", hitTime[j]);
            }
        }
        Photon2edep = PromptCount / edep;
        // ithBIN = h_xy->Fill(InitX[0]/1e3, InitZ[0]/1e3, Photon2edep);
        R_cubic = pow(EvtPos.Mag2(), 1.5);
        Costheta = EvtPos.CosTheta();
        ithBIN = h_ep->Fill(R_cubic, Costheta, Photon2edep);
        // ithBIN = h_LY->Fill(R_cubic, Photon2edep);
        // ithBIN = h_ep->Fill(R_cubic, Costheta, Photon2edep);
        // ithBIN = h_ep->FindBin(R_cubic, Costheta);
        // if (ithBIN > 1000)
        // printf("x:%f\ty:%f\tz:%f\tIthBIN:%d\n", R_cubic, Costheta, Photon2edep, ithBIN);
        if (ithBIN > 0 && ithBIN <= TotalBIN)
        {
            BinArray[ithBIN - 1] += 1;
            // printf("i:%d\tnum:%d\n", ithBIN, BinArray[ithBIN]);
        }

        // h_nPho->Fill(E_ratio, 1);
        // h_LY->Fill(E_true, E_ratio);
        // }
        // h_true->Fill(E_true);

        // E_vis = totalPE / LightYeild - n_capture;
        // h_ep->Fill(E_true, E_vis);
        // h_ep->Fill(E_true, E_dep);

        // printf("this entry: %e\n", E_vis);
        // h_LY->Fill(E_vis);
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
    // h_LY->Write();
    h_ep->Write();
    // h_nPho->Scale(1 / h_nPho->Integral());
    // h_nPho->Write();
    // h_xy->Write();

    ff_EL->Close();

    return 0;
}
