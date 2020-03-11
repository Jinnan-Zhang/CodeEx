#include <TFile.h>
#include <TGraph.h>
#include <iostream>
#include <TH1.h>
// using std::cout, std::endl;


int ShowNL()
{
    TH1::AddDirectory(false);
    TFile *ff = TFile::Open("energymodel_Apr2018_newE.root", "READ");
    TFile *ff_h=TFile::Open("histNL.root","READ");
    TH1D *h1=0;
    ff_h->GetObject("h1",h1);
    for(int i=0;i<1e7;i++)
    {
        printf("%f\n",h1->Interpolate(4));
    }
    // TGraph *g0 = 0;
    // ff->GetObject("positronFullNL", g0);
    // // for(int i=0;i<1e6;i++)
    // // {
    // //     g0->Eval(4);
    // // }
    // g0->Draw();
    return 0;
}