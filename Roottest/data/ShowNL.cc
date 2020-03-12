#include <TFile.h>
#include <TGraph.h>
#include <iostream>
#include <TH1.h>
// using std::cout, std::endl;
#include <timeMacro.h>

int ShowNL()
{
    TH1::AddDirectory(false);
    TFile *ff = TFile::Open("energymodel_Apr2018_newE.root", "READ");
    TFile *ff_h=TFile::Open("histNL.root","READ");
    TH1D *h1=0;
    ff_h->GetObject("h1",h1);
    StartTimeChrono(1);
    for(int i=0;i<1e7;i++)
    {
        printf("%f\n",h1->Interpolate(4));
    }
    StopTimeChrono(1);

    TGraph *g0 = 0;
    ff->GetObject("positronFullNL", g0);
    StopTimeChrono(2);
    for(int i=0;i<1e6;i++)
    {
        g0->Eval(4);
    }
    StopTimeChrono(2);
    PrintTimeChrono(1,"TH1");
    PrintTimeChrono(2,"TG");
    // g0->Draw();
    return 0;
}