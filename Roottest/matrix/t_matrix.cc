#pragma once
/*
usage:
StartTimeChrono(num);
...
StopTimeChrono(num);
PrintTimeChrono(num,"discription")
*/
#include <chrono>

#define StartTimeChrono(_num) \
    auto start##_num = std::chrono::high_resolution_clock::now()

#define StopTimeChrono(_num) \
    auto stop##_num = std::chrono::high_resolution_clock::now()

#ifdef _WIN32
#define PrintTimeChrono(_num, _str)                                                                    \
    auto dura##_num = std::chrono::duration_cast<std::chrono::microseconds>(stop##_num - start##_num); \
    printf("Time for calculating %s is %f millisecond.\n", _str, dura##_num.count())
#else
#define PrintTimeChrono(_num, _str)                                                                    \
    auto dura##_num = std::chrono::duration_cast<std::chrono::microseconds>(stop##_num - start##_num); \
    printf("Time for calculating %s is %f second.\n", _str, dura##_num.count() / 1.e6)
#endif

#include <TMatrixD.h>
#include <TFile.h>
#include <TH2.h>

int t_matrix()
{
    TFile *file_in = TFile::Open("/home/jinnan/work/Reactor/JUNO_Atm_Rea/JunoARCon/data/Inputs/TAOInputs2021_11_29.root");
    TH2 *h_TAO_cov = (TH2 *)file_in->Get("CovMatrixFVCut_3_5");
    TH1 *h_b = (TH1 *)file_in->Get("TAOFnBkg20KeVDownTime;1");
    int Nbins = h_TAO_cov->GetNbinsX();
    TMatrixD M_cov(Nbins, Nbins);
    TMatrixD A(Nbins + 3, 1);
    for (int i = 0; i < Nbins; i++)
    {
        A[i][0] = h_b->GetBinContent(i + 1);
        for (int j = 0; j < Nbins; j++)
        {
            M_cov[i][j] = h_TAO_cov->GetBinContent(i + 1, j + 1);
        }
    }
    printf("A:%dx%d\n", A.GetNrows(), A.GetNcols());
    // printf("v A: %f\n", A[20][0]);
    printf("v: %f\n", M_cov[20][20]);
    printf("M:%dx%d\n", M_cov.GetNrows(), M_cov.GetNcols());
    TMatrixD C(M_cov, TMatrixD::kMult, A.GetSub(0, Nbins-1, 0, 0));

    printf("M:%dx%d\n", M_cov.GetNrows(), M_cov.GetNcols());
    printf("C:%dx%d\n", C.GetNrows(), C.GetNcols());
    // printf("v: %f\n", C[20][20]);

    return 0;
}