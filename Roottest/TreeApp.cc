#include <TTree.h>
#include <iostream>
#include <TFile.h>
#include <TRandom3.h>
#include <string>
#include <TH2.h>
#include <TF2.h>

using namespace std;
int TreeApp()
{
    TH1::AddDirectory(false);
    TFile *file1 = TFile::Open("app.root", "UPDATE");
    TTree *t1 = 0;
    if ((TTree *)file1->Get("t1"))
        t1 = (TTree *)file1->Get("t1");
    else
        t1 = new TTree("t1", "app test");
    struct COM
    {
        double sinsq;
        double dmsq;
    } Coo;

    string anm = "try";
    if (t1->SetBranchAddress(anm.c_str(), &Coo) > 0)
    {
        t1->SetBranchAddress(anm.c_str(), &Coo);
    }
    else
    {
        t1->Branch(anm.c_str(), &Coo, "sinsq/D:dmsq/D");
    }

    for (int i = 0; i < 3e3; i++)
    {
        // double a=gRandom->Gaus(0, 10);
        Coo.dmsq = gRandom->Gaus(0, 10);
        Coo.sinsq =  gRandom->Gaus(0, 10);
        t1->Fill();
    }
    t1->Fill();
    t1->Write("", TObject::kOverwrite);
    file1->Close();
    return 0;
}