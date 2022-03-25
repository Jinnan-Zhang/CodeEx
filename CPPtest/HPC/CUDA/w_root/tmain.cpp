#include <stdlib.h>
#include <iostream>
#include <tFCN.h>
#include "HelloWorld.h"
#include <TH1.h>
#include <TCanvas.h>
#include <TH2.h>
#include <TFile.h>
#include "omp.h"
#include <vector>
#include "tmain.h"

void tWork();
int main()
{
    tWork();
    return 0;
}

void tWork()
{
    // printf("here\n");
    TFile *file_data = TFile::Open("JUNOResponseMatrix.root");
    TFile *file_input = TFile::Open("/home/jinnan/work/Reactor/JUNO_Atm_Rea/JunoARCon/data/Inputs/JUNOInputs2021_03_22.root");
    TH1 *h_flux = (TH1 *)file_input->Get("HuberMuellerFlux_DYBbumpFixed;1");
    TH2 *h_response = (TH2 *)file_data->Get("Xsec_matrix_VB_DYB_2keV;1");
    int NX = h_response->GetNbinsX();
    int NY = h_response->GetNbinsY();
    // int NX = 10;
    // int NY = 10;

    std::vector<double> A(NX, 0);
    std::vector<double> B(NY * NX, 0);
    std::vector<double> C(NY, 0);
    for (int i = 0; i < NX; i++)
    {
        double Enu = h_response->GetYaxis()->GetBinCenter(i + 1);
        A[i] = h_flux->Interpolate(Enu);
#pragma omp parallel for
        for (int j = 0; j < NY; j++)
        {
            int index_h = i * NX + j;
            double v_h = h_response->GetBinContent(i + 1, j + 1) ;
            B[index_h] = v_h;
            // if (v_h > 0)
            //     printf("B:%e\n", v_h);
        }
    }
    StartTimeChrono(1);
    C = GetMatProdcut(A, 1, NX, NX, B, C);

    StopTimeChrono(1);
    PrintTimeChrono(1, "matrix:");

    // printf("A: %f\n", A[0]);
    TH1 *h_result = new TH1D("result", "neutrino flux; Positron Energy [MeV]; #Phi", NX, 1.022, 12);
#pragma omp parallel for
    for (int i = 0; i < NX; i++)
        h_result->SetBinContent(i + 1, C[i]);
    TCanvas *c0 = new TCanvas("cc", "matrix production", 800, 600);
    h_result->Draw();
    c0->SaveAs("result.png");
    // DoVector();
    // ShowTH1();
    file_data->Close();
}
