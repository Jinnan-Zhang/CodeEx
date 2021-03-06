/// \file
/// \ingroup tutorial_fit
/// \notebook -js
/// Tutorial for convolution of two functions
///
/// \macro_image
/// \macro_output
/// \macro_code
///
/// \author Aurelie Flandi

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

using namespace std;

void fitConvolution()
{
   // //construction of histogram to fit
   // TH1F *h_ExpGauss = new TH1F("h_ExpGauss","Exponential convoluted by gaussian",100,0.,5.);
   // for (int i=0;i<1e6;i++)
   // {
   //    Double_t x = gRandom->Exp(1./0.3);//gives a alpha of -0.3 in the exp
   //    x += gRandom->Gaus(0.,3.);
   //    h_ExpGauss->Fill(x);//probability density function of the addition of two variables is the convolution of 2 dens. functions
   // }

   TF1Convolution *f_conv = new TF1Convolution("0.1*x^2+x-2*sin(7*x)","gaus",-1,6,true);
   f_conv->SetRange(-1.,6.);
   f_conv->SetNofPointsFFT(1000);
   TF1   *f = new TF1("f",*f_conv, 0., 5., f_conv->GetNpar());
   f->SetParameters(-0.3,0.,1.);
   f->Draw();

   //fit
   // new TCanvas("c","c",800,1000);
   // h_ExpGauss -> Fit("f");
   // h_ExpGauss->Draw();

}
