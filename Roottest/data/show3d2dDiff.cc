//目的：展示加入中子反冲非线性的对能谱的影响。
#include<TFile.h>
#include<TH1.h>
#include <TLegend.h>

int show3d2dDiff()
{
    TH1D *h_old=0;
    TH1D *h_new=0;
    TFile *ff_old=TFile::Open("SoCallData_NO_OLD.root","READ");
    TFile *ff_new=TFile::Open("SoCallData_NO.root","READ");
    ff_old->GetObject("h_NMO",h_old);
    ff_new->GetObject("h_NMO",h_new);
    h_new->SetLineColor(kRed);
    h_new->Draw();
    h_old->Draw("SAME");
    TLegend leg(5,10);
    leg.AddEntry(h_old,"w/o neutron recoil and NL");
    leg.AddEntry(h_new,"w/ neutron recoil and NL");
    leg.DrawClone("SAME");

    return 0;
}