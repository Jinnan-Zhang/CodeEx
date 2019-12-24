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
void average()
{
// argv[1] - FileName
// argv[2] - Number of Events ( "-1" - All events)  
  
 //gROOT->Reset();
 //gROOT->Clear();


  // TCanvas *C=new TCanvas("C","C",600,500);
   //C->SetGrid();

   ifstream in;
   TString filename="ch1.txt";

   in.open(filename, ios::in);
	if  (!in.good()) 
	{ 
		cout<<"!!! File reading error:"<<endl;
		return 0;
	}



const int iPoints = 2051;
int iSig[iPoints];	
int iAverageSig[iPoints];

int iNumEvent = 0;
int iNumFrames = 0;

iNumFrames =9996 ;
if (iNumFrames == -1) iNumFrames = 10000000;

for (int i = 0; i < iPoints; i++) 
{ 
  iAverageSig[i] = 0;
  iSig[i] = 0; 
}

char cEventSize[50];
char cEventCounter[50];
char cTriggerTimeStamp[100];

TH1F *hist=new TH1F("Gate","Gate",iPoints+0.5,-0.5,iPoints);

  while (iNumEvent < iNumFrames)
{
	if (!in.good()){cout<<"ATTENTION!!!! it is in.good()"<<endl; break;}
	
	in>>cEventSize;
	in>>cEventCounter;
	in>>cTriggerTimeStamp;
	//cout << "Event Size: " << cEventSize << endl;
	//cout << "Event counter: " << cEventCounter << endl;
	//cout << "Trigger stamp: " << cTriggerTimeStamp << endl;
	
	for (int i = 0; i < iPoints; i++)
	{
		in>>iSig[i];
		//cout<<iSig[i]<<endl;
		
		iAverageSig[i]+=iSig[i];
	}
		iNumEvent++; 
}
in.close();	

/*TApplication theApp("ADCMGateControl",  &argc, argv); 
  if(gROOT->IsBatch())
    {
      fprintf(stderr, "%s: cannot run in batch mode\n", argv[0]);
      return 1;
    }
 */
    cout << "Number of points = " << iPoints << endl;
    cout << "iNumEvent: "<< iNumEvent << endl;
  
for (int i = 0; i < iPoints; i++)	hist->SetBinContent(i+1,(double)iAverageSig[i]/iNumEvent);
//cout<<iDig[2050]<<endl;
//cout<<Record<<Length<<iRecLength<<endl;
//cout<<BoardID<<Id<<endl;
//cout<<Channel<<iChan<<endl;
//cout<<Event<<Number<<iEvent<<endl;
//cout<<Pattern<<cPattern<<endl;
//cout<<Trigger<<Time<<Stamp<<iTrig<<endl;
//cout<<DC<<offset<<DAC<<cDC<<endl;

   
//gStyle->SetStatFormat("6.4f");
//gStyle->SetOptStat("inemr");
   hist->Draw("PL");//
/*
TF1 *f1=new TF1("f1","gaus",280,310);//
      TF1 *f2=new TF1("f2","gaus",320,440);//
      hist->Fit(f1,"R+");//
      hist->Fit(f2,"R+");
 Double_t par[6];
f1->GetParameters(&par[0]);
f2->GetParameters(&par[3]);  




TF1 *f4 = new TF1("f4","[7]*((1-[0])/([1]*pow(2*TMath::Pi(),0.5))*exp(-0.5*((x-[2])/[1])**2)*exp(-[3])+[0]*[4]*exp(-[3]-[4]*(x-[2]))+[3]*exp(-[3])/([5]*pow(2*TMath::Pi(),0.5))*exp(-0.5*((x-[6])/[5])**2))",291,400);
     
      f4->SetParNames("w","#sigma_{0}","Q_{0}","#mu","#alpha","#sigma_{1}","Q_{1}","Const");
      
      f4->SetParameter(0,0.1);//
      f4->SetParameter(1,par[2]);
      f4->SetParameter(2,par[1]);
      f4->SetParameter(3,0.1);
      f4->SetParameter(4,1);
      f4->SetParameter(5,1);
      f4->SetParameter(6,par[4]);
      f4->SetParameter(7,counts);
   hist->Fit(f4,"R");
Float_t min,max,gain,pv,rde,resolution,minx;
max=f4->GetMaximum(par[4]-10,par[4]+10);
min=f4->GetMinimum(120,220);
pv=max/min;
//rde=1-exp(-1*(f4->GetParameter(3)));
gain=250000*(par[4]-par[1])/1.6;
resolution=par[5]/(par[4]-par[1]);
Float_t spe_counts,spe_percent;
minx=f4->GetMinimumX(120,220);
spe_counts=hist->Integral(minx,4096);
spe_percent=spe_counts/counts;
cout<<minx<<"\t"<<counts<<endl;
output<<pv<<"\t"<<gain<<"	"<<spe_percent<<"	"<<resolution<<endl;
*/
//if (gROOT->IsBatch()) return 1;
//TBrowser *Browser =  new TBrowser();
//theApp.Run();
//return 1;


}
