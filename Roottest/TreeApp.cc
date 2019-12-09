#include <TTree.h>
#include <iostream>
#include <TFile.h>
#include <TRandom3.h>
#include <string>
#include <TH2.h>
#include <TF2.h>
#include "ROOT/TProcessExecutor.hxx"
#include "ROOT/TSeq.hxx"
#include <fstream>

const UInt_t nWorkers = 106U;
using namespace std;
int appd(int ID);

int TreeApp()
{
    
    // TTree *t1 = 0;
    // if ((TTree *)file1->Get("t1"))
    //     t1 = (TTree *)file1->Get("t1");
    // else
    //     t1 = new TTree("t1", "app test");
    // struct COM
    // {
    //     double sinsq;
    //     double dmsq;
    // } Coo;

    // string anm = "try";
    // if (t1->SetBranchAddress(anm.c_str(), &Coo) > 0)
    // {
    //     t1->SetBranchAddress(anm.c_str(), &Coo);
    // }
    // else
    // {
    //     t1->Branch(anm.c_str(), &Coo, "sinsq/D:dmsq/D");
    // }

    // for (int i = 0; i < 3e3; i++)
    // {
    //     // double a=gRandom->Gaus(0, 10);
    //     Coo.dmsq = gRandom->Gaus(0, 10);
    //     Coo.sinsq =  gRandom->Gaus(0, 10);
    //     t1->Fill();
    // }
    // t1->Fill();
    // t1->Write("", TObject::kOverwrite);

    auto work_item=appd;
    ROOT::TProcessExecutor workers(nWorkers);
    workers.Map(work_item,ROOT::TSeqI(nWorkers));

    return 0;
}
int appd(int ID)
{
    // ofstream outfile("app.txt",ios::app);
    // for(int i=0;i<1e1;i++)
    //     outfile<<i+ID<<endl;
    // outfile.close();
    TH1::AddDirectory(false);
    TFile *file1 = TFile::Open("app.root", "READ");
    TH2D *h1 = 0;
    if ((TH2D *)file1->Get("h1") )
        h1 = (TH2D *)file1->Get("h1");
    else
        h1 = new TH2D("h1", "", 50, -10, 10, 50, -10, 10);

    TF2 f1("f1", "x*x+y*y+2", -10, 10, -10, 10);
    // h1->FillRandom("f1");
    double a[2]={1,2};
    // h1->SetContour(2,a);
    // h1->Write("",TObject::kOverwrite);
    h1->Draw();
    file1->Close("R");
    return 0;
}