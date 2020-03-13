//目的：展示加入中子反冲非线性的对能谱的影响。
#include<TFile.h>
#include<TH1.h>
#include <TLegend.h>

int show3d2dDiff()
{
    TH1D *h_old=0;
    TH1D *h_NLNR=0;
    TH1D *h_NR=0;

    TFile *ff_old=TFile::Open("SoCallData_NO.root","READ");
    ff_old->GetObject("h_NMO",h_old);
    
    TFile *ff_NLNR=TFile::Open("WithNLNR.root","READ");
    ff_NLNR->GetObject("h_NMO",h_NLNR);
    h_NLNR->SetLineColor(kRed);
    TFile *ff_NR=TFile::Open("WithNR.root","READ");
    ff_NR->GetObject("h_NMO",h_NR);
    h_NR->SetLineColor(kBlue);

    h_NLNR->Draw();
    h_old->Draw("SAME");
    h_NR->Draw("SAME");
    TLegend leg(5,10);
    leg.AddEntry(h_old,"w/o neutron recoil and NL");
    leg.AddEntry(h_NLNR,"w/ neutron recoil and NL");
    leg.AddEntry(h_NR,"w/ neutron recoil");
    leg.DrawClone("SAME");

    return 0;
}