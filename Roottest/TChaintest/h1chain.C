/// \file
/// \ingroup tutorial_tree
/// \notebook -nodraw
/// Creates a TChain to be used by the h1analysis.C class
/// the symbol H1 must point to a directory where the H1 data sets
/// have been installed.
///
/// \macro_code
///
/// \author Rene Brun
#include <TChain.h>
#include <TROOT.h>
#include <TTree.h>
#include <TFile.h>
#include <TSelector.h>
#include <TH1.h>
#include <TH2.h>
#include <TEntryList.h>
#include <TF1.h>
#include "TStyle.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TLine.h"
#include "TMath.h"
#include "h1analysis.h"

int h1chain()
{
   TChain chain("h42");
   chain.Add("dstar*.root");
   // chain.MakeSelector("h1analysis");
   chain.Process("h1analysis.C");
   return 0;
}
