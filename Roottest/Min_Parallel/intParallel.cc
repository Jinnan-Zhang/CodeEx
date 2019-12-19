#include "ROOT/TProcessExecutor.hxx"
#include "ROOT/TSeq.hxx"
#include <TH1.h>
#include <TH2.h>
#include <TF1.h>
#include <TFile.h>
#include <iostream>

using namespace std;

// The number of workers
const UInt_t nWorkers = 6U;
int doit(UInt_t workerID);
TF1 *f1 = new TF1("f1", "sin(x)+x*x", -10, 10);
int ntParallel()
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
    
}