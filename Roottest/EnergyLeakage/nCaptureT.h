//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Apr 11 14:45:15 2020 by ROOT version 6.18/00
// from TChain nCapture/
//////////////////////////////////////////////////////////

#ifndef nCaptureT_h
#define nCaptureT_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector
#include <vector>



class nCaptureT : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Int_t> evtID = {fReader, "evtID"};
   TTreeReaderArray<int> NeutronTrkid = {fReader, "NeutronTrkid"};
   TTreeReaderArray<float> NeutronKine = {fReader, "NeutronKine"};
   TTreeReaderArray<double> NeutronCaptureT = {fReader, "NeutronCaptureT"};
   TTreeReaderArray<float> NCStartX = {fReader, "NCStartX"};
   TTreeReaderArray<float> NCStartY = {fReader, "NCStartY"};
   TTreeReaderArray<float> NCStartZ = {fReader, "NCStartZ"};
   TTreeReaderArray<float> NCStopX = {fReader, "NCStopX"};
   TTreeReaderArray<float> NCStopY = {fReader, "NCStopY"};
   TTreeReaderArray<float> NCStopZ = {fReader, "NCStopZ"};
   TTreeReaderArray<float> NCTrackLength = {fReader, "NCTrackLength"};
   TTreeReaderArray<int> trkid = {fReader, "trkid"};
   TTreeReaderArray<int> pdgid = {fReader, "pdgid"};
   TTreeReaderArray<float> kine = {fReader, "kine"};
   TTreeReaderArray<float> px = {fReader, "px"};
   TTreeReaderArray<float> py = {fReader, "py"};
   TTreeReaderArray<float> pz = {fReader, "pz"};
   TTreeReaderArray<float> x = {fReader, "x"};
   TTreeReaderArray<float> y = {fReader, "y"};
   TTreeReaderArray<float> z = {fReader, "z"};
   TTreeReaderArray<double> t = {fReader, "t"};


   nCaptureT(TTree * /*tree*/ =0) { }
   virtual ~nCaptureT() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(nCaptureT,0);

};

#endif

#ifdef nCaptureT_cxx
void nCaptureT::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t nCaptureT::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef nCaptureT_cxx
