//目的：展示加入中子反冲非线性的对能谱的影响。
#include<TFile.h>
#include<TH1.h>
#include <TLegend.h>
double E_Lower = 1.807;             //energy threshold of IBD
double E_Upper = 10;               //energy cut for neutrino energy
double E_LP = 1.022;                //E_Lower-0.78233108;
double E_UP = E_Upper - 0.78233108; 

int show3d2dDiff()
{
    TH1D *h_old=0;
    TH1D *h_NLNR=0;
    TH1D *h_NL=0;
    TH1D *h_NR=0;
    TLegend leg(5,10);

    TFile *ff_old=TFile::Open("SoCallData_NO.root","READ");
    ff_old->GetObject("h_NMO",h_old);
    
    TFile *ff_NLNR=TFile::Open("WithNLNR.root","READ");
    ff_NLNR->GetObject("h_NMO",h_NLNR);
    h_NLNR->SetLineColor(kRed);

    TFile *ff_NL=TFile::Open("WithNL.root","READ");
    ff_NL->GetObject("h_NMO",h_NL);
    h_NL->SetLineColor(kRed);

    TFile *ff_NR=TFile::Open("WithNR.root","READ");
    ff_NR->GetObject("h_NMO",h_NR);
    h_NR->SetLineColor(kBlue);


    TH1D *h_2NL=new TH1D("h_2NL","",200,E_LP,E_UP);
    TH1D *h_2NR=new TH1D("h_2NR","",200,E_LP,E_UP);
    h_2NL->Divide(h_NL,h_old);
    h_2NR->Divide(h_NR,h_old);
    h_2NL->SetLineColor(kRed);
    h_2NR->SetLineColor(kBlack);
    h_2NL->SetYTitle("h_{new}/h_old");
    h_2NL->SetXTitle("E_{#nu}/MeV");
    h_2NL->Draw();
    h_2NR->Draw("SAME");

    // h_NLNR->Draw();
    // h_old->Draw("SAME");
    // h_NL->SetLineWidth(3);
    // h_old->SetYTitle("h_{new}/h_old");
    // h_old->SetXTitle("E_{#nu}/MeV");

    // h_old->Draw();
    // h_NR->Draw("SAME");
    // h_NL->Draw("SAME");
    // leg.AddEntry(h_old,"w/o neutron recoil and NL");
    // leg.AddEntry(h_NLNR,"w/ neutron recoil and NL");
    // leg.AddEntry(h_NL,"w/ NL");
    // leg.AddEntry(h_NR,"w/ neutron recoil");
    leg.AddEntry(h_2NR,"With n Recoil / no n Recoil");
    leg.AddEntry(h_2NL,"With nonlinearity/ no nonlinearity");

    leg.DrawClone("SAME");


    // TFile *ff_rr=TFile::Open("NLandNRImpact.root","RECREATE");
    // ff_rr->cd();
    // h_2NL->Write();
    // h_2NR->Write();
    // ff_rr->Close();

    return 0;
}