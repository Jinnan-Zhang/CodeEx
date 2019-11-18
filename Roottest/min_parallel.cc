#include "ROOT/TSeq.hxx"
#include "ROOT/TThreadExecutor.hxx"
#include "PoolUtils.h"

#include <TMath.h>
#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "TRandom3.h"
#include "TError.h"

#include <TCanvas.h>
#include <TH1.h>
#include <iostream>
#include "timeMacro.h"
#define NUMBIN 20000
#define DENBIN 100
using namespace std;

const UInt_t poolSize = 8U;
double x_0, y_0, z_0;
double wrapx0(const double *x)
{
    double y = x[0];
    double z = x[1];
    return 2 * x_0 * x_0 + y * y + z * z * z * z + 10;
}
double wrapx1(const double *x)
{
    double x1 = x[0];
    double z = x[1];
    return 2 * x1 * x1 + y_0 * y_0 + z * z * z * z + 10;
}

double min_x(double x_v, int par)
{
    ROOT::Math::Minimizer *miniChi = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");
    //set tolerance , etc...
    miniChi->SetMaxFunctionCalls(100000); // for Minuit/Minuit2
    miniChi->SetMaxIterations(1000);      // for GSL
    miniChi->SetTolerance(0.001);
    miniChi->SetPrintLevel(0);
    //create function wrapper for minimizer
    //a IMultiGenFunction type
    int SN4par = 0;

    switch (par)
    {
    case 0: //
    {
        x_0 = x_v;
        ROOT::Math::Functor fG(&wrapx0, 2);
        miniChi->SetFunction(fG);
        double steps = 0.01;
        double starts = 0;
        miniChi->SetVariable(SN4par++, "y", starts, steps);
        miniChi->SetVariable(SN4par++, "z", starts, steps);
        miniChi->Minimize();
        return miniChi->MinValue();
    }
    case 1:
    {
        y_0 = x_v;
        ROOT::Math::Functor fG(&wrapx1, 2);
        miniChi->SetFunction(fG);
        double steps = 0.01;
        double starts = 0;
        miniChi->SetVariable(SN4par++, "x", starts, steps);
        miniChi->SetVariable(SN4par++, "z", starts, steps);
        miniChi->Minimize();
        return miniChi->MinValue();
    }
    }
    return 0;
}

// auto h = new TH1F("myHist", "Filled in parallel", NUMBIN, -8, 8);
int min_parallel()
{
    StartTimeChrono(1);

    ROOT::EnableThreadSafety();
    TH1::AddDirectory(false);
    ROOT::TThreadExecutor pool(poolSize);
    auto fillRandomHisto = [](int seed = 0) {
        auto h = new TH1F("myHist", "Filled in parallel", NUMBIN, -8, 8);
        // for (auto i : ROOT::TSeqI(NUMBIN / DENBIN))
        // {
        double aa = -8. + seed * 16. / NUMBIN;
        // printf("?: %d\n", i);
        h->SetBinContent(seed + 1, min_x(aa, 0));
        // }
        return h;
    };
    auto seeds = ROOT::TSeqI(NUMBIN);
    ROOT::ExecutorUtils::ReduceObjects<TH1F *> redfunc;
    // pool.Foreach(fillRandomHisto, seeds);
    auto h1 = pool.MapReduce(fillRandomHisto, seeds, redfunc);
    StopTimeChrono(1);

    StartTimeChrono(2);
    TH1F *h2 = new TH1F("myHist", "Filled in parallel", NUMBIN, -8, 8);
    for (int i = 0; i < NUMBIN; i++)
    {
        double aa = -8. + i * 16. / NUMBIN;
        h2->SetBinContent(i + 1, min_x(aa, 0));
    }
    StopTimeChrono(2);

    h1->Draw();
    h2->Draw("Same");

    PrintTimeChrono(1, "Parallel");
    PrintTimeChrono(2, "Sequence");

    return 0;
}