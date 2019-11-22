#include "ROOT/TSeq.hxx"
#include "ROOT/TThreadExecutor.hxx"
#include "PoolUtils.h"

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
#include "timeMacro.h"
#define NUMBIN 20 //worker number
#define DENBIN 200
using namespace std;

// The number of workers
// const UInt_t nWorkers = 4U;
double x_0=1, y_0, z_0;
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
    return 2 * x1 * x1 + y_0 * y_0 + z * z * z * z + 15;
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
        // x_0 = x_v;
        ROOT::Math::Functor fG(&wrapx0, 2);
        ROOT::Math::Functor fG1(&wrapx1, 2);
        // x_0 = x_v;
        miniChi->SetFunction(fG);
        double steps = 0.01;
        double starts = 0;
        miniChi->SetVariable(SN4par++, "y", starts, steps);
        miniChi->SetVariable(SN4par++, "z", starts, steps);
        
        miniChi->Minimize();
        cout<<"1st: "<<miniChi->MinValue()<<endl;
        miniChi->SetFunction(fG1);
        miniChi->Minimize();
        cout<<"2rd: "<<miniChi->MinValue()<<endl;
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

double tema[NUMBIN*DENBIN];
int min_parallel()
{
    StartTimeChrono(1);

    // ROOT::EnableThreadSafety();

    // auto workItem = [](UInt_t workerID) {
    //     // auto h = new TH1F("myHist", "Filled in parallel", NUMBIN*DENBIN, -8, 8);
    //     for (int i = 0; i < DENBIN; i++)
    //     {
    //         double aa = 0;
    //         aa = -8. + (workerID * DENBIN + i) * 16. / NUMBIN / DENBIN;
    //         tema[(workerID * DENBIN + i)]=min_x(aa,0);
    //         // printf("?: %d\n", (workerID * DENBIN + i));
    //         // h->SetBinContent((workerID * DENBIN + i + 1), min_x(aa, 0));
    //     }
    //     // printf("?: %d\n", workerID);
    //     // return h;
    // };
    // // Create the collection which will hold the threads, our "pool"
    // std::vector<std::thread> workers;

    // // Fill the "pool" with workers
    // for (auto workerID : ROOT::TSeqI(NUMBIN))
    // {
    //     workers.emplace_back(workItem, workerID);
    // }

    // // Now join them
    // for (auto &&worker : workers)
    //     worker.join();
    
    auto h = new TH1F("myHist", "Filled in parallel", NUMBIN *DENBIN, -8, 8);
    for(int i=0;i<NUMBIN*DENBIN;i++)
        h->SetBinContent(i+1,tema[i]);

    StopTimeChrono(1);

    StartTimeChrono(2);
    TH1F *h2 = new TH1F("myHist2", "Filled without parallel", NUMBIN * DENBIN, -8, 8);
    for (int i = 0; i < NUMBIN * DENBIN; i++)
    {
        double aa = 0;
        aa = -8. + i * 16. / NUMBIN / DENBIN;
        // printf("??:%f\n",aa);
        // h2->SetBinContent(i + 1, min_x(aa, 0));
    }
    StopTimeChrono(2);

    h->SetLineColor(kRed);
    // TCanvas *a = new TCanvas("c1", "Candle Decay", 800, 600);
    // a->Divide(2, 1);
    // a->cd(1);
    // // h->Draw();
    // // h2->Draw("Same");
    // a->cd(2);
    // h2->Draw();
    // h->Draw("SAME");
    PrintTimeChrono(1, "Parallel");
    PrintTimeChrono(2, "Sequence");
    cout<<min_x(0,0)<<endl;
    // double diffsum=0;
    // // for(int i=0;i<NUMBIN*DENBIN;i++)
    // // {
    // //     diffsum += (tema[i]-h2->GetBinContent(i+1));
    // // }
    // // cout<<diffsum<<endl;
    return 1;
}