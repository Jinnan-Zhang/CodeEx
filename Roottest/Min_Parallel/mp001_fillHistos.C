#include "ROOT/TProcessExecutor.hxx"
#include "ROOT/TSeq.hxx"
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <iostream>

using namespace std;

// The number of workers
const UInt_t nWorkers = 6U;
int doit(UInt_t workerID);
static TH1D *h1 = new TH1D("h1", "", 20, -10, 10);
double a[10];
Int_t mp001_fillHistos()
{
   // We define our work item
   auto workItem = doit;

   // Create the pool of workers
   ROOT::TProcessExecutor workers(nWorkers);

   // Fill the pool with work
   workers.Map(workItem, ROOT::TSeqI(nWorkers));

   // TFile *fx=TFile::Open("myfile.root","RECREATE");
   // h1->Draw();

   return 0;
}
int doit(UInt_t workerID)
{
   TFile *f=TFile::Open("a.root","READ");
   TH1* h2=0;
   f->GetObject("h1",h2);
   cout << h2->GetBinContent(50) << endl;
   return 0;
};