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

// Headers needed by this particular selector

class GetPE2R3 : public TSelector
{
public:
   TTreeReader fReader;         //!the tree reader
   TTree *fChain = 0;           //!pointer to the analyzed TTree or TChain
   TTree *prmtrkdep = 0;        //tree friend
   TTreeReader prmtrkdepReader; //!the tree reader
   TTree *geninfo = 0;          //tree friend
   TTreeReader geninfoReader;   //!the tree reader

   // Readers to access the data (delete the ones you do not need).
   // TTreeReaderValue<Int_t> nPhotons = {fReader, "nPhotons"};
   // TTreeReaderValue<Int_t> totalPE = {fReader, "totalPE"};
   // TTreeReaderArray<Int_t> nPE = {fReader, "nPE"};
   TTreeReaderArray<Double_t> hitTime = {fReader, "hitTime"};
   // TTreeReaderValue<Float_t> edep = {fReader, "edep"};
   // TTreeReaderValue<Float_t> edepX = {fReader, "edepX"};
   // TTreeReaderValue<Float_t> edepY = {fReader, "edepY"};
   // TTreeReaderValue<Float_t> edepZ = {fReader, "edepZ"};
   TTreeReaderArray<Float_t> edep = {prmtrkdepReader, "edep"};

   GetPE2R3(TTree * /*tree*/ = 0) {}
   virtual ~GetPE2R3() {}
   virtual Int_t Version() const { return 2; }
   virtual void Begin(TTree *tree);
   virtual void SlaveBegin(TTree *tree);
   virtual void Init(TTree *tree);
   virtual Bool_t Notify();
   virtual Bool_t Process(Long64_t entry);
   virtual Int_t GetEntry(Long64_t entry, Int_t getall = 0)
   {
      TString option = GetOption();
      if (option.Contains("prmtrkdep"))
         prmtrkdep->GetTree()->GetEntry(entry, getall);
      if (option.Contains("geninfo"))
         geninfo->GetTree()->GetEntry(entry, getall);
      return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0;
   }
   virtual void SetOption(const char *option) { fOption = option; }
   virtual void SetObject(TObject *obj) { fObject = obj; }
   virtual void SetInputList(TList *input) { fInput = input; }
   virtual TList *GetOutputList() const { return fOutput; }
   virtual void SlaveTerminate();
   virtual void Terminate();

   ClassDef(GetPE2R3, 0);
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

   fReader.SetTree(tree);
   TString option = GetOption();
   if (option.Contains("prmtrkdep"))
   {
      prmtrkdepReader.SetTree(tree->GetFriend("prmtrkdep"));
   }
   if (option.Contains("geninfo"))
   {
      geninfoReader.SetTree(tree->GetFriend("geninfo"));
   }
}

Bool_t GetPE2R3::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef GetPE2R3_cxx
