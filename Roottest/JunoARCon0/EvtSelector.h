//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Apr  5 10:49:10 2020 by ROOT version 6.18/00
// from TChain evt/
//////////////////////////////////////////////////////////

#ifndef EvtSelector_h
#define EvtSelector_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TH2.h>

// Headers needed by this particular selector

class EvtSelector : public TSelector
{
public:
   TTreeReader fReader; //!the tree reader
   TTree *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   // TTreeReaderValue<Int_t> evtID = {fReader, "evtID"};
   TTreeReaderValue<Int_t> nPhotons = {fReader, "nPhotons"};
   // TTreeReaderValue<Int_t> totalPE = {fReader, "totalPE"};
   // TTreeReaderArray<Int_t> nPE = {fReader, "nPE"};
   // TTreeReaderArray<Float_t> energy = {fReader, "energy"};
   // TTreeReaderArray<Double_t> hitTime = {fReader, "hitTime"};
   // TTreeReaderArray<Int_t> pmtID = {fReader, "pmtID"};
   // TTreeReaderArray<Int_t> PETrackID = {fReader, "PETrackID"};
   // TTreeReaderValue<Float_t> edep = {fReader, "edep"};
   // TTreeReaderValue<Float_t> edepX = {fReader, "edepX"};
   // TTreeReaderValue<Float_t> edepY = {fReader, "edepY"};
   // TTreeReaderValue<Float_t> edepZ = {fReader, "edepZ"};
   // TTreeReaderArray<Int_t> isCerenkov = {fReader, "isCerenkov"};
   // TTreeReaderArray<Int_t> isReemission = {fReader, "isReemission"};
   // TTreeReaderArray<Int_t> isOriginalOP = {fReader, "isOriginalOP"};
   // TTreeReaderArray<Double_t> OriginalOPTime = {fReader, "OriginalOPTime"};
   // TTreeReaderValue<Int_t> nPMTs = {fReader, "nPMTs"};
   // TTreeReaderArray<Int_t> nPE_byPMT = {fReader, "nPE_byPMT"};
   // TTreeReaderArray<Int_t> PMTID_byPMT = {fReader, "PMTID_byPMT"};
   // TTreeReaderArray<Float_t> LocalPosX = {fReader, "LocalPosX"};
   // TTreeReaderArray<Float_t> LocalPosY = {fReader, "LocalPosY"};
   // TTreeReaderArray<Float_t> LocalPosZ = {fReader, "LocalPosZ"};
   // TTreeReaderArray<Float_t> LocalDirX = {fReader, "LocalDirX"};
   // TTreeReaderArray<Float_t> LocalDirY = {fReader, "LocalDirY"};
   // TTreeReaderArray<Float_t> LocalDirZ = {fReader, "LocalDirZ"};
   TTreeReaderArray<Float_t> GlobalPosX = {fReader, "GlobalPosX"};
   TTreeReaderArray<Float_t> GlobalPosY = {fReader, "GlobalPosY"};
   TTreeReaderArray<Float_t> GlobalPosZ = {fReader, "GlobalPosZ"};
   // TTreeReaderArray<Float_t> BoundaryPosX = {fReader, "BoundaryPosX"};
   // TTreeReaderArray<Float_t> BoundaryPosY = {fReader, "BoundaryPosY"};
   // TTreeReaderArray<Float_t> BoundaryPosZ = {fReader, "BoundaryPosZ"};
   TH2F *h2d;


   EvtSelector(TTree * /*tree*/ = 0)
   {
   }
   virtual ~EvtSelector() {}
   virtual Int_t Version() const { return 2; }
   virtual void Begin(TTree *tree);
   virtual void SlaveBegin(TTree *tree);
   virtual void Init(TTree *tree);
   virtual Bool_t Notify();
   virtual Bool_t Process(Long64_t entry);
   virtual Int_t GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void SetOption(const char *option) { fOption = option; }
   virtual void SetObject(TObject *obj) { fObject = obj; }
   virtual void SetInputList(TList *input) { fInput = input; }
   virtual TList *GetOutputList() const { return fOutput; }
   virtual void SlaveTerminate();
   virtual void Terminate();

   ClassDef(EvtSelector, 0);
};

#endif

#ifdef EvtSelector_cxx
void EvtSelector::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t EvtSelector::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef EvtSelector_cxx
