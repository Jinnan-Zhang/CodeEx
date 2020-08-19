#include "TRandom3.h"
#include "TF2.h"
#include "TMath.h"
#include "TH2D.h"
#include "TCanvas.h"

static const Double_t Me = 0.51099907;   
static const Double_t Q = 2.525;	       
static const Double_t Mr = 19559.31191; 
static const Double_t MI = Mr+Q+Me;  
static const Double_t a0 = 0.55;        

Double_t fcn(Double_t *x, Double_t* par) 
{

Double_t f,A1,Pe,Pr,Pnu,Cbn,Cbr,Per,Ee,Er;
Pe=x[0];
Pr=x[1];
f=0;
A1=-(sqrt(Pr*Pr+Mr*Mr)+sqrt(Pe*Pe+Me*Me)-MI);
Per=(A1*A1-Pe*Pe-Pr*Pr)/2;
if (A1>0 && Pe>0 && Pr>0)
{
Cbn=-(Pe*Pe+Per)/(Pe*A1);
Cbr=Per/(Pe*Pr);
if (Cbr>=-1 && Cbr<=1)
{
f= Pr*Pe*A1*(1+(a0*Pe*Cbn/sqrt(Pe*Pe+Me*Me)));
}
}
return f;
}

Double_t fcnt(Double_t *x2, Double_t* par) 
{
Double_t f2,A1,Pe,Pr,Pnu,Cbn,Cbr,Per,Ee,Er;
Pe=x2[0];
Pr=x2[1];
f2=0;
A1=-(sqrt(Pr*Pr+Mr*Mr)+sqrt(Pe*Pe+Me*Me)-MI);
Per=(A1*A1-Pe*Pe-Pr*Pr)/2;
if (A1>0 && Pe>0 && Pr>0)
{
Cbn=-(Pe*Pe+Per)/(Pe*A1);
Cbr=Per/(Pe*Pr);
if (Cbr>=-1 && Cbr<=1)
{
f2= Pr*Pe*A1*(1+(par[0]*Pe*Cbn/sqrt(Pe*Pe+Me*Me)))*1000000*par[1];
}
}
return f2;
}
 
void doit()   
{
  
  Double_t Ee;
  Double_t Er;
  if (gRandom) delete gRandom;
  gRandom = new TRandom3(0); 
   
  TCanvas* bcan=new TCanvas("bcan","events",300,10,900,800);  
  
  TF2 *func=new TF2("func",fcn,0,3,0,3,0);  
  TF2 *funct=new TF2("funct",fcnt,0,3,0,3,2);  
    
  TH2D* EeErf = new TH2D("EeEf","a=0.558 Counts",20,0,3,20,0,3);
  EeErf->Sumw2();
  
  bcan->Divide(1,2,0.1,0.01);  
  gStyle->SetPalette(1);         
     
  for (UInt_t h=0;h<1000000;h++)
	{
		func->GetRandom2(Ee,Er);
		EeErf->Fill(Ee,Er);
                }    
  bcan->cd(1);
  EeErf->Draw("zcol");
  funct->SetParameters(0.5,1);
  EeErf->Fit("funct","IV");
  bcan->cd(2); 
  funct->Draw("zcol");
 }
