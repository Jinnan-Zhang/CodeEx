#include <TTimeStamp.h>
#include <TFile.h>
#include <TTree.h>
#include <vector>

int TimeStmp()
{
    TFile *ff_out = TFile::Open("TT.root", "RECREATE");
    TTree *t_Time = new TTree("tTime", "test TimeStamp");
    // std::vector<TTimeStamp> t;
    std::vector<float> t;
    // TTimeStamp t0;
    // TTimeStamp t1;
    // t.emplace_back(t0);
    // t.emplace_back(t1);
    t_Time->Branch("TTimeStamp",&t);
    t_Time->Fill();
    t_Time->Write();
    ff_out->Close();

    return 0;
}