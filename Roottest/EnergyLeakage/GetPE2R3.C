#define GetPE2R3_cxx
// The class definition in GetPE2R3.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("GetPE2R3.C")
// root> T->Process("GetPE2R3.C","some options")
// root> T->Process("GetPE2R3.C+")
//

#include "GetPE2R3.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <TFile.h>
#include <TVector3.h>
#include <vector>
#include <cmath>
// #include <TROOT.h>
// #include <TChain.h>
// #include <TSelector.h>
// #include <TTreeReader.h>
// #include <TTreeReaderValue.h>
// #include <TTreeReaderArray.h>

void GetPE2R3::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
   Reset();
}

void GetPE2R3::SlaveBegin(TTree *myTree)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).
   Init(myTree);
   TString option = GetOption();
   h_ep = new TH2F("EnergyProfile", "Simulation", NBinx, Ran_x[0], Ran_x[1], NBiny, Ran_y[0], Ran_y[1]);
   fOutput->Add(h_ep);
   h_ep_count = new TH2F("hep_Counts", "Simulation", NBinx, Ran_x[0], Ran_x[1], NBiny, Ran_y[0], Ran_y[1]);
   fOutput->Add(h_ep_count);
   TotalBin = h_ep->GetSize();
   // BinValue = new int[TotalBin];
   // for (int i = 0; i < TotalBin; i++)
   //    BinValue[i] = 0;
}
Bool_t GetPE2R3::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // When processing keyed objects with PROOF, the object is already loaded
   // and is available via the fObject pointer.
   //
   // This function should contain the \"body\" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.
   // TTree *tree = evtReader.GetTree();
   // prmtrkdepReader.SetTree(tree->GetFriend("prmtrkdep"));
   // geninfoReader.SetTree(tree->GetFriend("geninfo"));
   // nCaptureReader.SetTree(tree->GetFriend("nCapture"));

   geninfoReader.SetLocalEntry(entry);
   prmtrkdepReader.SetLocalEntry(entry);
   evtReader.SetLocalEntry(entry);
   nCaptureReader.SetLocalEntry(entry);
   // printf("time:%f\n", hitTime[1]);
   nCaptureReader.GetTree()->Draw("NeutronCaptureT>>h_ncap(1,0,1200)", "", "goff", 1, entry);
   TH1F *h_ncap = (TH1F *)gDirectory->Get("h_ncap");

   if (!(h_ncap->GetEffectiveEntries()))
   {
      TVector3 EvtPos(InitX[0] / 1e3, InitY[0] / 1e3, InitZ[0] / 1e3);
      evtReader.GetTree()->Draw("hitTime>>h_pr", "hitTime<1000", "goff", 1, entry);
      TH1F *h_pr = (TH1F *)gDirectory->Get("h_pr");
      double PromptCount = h_pr->GetEffectiveEntries();
      // printf("h_pr:%f\ttotalPE:%d\n", PromptCount,*totalPE);
      // prmtrkdepReader.GetTree()->Draw("edep[0]>>h_edeps(1)", "edep[0]*(1>0)", "goff", 1, entry);
      // TH1F *h_edeps = (TH1F *)gDirectory->Get("h_edeps");
      // float E_dep(h_edeps->GetBinContent(1));
      float E_dep(edep[0]);
      float Photon2edep(PromptCount / E_dep);

      printf("E_dep:%f\n", E_dep);
      double R_cubic = pow(EvtPos.Mag2(), 1.5);
      double Costheta = EvtPos.CosTheta();
      // printf("x:%f\ty:%f\tz:%f\n", R_cubic, Costheta, E_dep);
      h_ep->Fill(R_cubic, Costheta, Photon2edep);
      h_ep_count->Fill(R_cubic, Costheta);
   }

   return kTRUE;
}

void GetPE2R3::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.
   // delete BinValue;
}

void GetPE2R3::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
   TH1::SetDefaultSumw2();
   h_ep = dynamic_cast<TH2F *>(fOutput->FindObject("EnergyProfile"));
   h_ep_count = dynamic_cast<TH2F *>(fOutput->FindObject("hep_Counts"));
   TCanvas c("myCanvasName", "The Canvas Title", 800, 600);
   // //calculate average
   // h_ep->Divide(h_ep, h_ep_count);
   double BinVi[2] = {0};
   for (int i = 0; i < TotalBin; i++)
   {
      BinVi[0] = h_ep_count->GetBinContent(i + 1);
      if (BinVi[0] > 1)
      {
         BinVi[1] = h_ep->GetBinContent(i + 1);
         BinVi[1] /= BinVi[0];
         h_ep->SetBinContent(i + 1, BinVi[1]);
      }
   }
   h_ep->SetXTitle("R^{3} (m^{3})");
   h_ep->SetYTitle("cos#theta");
   h_ep->Draw("colz");
   // h_ep_count->Draw("colz");
   c.SaveAs("totalPE2R3.png");
   TFile ff_PE2R3("totalPE2R3.root", "RECREATE");
   ff_PE2R3.cd();
   h_ep->Write();
   h_ep_count->Write();
   ff_PE2R3.Close();
}