/// \file
/// \ingroup tutorial_multicore
/// \notebook
/// Parallel fill of a histogram.
/// This tutorial shows how a histogram can be filled in parallel
/// with a multiprocess approach.
///
/// \macro_image
/// \macro_code
///
/// \date January 2016
/// \author Danilo Piparo.
#include "ROOT/TSeq.hxx"
#include "ROOT/TThreadExecutor.hxx"
#include "PoolUtils.h"

#include <TH1.h>
#include <TCanvas.h>
#include <TRandom3.h>


const UInt_t poolSize = 8U;

Int_t mtbb201_parallelHistoFill()
{
   ROOT::EnableThreadSafety();
   TH1::AddDirectory(false);
   ROOT::TThreadExecutor pool(poolSize);
   auto fillRandomHisto = [](int seed = 0) {
      TRandom3 rndm(seed);
      auto h = new TH1F("myHist", "Filled in parallel", 128, -8, 8);
      for (auto i : ROOT::TSeqI(1e8)) {
         h->Fill(rndm.Gaus(0, 1));
      }
      return h;
   };

   auto seeds = ROOT::TSeqI(23);
   ROOT::ExecutorUtils::ReduceObjects<TH1F *> redfunc;
   auto sumRandomHisto = pool.MapReduce(fillRandomHisto, seeds, redfunc);

   auto c = new TCanvas();
   sumRandomHisto->Draw();
   return 0;
}
