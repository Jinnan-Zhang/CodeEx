#include <TFile.h>
#include <TGraph.h>
#include <iostream>
using std::cout, std::endl;

int ShowNL()
{
    TFile *ff = TFile::Open("energymodel_Apr2018_newE.root", "READ");
    TGraph *g0 = 0;
    ff->GetObject("positronFullNL", g0);
    // for(int i=0;i<1e6;i++)
    // {
    //     g0->Eval(4);
    // }
    g0->Draw();
     return 0;
}