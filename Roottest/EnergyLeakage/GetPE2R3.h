//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Apr 11 10:17:14 2020 by ROOT version 6.18/00
// from TChain evt/
//////////////////////////////////////////////////////////

#ifndef GetPE2R3_h
#define GetPE2R3_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TH2.h>
#include <TH1.h>
#include <TVector3.h>
#include <vector>

// Headers needed by this particular selector

class GetPE2R3 : public TSelector
{
public:
   TTree *evt = 0;              //!pointer to the analyzed TTree or TChain
   TTreeReader evtReader;       //!the tree reader
   TTree *prmtrkdep = 0;        //tree friend
   TTreeReader prmtrkdepReader; //!the tree reader
   TTree *geninfo = 0;          //tree friend
   TTreeReader geninfoReader;   //!the tree reader
   TTree *nCapture = 0;         //tree friend
   TTreeReader nCaptureReader;  //!the tree reader

   // Readers to access the data (delete the ones you do not need).
   // TTreeReaderValue<Int_t> nPhotons = {evtReader, "nPhotons"};
   // TTreeReaderValue<Int_t> totalPE = {evtReader, "totalPE"};
   // TTreeReaderArray<Int_t> nPE = {evtReader, "nPE"};
   // TTreeReaderArray<Double_t> hitTime = {evtReader, "hitTime"};
   // TTreeReaderValue<Float_t> edep = {evtReader, "edep"};
   // TTreeReaderValue<Float_t> edepX = {evtReader, "edepX"};
   // TTreeReaderValue<Float_t> edepY = {evtReader, "edepY"};
   // TTreeReaderValue<Float_t> edepZ = {evtReader, "edepZ"};
   // TTreeReaderArray<Float_t> edep = {prmtrkdepReader, "edep"};
   TTreeReaderArray<Float_t> InitX = {geninfoReader, "InitX"};
   TTreeReaderArray<Float_t> InitY = {geninfoReader, "InitY"};
   TTreeReaderArray<Float_t> InitZ = {geninfoReader, "InitZ"};
   // TTreeReaderArray<double> NeutronCaptureT = {nCaptureReader, "NeutronCaptureT"};

   //outputs
   TH2F *h_ep;
   TH2I *h_ep_count;

   GetPE2R3(TTree * /*tree*/ = 0) { Reset(); }
   virtual ~GetPE2R3() {}
   virtual Int_t Version() const { return 1; }
   virtual void Begin(TTree *tree);
   virtual void SlaveBegin(TTree *tree);
   virtual void Init(TTree *tree);
   virtual Bool_t Notify();
   virtual Bool_t Process(Long64_t entry);
   // virtual Int_t GetEntry(Long64_t entry, Int_t getall = 0)
   // {
   //    TString option = GetOption();
   //    if (option.Contains("prmtrkdep"))
   //       prmtrkdep->GetTree()->GetEntry(entry, getall);
   //    if (option.Contains("geninfo"))
   //       geninfo->GetTree()->GetEntry(entry, getall);
   //    if (option.Contains("nCapture"))
   //       nCapture->GetTree()->GetEntry(entry, getall);
   //    return evt ? evt->GetTree()->GetEntry(entry, getall) : 0;
   // }
   virtual void SetOption(const char *option) { fOption = option; }
   virtual void SetObject(TObject *obj) { fObject = obj; }
   virtual void SetInputList(TList *input) { fInput = input; }
   virtual TList *GetOutputList() const { return fOutput; }
   virtual void SlaveTerminate();
   virtual void Terminate();
   void Reset()
   {
      h_ep = 0;
      h_ep_count = 0;
   }
   ClassDef(GetPE2R3, 0);

private:
   double M_electron_sq = 0.26111993;
   double M_e = 0.51099895;
   double n_capture = 2.2; //MeV
   double LightYeild = 1200.;

   double Ran_x[2] = {0, 5300};
   double Ran_y[2] = {-1, 1};
   int NBinx = 100;
   int NBiny = 50;
   double PromptTimeCut = 1000;
   int TotalBin = 0;
   // int *BinValue;
};

#endif

#ifdef GetPE2R3_cxx
void GetPE2R3::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   evtReader.SetTree(tree);
   TString option = GetOption();
   if (option.Contains("prmtrkdep"))
   {
      prmtrkdepReader.SetTree(tree->GetFriend("prmtrkdep"));
   }
   if (option.Contains("geninfo"))
   {
      geninfoReader.SetTree(tree->GetFriend("geninfo"));
   }
   if (option.Contains("nCapture"))
   {
      nCaptureReader.SetTree(tree->GetFriend("nCapture"));
   }
}

Bool_t GetPE2R3::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.
   Info("Notify", "processing file: %s", evtReader.GetTree()->GetCurrentFile()->GetName());

   return kTRUE;
}

#endif // #ifdef GetPE2R3_cxx
