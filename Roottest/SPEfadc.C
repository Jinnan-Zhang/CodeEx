//#include <TApplication.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <TTree.h>
#include <TFile.h>
#include <TMath.h>
#include <TH1.h>
#include <TF1.h>
#include <TROOT.h>
#include <TBrowser.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <TGraph.h>
#include <ctime>
#include <iomanip>

using namespace std;

//par[0] â€?par[7] - "#mu","Pedestal","Sigma of pedestal","Norm","Gain","Sigma of the 1st peak","w","#alpha"

/*Double_t FullGaus(Double_t *x, Double_t *par) {
   Double_t Qsh = 0;
    Qsh = par[6]/par[7];
Double_t arg = 0;
if (par[2] != 0) arg = (x[0] - par[1])/par[2];
Double_t arg1 = 0;
if (par[2] != 0) arg1 = (x[0] - (par[1]+  par[4]) - Qsh)*(x[0] - (par[1]+par[4])   - Qsh)/(par[2]*par[2]+par[5]*par[5]);
Double_t arg2 = 0;
if (par[2] != 0) arg2 = (x[0] - (par[1]+2*par[4]) - Qsh)*(x[0] - (par[1]+2*par[4]) - Qsh)/(2*(par[2]*par[2]+par[5]*par[5]));
Double_t arg3 = 0;
if (par[2] != 0) arg3 = (x[0] - (par[1]+3*par[4]) - Qsh)*(x[0] - (par[1]+3*par[4]) - Qsh)/(3*(par[2]*par[2]+par[5]*par[5]));
Double_t arg4 = 0;
if (par[2] != 0) arg4 = (x[0] - (par[1]+4*par[4]) - Qsh)*(x[0] - (par[1]+4*par[4]) - Qsh)/(4*(par[2]*par[2]+par[5]*par[5]));
Double_t arg5 = 0;
if (par[2] != 0) arg5 = (x[0] - (par[1]+5*par[4]) - Qsh)*(x[0] - (par[1]+5*par[4]) - Qsh)/(5*(par[2]*par[2]+par[5]*par[5]));
			 
Double_t pi = 3.1415;
Double_t A0 = ( par[3]*(1-par[6])*TMath::Exp(-par[0]) ) / ( par[2]*sqrt(2*pi) );
Double_t A1 = ( par[3]*TMath::Exp(-par[0])*par[0] ) / ( sqrt(2*pi*(par[2]*par[2]+par[5]*par[5]) ) );
Double_t A2 = par[3]*TMath::Exp(-par[0])*pow(par[0],2) / 2/( sqrt(4*pi*(par[2]*par[2]+par[5]*par[5]) ) );
Double_t A3 = par[3]*TMath::Exp(-par[0])*pow(par[0],3) / 6/( sqrt(6*pi*(par[2]*par[2]+par[5]*par[5]) ) );
Double_t A4 = par[3]*TMath::Exp(-par[0])*pow(par[0],4) / 24/( sqrt(8*pi*(par[2]*par[2]+par[5]*par[5]) ) );
Double_t A5 = par[3]*TMath::Exp(-par[0])*pow(par[0],5) / 120/( sqrt(10*pi*(par[2]*par[2]+par[5]*par[5]) ) );

Double_t noise = 0;
Double_t Tetha = 0;
noise = par[6]*par[7]*TMath::Exp(-par[7]*(x[0] - par[1]))*TMath::Exp(-par[0]); 
Tetha = 0.5*(1+TMath::Erf( (x[0] - par[1]) / sqrt(2)/par[2] ));

Double_t fitval = par[3]*Tetha*noise + A0*TMath::Exp(-0.5*arg*arg) + A1*TMath::Exp(-0.5*arg1) + A2*TMath::Exp(-0.5*arg2) + A3*TMath::Exp(-0.5*arg3)  + A4*TMath::Exp(-0.5*arg4) + A5*TMath::Exp(-0.5*arg5);
    return fitval;    
}
*/
void SPEfadc()
{
// argv[1] - FileName
// argv[2] - Start point of integration range
// argv[3] - End point of integration range 
// argv[4] - Number of Events ( "-1" - All events)  
 
  //gROOT->Reset();
 //gROOT->Clear();
  
int iStartGate =1034;
int iEndGate = 1120;
  
int iNumEvent = 0;
int iNumFrames = 0;

iNumFrames = 20000;
if (iNumFrames == -1) iNumFrames = 10000000;

  // TCanvas *C=new TCanvas("C","C",600,500);
   //C->SetGrid();
  //cout<<argv[1]<<endl;
   ofstream output("result.txt",ios::trunc);
   ifstream in;TString filename="ch1.txt";

   in.open(filename, ios::in);
	if  (!in.good()) 
	{ 
		cout<<"!!! File reading error:"<<endl;
		return 0;
	}
const int Nbins = 2000;

TH1F *hist=new TH1F("Charge","Charge",Nbins+0.5,-0.5,Nbins);

const int iPoints = 2051;

int iSig[iPoints];	
int iIntegral = 0;
int iPed = 0;
int iCharge = 0;

//check the program;
for (int i = 0; i < iPoints; i++) 
{ 
  iSig[i] = 0; 
}

char cEventSize[50];
char cEventCounter[50];
char cTriggerTimeStamp[100];

  while (iNumEvent < iNumFrames)
{
	if (!in.good()){cout<<"ATTENTION!!!! it is in.good()"<<endl; break;}

	in>>cEventSize;
	in>>cEventCounter;
	in>>cTriggerTimeStamp;
        //cout<<cEventCounter<<endl;
	
	for (int i = 0; i < iPoints; i++)
	{
		in>>iSig[i];
		//cout<<iSig[i]<<endl;
	}
	
	for (int i = iStartGate; i < iEndGate + 1; i++) iIntegral += iSig[i]; // Integral of signal calculation
	for (int i = (iStartGate-200-(iEndGate-iStartGate)); i < (iStartGate - 200 + 1); i++) iPed += iSig[i]; // Pedestal calculation
	iCharge = iIntegral - iPed; 
	
	//cout<<"Start: "<<(iStartGate-200-(iEndGate-iStartGate))<<endl;
	//cout<<"End: "<<(iStartGate-200+1)<<endl;
	
	//cout<<"iIntegral: "<<iIntegral<<endl;
	//cout<<"iPed: "<<iPed<<endl;
	
	//cout<<"iCharge: "<<iCharge<<endl;
	//
	//remove the ped from 0 to some distance 100;
	hist->Fill((-iCharge+100)); // We have negative signal that's why "-iCharge" 
       // if((-iCharge)+100<-0.5||(-iCharge)+100>1000)  cout<<"NumberEvent : "<<iNumEvent<<"     Charge : "<<(-iCharge)+100<<endl;
	// to make the charge intergral and ped and signal for next time  0
	iCharge = 0;
	iIntegral = 0;
	iPed = 0;
	for (int i = 0; i < iPoints; i++)
	{
		iSig[i]= 0;
		//cout<<iSig[i]<<endl;
	}
	iNumEvent++;
}
in.close();	

//TApplication theApp("ADCMGateControl",  &argc, argv); 
//  if(gROOT->IsBatch())
//    {
//    fprintf(stderr, "%s: cannot run in batch mode\n", argv[0]);
//  return 1;
// }
    
    cout << "Number of points = " << iPoints << endl;
    cout << "iNumEvent: " << iNumEvent << endl;

//cout<<iDig[2050]<<endl;
//cout<<Record<<Length<<iRecLength<<endl;
//cout<<BoardID<<Id<<endl;
//cout<<Channel<<iChan<<endl;
//cout<<Event<<Number<<iEvent<<endl;
//cout<<Pattern<<cPattern<<endl;
//cout<<Trigger<<Time<<Stamp<<iTrig<<endl;
//cout<<DC<<offset<<DAC<<cDC<<endl;

  //   TF1 *f1 = new TF1("Full Gaus",FullGaus,80,400,8);
     
 //     f1->SetParNames("#mu","Pedestal","Sigma of pedestal","Norm","Gain","Sigma of the 1st peak","w","#alpha");
      
/*      f1->SetParameter(0,0.2);  // mu
      f1->SetParameter(1,101);   // Pedestal
      f1->SetParameter(2,7);    // Sigma of pedestal
      f1->SetParameter(3,15000);// Norm
      f1->SetParameter(4,50);   //Gain
      f1->SetParameter(5,20);   //Sigma of 1st peak
      f1->SetParameter(6,0.2);  // w
      f1->SetParameter(7,0.04);// alpha
      //hist->Fit(f1,"R");
*/ 
gStyle->SetOptFit(1);  
gStyle->SetStatFormat("6.4f");
gStyle->SetOptStat("inemr");
gStyle->SetFitFormat("6.4f");
 // hist->SetOption("Show Fit Parameters");
     hist->Draw();



      TF1 *f1=new TF1("f1","gaus",50,120);
      TF1 *f3=new TF1("f3","expo",120,180);
      TF1 *f2=new TF1("f2","gaus",180,1100);
     f3->SetLineColor(kBlue);
      hist->Fit(f1,"R+");
      hist->Fit(f3,"R+");
      hist->Fit(f2,"R+");
 Double_t par[8];
 float counts=0;
f1->GetParameters(&par[0]);
f1->GetParameters(&par[3]);
f2->GetParameters(&par[5]);  
cout<<par[6]<<"\t"<<par[1];
//TF1 *f4 = new TF1("f4","[7]*((1-[0])/([1]*pow(2*TMath::Pi(),0.5))*exp(-0.5*((x-[2])/[1])**2)*exp(-[3])+[0]*[4]*exp(-[3]-[4]*(x-[2]))+[3]*exp(-[3])/([5]*pow(2*TMath::Pi(),0.5))*exp(-0.5*((x-[6])/[5])**2))",210,300);
     TF1 *f4=new TF1("f4","[0]*exp(-0.5*(x-[1])*(x-[1])/([2]*[2]))+[3]*exp(-x*[4])+[5]*exp(-0.5*(x-[6])*(x-[6])/([7]*[7]))",50,1100);
//      f4->SetParNames("w","#sigma_{0}","Q_{0}","#mu","#alpha","#sigma_{1}","Q_{1}","Const");
//      f4->SetParameters(par[0],par[1],par[2],par[3],par[4],par[5],par[6],par[7]);
   	 f4->SetParameters(par); 
   	 f4->SetLineColor(kGreen);
    
        hist->Fit(f4,"R+");
        f4->GetParameters(par);
	Float_t min,max,gain,pv,rde,resolution,minx;
	max=f4->GetMaximum(par[6]-par[7],par[6]+par[7]);
	min=f4->GetMinimum(par[1],par[6]);
	pv=max/min;

	gain=(1000./1024)*200000*(par[6]-par[1])/1.6;
	resolution=par[7]/(par[6]-par[7]);
	Float_t spe_counts,spe_percent;
	minx=f4->GetMinimumX(par[1],par[6]);
	counts=hist->Integral(0,300);
	spe_counts=hist->Integral(minx/2,300);
	spe_percent=spe_counts/counts;
	cout<<gain<<"\t"<<pv<<endl;
	output<<pv<<"\t"<<gain<<"	"<<spe_percent<<"	"<<resolution<<endl;



}
