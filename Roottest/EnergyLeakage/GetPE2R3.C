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

void GetPE2R3::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
}

void GetPE2R3::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
   h_ep = new TH2F("EnergyProfile", "Simulation", NBinx, Ran_x[0], Ran_x[1], NBiny, Ran_y[0], Ran_y[1]);
   fOutput->Add(h_ep);
   h_ep_count = new TH2I("hep_Counts", "Simulation", NBinx, Ran_x[0], Ran_x[1], NBiny, Ran_y[0], Ran_y[1]);
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
   TString option = GetOption();
   // if (option.Contains("prmtrkdep") && option.Contains("geninfo")&&option.Contains("nCapture"))
   // {
   fReader.SetLocalEntry(entry);
   prmtrkdepReader.SetLocalEntry(entry);
   // printf("hitTime:%f\n", hitTime[0]);
   // printf("edep:%f\n", edep.At(1));
   geninfoReader.SetLocalEntry(entry);
   nCaptureReader.SetLocalEntry(entry);
   TVector3 EvtPos(InitX[0] / 1e3, InitY[0] / 1e3, InitZ[0] / 1e3);
   int PromptCount(0);
   for (int j = 0; j < *totalPE; j++)
   { //avoid short time capture
      if (hitTime[j] < PromptTimeCut && NeutronCaptureT[0] > PromptTimeCut)
      {
         PromptCount++;
      }
   }
   float Photon2edep(PromptCount / edep[0]);
   double R_cubic = pow(EvtPos.Mag2(), 1.5);
   double Costheta = EvtPos.CosTheta();
   // printf("x:%f\ty:%f\tz:%f\n", R_cubic, Costheta, Photon2edep);
   h_ep->Fill(R_cubic, Costheta, Photon2edep);
   h_ep_count->Fill(R_cubic, Costheta);
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
   h_ep = dynamic_cast<TH2F *>(fOutput->FindObject("EnergyProfile"));
   h_ep_count = dynamic_cast<TH2I *>(fOutput->FindObject("hep_Counts"));
   TCanvas c("myCanvasName", "The Canvas Title", 800, 600);
   //calculate average
   h_ep->Divide(h_ep,h_ep_count);
   
   h_ep->SetXTitle("R^{3} (m^{3})");
   h_ep->SetYTitle("cos#theta");
   h_ep->Draw("colz");
   c.SaveAs("totalPE2R3.png");
   TFile ff_PE2R3("totalPE2R3.root", "RECREATE");
   ff_PE2R3.cd();
   h_ep->Write();
   ff_PE2R3.Close();
}