//purpose: test efficiency of different method
#include <TH1.h>
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
double GFCN(double x)
{
    // double a = 1. / sqrt(2 * 3.14) / 1. * exp(-0.5 * x * x);
    // double b = 1. / sqrt(2 * 3.14) / 1. * exp(-0.5 * x * x);
    // double c = 1. / sqrt(2 * 3.14) / 1. * exp(-0.5 * x * x);
    // return a + b * c;
    double a=exp(x)+exp(x+1)+exp(x*1)+exp(x-1)+exp(x+7);
    return a;
}
void tHistFCN()
{
    TH1D *h_d = new TH1D("h_d", "hh", 600, -1, 1);
    h_d->FillRandom("gaus",1e5);
    double N = 1e7;
    double sum = 0;
    StartTimeChrono(1);
    for (int i = 0; i < N; i++)
    {
        sum += h_d->Interpolate(0.15);
        sum += h_d->Interpolate(0.15);
        sum += h_d->Interpolate(0.15);
        sum += h_d->Interpolate(0.15);
        sum += h_d->Interpolate(0.15);
    }
    StopTimeChrono(1);
    PrintTimeChrono(1, "hist");
    sum = 0;
    StartTimeChrono(2);
    for (int i = 0; i < N; i++)
    {
        sum += GFCN(0.15);
    }
    StopTimeChrono(2);
    PrintTimeChrono(2, "fcn");
}
int EffTest()
{
    // tHistFCN();
    return 0;
}