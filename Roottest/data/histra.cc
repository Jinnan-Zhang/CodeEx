#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TLegend.h>
#define NumBins 200
double E_LP = 1.022;    //E_Lower-0.78233108;
double E_UP = 9.217;    //E_Upper-0.78233108;//energy cut for prompt energy

int histra()
{
    
    TFile *f_YBNO=TFile::Open("NOYB.root","READ");
    TFile *f_YBIO=TFile::Open("IOYB.root","READ");
    TFile *f_2019NO=TFile::Open("NO2019.root","READ");
    TFile *f_2019IO=TFile::Open("IO2019.root","READ");
    TH1 *ht=0;
    TH1D *h_NO_YB=new TH1D("YB0","YB NH/IH",NumBins,E_LP,E_UP);
    // TH1D *h_IO_YB=new TH1D("YB1","YB IH",NumBins,E_LP,E_UP);
    TH1D *h_NO_2019=new TH1D("2019NH","Nu-fit 2019 NH/IH",NumBins,E_LP,E_UP);
    
    double tNO,tIO;
    double raYB[NumBins];

    for(int i=0;i<NumBins;i++)
    {
        f_YBNO->cd();
        f_YBNO->GetObject("h_NMO",ht);
        tNO=ht->GetBinContent(i+1);
        f_YBIO->cd();
        f_YBIO->GetObject("h_NMO",ht);
        tIO=ht->GetBinContent(i+1);
        raYB[i]=tNO/tIO;
        h_NO_YB->SetBinContent(i+1,raYB[i]);

        f_2019NO->cd();
        f_2019NO->GetObject("h_NMO",ht);
        tNO=ht->GetBinContent(i+1);
        f_2019IO->cd();
        f_2019IO->GetObject("h_NMO",ht);
        tIO=ht->GetBinContent(i+1);
        raYB[i]=tNO/tIO;
        h_NO_2019->SetBinContent(i+1,raYB[i]);

    }
    int co=1;
    h_NO_YB->SetLineColor(co++);
    // h_IO_YB->SetLineColor(co++);
    h_NO_YB->SetLineWidth(3);
    h_NO_YB->Draw();
    h_NO_2019->SetLineColor(co++);
    h_NO_2019->SetLineWidth(3);
    h_NO_2019->Draw("SAME");
    TLegend leg(5,10);
    leg.AddEntry(h_NO_YB,"Yellow Book NH/IH \"data\" ratio");
    leg.AddEntry(h_NO_2019,"Nu-fit 2019 NH/IH \"data\" ratio");
    leg.DrawClone("SAME");
    // h_IO_YB->Draw("SAME");

    return 0;
}