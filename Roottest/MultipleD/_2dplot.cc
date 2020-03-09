#include <TF2.h>
#include <TH2.h>
#include <TMath.h>

int _2dplot()
{
    TF2 *f2=new TF2("f2","3.298076/sqrt(x)*TMath::Exp(-10*((x-y)/sqrt(x))^2)",1,10,1,10);
    TH2D *h1=new TH2D("h1","",1000,1.05,10,1000,1.05,10);
    h1->FillRandom("f2",1e6);
    h1->SetXTitle("E_{dep}/MeV");
    h1->SetYTitle("E_{rec}/MeV");
    // h1->Scale(1/h1->Integral());
    h1->Draw("Colz");
    // f2->SetNpx(1000);
    // f2->SetNpy(1000);
    // f2->Draw("COLZ");
    return 0;
}
//目的：绘制较为直观的二维图