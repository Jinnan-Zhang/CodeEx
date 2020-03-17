//目的:展示能谱差异
#include<TFile.h>
#include<TH1.h>
#include <TLegend.h>
double E_Lower = 1.807;             //energy threshold of IBD
double E_Upper = 10;               //energy cut for neutrino energy
double E_LP = 1.022;                //E_Lower-0.78233108;
double E_UP = E_Upper - 0.78233108; 

int ShowNOIO()
{
    TH1::SetDefaultSumw2();
    TH1::AddDirectory(false);
    TFile *ff_NO=TFile::Open("SoCallData_NO.root","READ");
    TFile *ff_IO=TFile::Open("SoCallData_IO.root","READ");
    TH1D *h_NO=0,*h_IO=0;
    ff_NO->cd();
    ff_NO->GetObject("h_NMO",h_NO);
    ff_IO->cd();
    ff_IO->GetObject("h_NMO",h_IO);
    h_IO->SetLineColor(kBlue);
    TH1D *h_new0=new TH1D("h_ratio","",200,E_LP,E_UP);
    TH1D *h_new=new TH1D("h_ratio","",200,E_LP,E_UP);

    h_new0->Add(h_IO,h_NO,1.,-1.);
    h_new->Divide(h_new0,h_NO);
    h_new->SetLineColor(kRed);

    // h_NO->Draw();
    // h_IO->Draw("SAME");
    // h_IO->Draw();
    // h_new->Draw("SAME");
    h_new->Draw();
    TLegend leg(5,10);
    // leg.AddEntry(h_NO,"Normal Ordering");
    // leg.AddEntry(h_IO,"Invert Ordering");
    leg.AddEntry(h_new,"(IH-NH)/NH");
    leg.DrawClone("SAME");
    TFile *ff_r=TFile::Open("NOIOratio.root","RECREATE");
    ff_r->cd();
    h_new->Write();
    h_NO->SetName("h_NO");
    h_NO->Write();
    h_IO->SetName("h_IO");
    h_IO->Write();
    ff_r->Close();
    return 0;

}