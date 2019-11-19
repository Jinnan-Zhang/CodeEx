
#include <TMath.h>
#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "TRandom3.h"
#include "TError.h"
#include <thread>
#include <vector>

#include <TCanvas.h>
#include <TH1.h>
#include <iostream>
using namespace std;
int alla = 0;
double wra(const double *x)
{
    switch (alla)
    {
    case 2:
        return x[0] * x[0] + x[1] * x[1] * x[1] * x[1];

    case 3:
        return x[1] * x[1] + x[0] * x[0] * x[0] * x[0] + 1 + x[2] * x[2];
    }
    return 0;
}

int minfunct()
{
    ROOT::Math::Minimizer *miniChi = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");
    //set tolerance , etc...
    miniChi->SetMaxFunctionCalls(100000); // for Minuit/Minuit2
    miniChi->SetMaxIterations(1000);      // for GSL
    miniChi->SetTolerance(0.001);
    miniChi->SetPrintLevel(1);
    //create function wrapper for minimizer
    //a IMultiGenFunction type
    int SN4par = 0;
    alla = 3;
    ROOT::Math::Functor fG(&wra, alla);
    miniChi->SetFunction(fG);
    double steps = 0.01;
    double starts = 0;
    miniChi->SetVariable(SN4par++, "x", starts, steps);
    miniChi->SetVariable(SN4par++, "y", starts, steps);
    miniChi->SetVariable(SN4par++, "z", starts, steps);
    miniChi->Minimize();
    cout<<miniChi->MinValue()<<endl;
    return 0;
}