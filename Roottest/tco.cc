#include <stdio.h>
#include <TMath.h>
#include <TCanvas.h>
#include <iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TObject.h>
#include <TRandom.h>
#include <TFile.h>
#include <math.h>
#include <TF1Convolution.h>
#include <TF1.h>
#include <TH1F.h>
#include <TGraph.h>
#include <TStopwatch.h>

int tco()
{
    TF1* f1=new TF1("f1","0.1*x^2+x-2*sin([0]*x)+[1]",-10,10);
    TF1* f2=new TF1("f2","gaus(0)",-20,20);
    TF1Convolution *f_conv=new TF1Convolution(f1,f2,-20,20,true);
    f_conv->SetRange(-20,20);
    f_conv->SetNofPointsFFT(1000);
    TF1 *f=new TF1("f",*f_conv,-10,10,f_conv->GetNpar());
    f1->SetParameters(7,1);
    //f2->SetParameters(1./(sqrt(6.28)*0.5),0,0.5);
    f->SetParameters(7,1,1./(sqrt(6.28)*0.2),0,0.2);
    f->SetLineColor(kBlue);
    f->SetNpx(200);
    f1->SetNpx(200);
    f1->Draw();
    
    f->Draw("SAME");
    return 0;
}