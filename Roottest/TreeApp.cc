#include <TTree.h>
#include <iostream>
#include <TFile.h>
#include <TRandom3.h>

using namespace std;
int TreeApp()
{
    TFile *file1 = TFile::Open("app.root", "UPDATE");
    TTree *t1 = 0;
    if ((TTree *)file1->Get("t1"))
        t1 = (TTree *)file1->Get("t1");
    else
        t1 = new TTree("t1", "app test");
    // t1 = ((TTree *)file1->Get("t1") ? (TTree *)file1->Get("t1") : new TTree("t1", "app test"));
    double sinsq;
    double dmsq;
    if (t1->SetBranchAddress("sinsq", &sinsq) > 0)
    {
        t1->SetBranchAddress("sinsq", &sinsq);
    }
    else
    {
        t1->Branch("sinsq", &sinsq, "sinsq/D");
    }
    if (t1->SetBranchAddress("dmsq", &dmsq) > 0)
    {
        t1->SetBranchAddress("dmsq", &dmsq);
    }
    else
    {
        t1->Branch("dmsq", &dmsq, "dmsq/D");
    }

    for (int i = 0; i < 3e4; i++)
    {
        dmsq = gRandom->Gaus(i,i);
        sinsq = gRandom->Gaus(i,i);
        t1->Fill();
    }
    t1->Write("",TObject::kOverwrite);
    file1->Close();
    return 0;
}