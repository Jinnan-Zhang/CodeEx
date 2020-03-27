
#include"TTree.h"
#include"TFile.h"
#include"TGraph.h"
#include"TH2.h"
#include"TH1.h"
#include"TF1.h"
#include"TBranch.h"
#include"TLegend.h"
#include"TCanvas.h"
#include"TStyle.h"
#include"string.h"
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<sstream>
#include<fstream>
#include<cmath>
#include<map>
#include"PMT_Contain.h"
#include "TVirtualFFT.h"
using  std::cout;
using  std::cin;

void container()
{   
   Double_t HiVol[36]={0};
   ifstream HV_in;
   HV_in.open("HV.txt",ios::in);
   
   Double_t temp=0;int ii=0;
   for(ii=0;ii<36;++ii)
   {
      HV_in>>temp;HV_in>>HiVol[ii];
   }
   HV_in.close();
  
   Double_t Gain_pmt[36][10]={0},HV_pmt[36][10]={0};

   string filename1;

   //string file_A="/pmtfs/disk01/container_data/calibrationSetPointTesting/";
   //string file_A="/junofs/PmtCharacterization/container_data/calibrationSetPointTesting/";
   string file_A="/junofs/PmtCharacterization/container_data/Meassurements_DAQ/";
   ////////////////////////////////////////////////////////////////
   //     #_part###.txt   
   //     # and ### can be changed!We select the path in this way!
   ////////////////////////////////////////////////////////////////

   string filename_id="#";
   string filename2="_part";
   string filename_pa="###";
   string filename3=".dat";
   string filename;
   

   int RUN = 0;
   cin>>RUN;
   int    FIRST_PMT=136,LAST_PMT=136;
   int    LogGain_HV_Need=0;
   int    begin_file_num=0;
   int    NUM_FILE=0;
   char   ORDER[20];
   char parameters_fn[200];
   Double_t  BEGIN_HV=0;
   Double_t fit_n=0;
   int N_id=0;
   

   Double_t HV_temp=0;
   int Container_temp = 0;
   string SET_TEMP=" ";


for(int run=RUN;run<=RUN;++run) {
   
    std::vector<string> PATH;
    std::vector<Double_t> HV_PPINT;
    //std::vector<int> Container_Id;
    std::map<int, int> Container_Id;

    char runInfo_fn[200];
    sprintf(runInfo_fn,"input_mass%d.txt", run);
    ifstream FileInfo;
    FileInfo.open(runInfo_fn, ios::in);

    FileInfo>>SET_TEMP;
    if(SET_TEMP=="FIRST_PMT") FileInfo>>FIRST_PMT;
    else {cout<<"---------------FIRST_PMT FileInfo WRONG!-------------------";exit(0);}

    FileInfo>>SET_TEMP;
    if(SET_TEMP=="LAST_PMT") FileInfo>>LAST_PMT;
    else {cout<<"---------------LAST_PMT FileInfo WRONG!-------------------";exit(0);}

    FileInfo>>SET_TEMP;
    if(SET_TEMP=="ORDER") FileInfo>>ORDER;
    else {cout<<"---------------ORDER FileInfo WRONG!-------------------";exit(0);}


    int pathNum = 0;
    FileInfo>>SET_TEMP;
    if(SET_TEMP=="PATH")
    {
        while(FileInfo>>SET_TEMP)
        {
            PATH.push_back(SET_TEMP);
            FileInfo>>Container_temp;
            //Container_Id[Container_temp] = pathNum;
            Container_Id[pathNum] = Container_temp;
            pathNum++;
        }
    }

   else {cout<<"---------------PATH   FileInfo WRONG!-------------------";exit(0);}
   if(pathNum!=PATH.size())
        {cout<<"---------------NUM_PATH FileInfo WRONG!-------------------";exit(0);}
   //int end_file_num=PATH.size();
   int end_file_num = begin_file_num + 1;
 


    TFile Container_resultf_Charge(Form("%sRun%d_Charge_Result.root",ORDER,run),"RECREATE");
    TFile Container_resultf_Amp(Form("%sRun%d_Amp_Result.root",ORDER,run),"RECREATE");   
    
    for(ii=begin_file_num;ii<end_file_num;++ii)
    {

      TFile* FitResults = new TFile(Form("%sRun%d_FitResults.root", ORDER, run),"RECREATE");
      sprintf(parameters_fn,"%sRun%d_Parameters.txt", ORDER, run);

      ofstream Parameter_out;
      Parameter_out.open(parameters_fn, ios::out);
      
      Parameter_out<<"PMTid"<<'\t'<<"Mu"<<'\t'<<"Gain"<<'\t'<<"riset"<<'\t'<<"fallt"<<'\t'<<"Res"<<'\t'<<"P/V"<<'\t'
                   <<"Threshold"<<'\t'<<"Mbx1"<<'\t'<<"Sigma_PDT"<<'\t'<<"Mbx2"<<'\t'<<"Sigma_SPE"<<endl;
    

      int i=0,j=0,k=0,Tk=0,pmtid=0;
      Double_t amp=0;
      char charAmp[4];
      Double_t PMTParameters[10]={0};
       
      int MuN=0,MuN2=0;
      for(int pid=FIRST_PMT;pid<=LAST_PMT;pid++)
      {  
    
         pmtid = Container_Id[pid];
         filename1=file_A+PATH[pid];
         cout<<"PMT_"<<pmtid<<'\t'<<pid<<endl;
          
         //TFile *Container_resultf=new TFile(an,"RECREATE");
         Container_resultf_Amp.cd();   
         TTree *Container_Amptree=new TTree(Form("Amp_Pmt%d", pmtid),"Tree of container_data");
         Double_t wave_arr[Wnum]={0},time_arr[Wnum]={}, amp_total[Wnum]={};
         Container_Amptree->Branch("wave_arr",wave_arr,"wave_arr[501]/D");
         Container_Amptree->Branch("time_arr",time_arr,"time_arr[501]/D");  
         

         for(i=1;i<=4;i++)
         {
            stringstream sspart; sspart<<i;
            filename_pa=sspart.str();
            filename=filename1 + filename2 + filename_pa + filename3;
            cout<<"Processing File ==>"<<filename<<endl;
            const char *pmt_fn=filename.c_str();
            ifstream pmtdata;
            pmtdata.open(pmt_fn, ios::in | ios::binary);
            j=0;


            char amptemp;
            bool find_begin = false;
            while(pmtdata.read(charAmp, sizeof(float)))
            {  
               amptemp = charAmp[0];
               charAmp[0] = charAmp[3];
               charAmp[3] = amptemp;
               amptemp = charAmp[1];
               charAmp[1] = charAmp[2];
               charAmp[2] = amptemp;

               amp = (*reinterpret_cast<float*>(charAmp))/10000.;
               //cout<<amp<<endl;
               if(amp<1e-20) {find_begin=true; continue;}
               if(!find_begin) continue;

               amp_total[j] += double(amp);
               wave_arr[j]=amp; time_arr[j]=j;
               if(j==Wnum-1) {Container_Amptree->Fill(); Tk++; find_begin=false; j=-1;}
               j++;
            }
            cout<<"TotalEvt ==>"<<Tk<<endl;
            pmtdata.close();

         }

         Container_Amptree->Write();
        
         TTree *Amp_analysis=(TTree *)Container_resultf_Amp.Get(Form("Amp_Pmt%d",pmtid));
         Double_t w_axis[Wnum]={},t_axis[Wnum]={};
         Amp_analysis->SetBranchAddress("wave_arr", w_axis); 
         Amp_analysis->SetBranchAddress("time_arr", t_axis);
       

         Container_resultf_Charge.cd(); //Important!!!
         TTree *Container_result=new TTree(Form("Rebuild_Pmt%d", pmtid),"the analysis result  of container_data");
         Double_t charge=0,Rise_time=0,Fall_time=0;
         Container_result->Branch("charge",&charge,"charge/D");
         Container_result->Branch("Rise_time",&Rise_time,"Rise_time/D");
         Container_result->Branch("Fall_time",&Fall_time,"Fall_time/D");

         
         TH1F *hRise_time=new TH1F("Rise_time","Time Information",   t_bin_num,tbina,tbinb);
         TH1F *hFall_time=new TH1F("Fall_time","Time Information",   t_bin_num,tbina,tbinb);
         TH1F *hcharge=new TH1F(Form("Charge_Spectrum_run%d_pmtid%d", run, pmtid), Form("Charge_Spectrum_run%d_pmtid%d", run, pmtid), bin_num,bina,binb);
 
         int Entries=Amp_analysis->GetEntries();
         cout<<"Entries:"<< Entries<<endl;       
         
         for(int kk=0;kk<Wnum;kk++) {amp_total[kk] /= double(Entries);}
         TGraph* SumWave=new TGraph(Wnum, time_arr, amp_total);
         SumWave->SetName(Form("SumWave_run%d_pmtid%d", run, pmtid));
         SumWave->Write();
         //for(int j=0;j<Wnum;j++) cout<<amp_total[j]<<endl;

         
         double WaveNum = 0;
         int FSR_HALF=55;
         int FSL_HALF=20;
         int Tmax_bin=v_min_get(amp_total);
         Double_t RISET[10000]={0},AMPT[10000]={0};int ai=0;
         Double_t Move_Peak_W[310]={0},T_Move[310]={0};for(int iii=0;iii<310;++iii){T_Move[iii]=iii;}
         TH2D* hFreq2D = new TH2D(Form("FrqySpec_run%d_pmtid%d", run, pmtid), Form("FrqySpec_run%d_pmtid%d", run, pmtid), Wnum, 0., Wnum, 2000, 0., 2000);
         for(k=0;k<Entries;++k)
         {
            Amp_analysis->GetEntry(k);
 
         //////////
         // [PartA]
         //////////
            Double_t sum=0, base=0; 
            for(i=Tmax_bin-125;i<Tmax_bin-50;++i) {sum=sum+w_axis[i];}
            base=sum/75.;
            for(i=0;i<Wnum;++i){w_axis[i]=-w_axis[i]+base;}
          
            int   max_bin=v_max_get(w_axis,10,Wnum-30);
            Double_t v_max=w_axis[max_bin];
            Double_t t_max=t_axis[max_bin];
            
            int fbin=0;
            int *p_fbin=&fbin; 

            if(v_max>6 && max_bin>Tmax_bin-FSL_HALF && max_bin<Tmax_bin+FSR_HALF) {
              
                Int_t n_size = Wnum+1;
                double* WaveD = new Double_t[Wnum]; //!!!!!!!!!!!!
                for(int i=0;i<Wnum;++i) WaveD[i] = w_axis[i];
            
                
                TVirtualFFT *fft_own = TVirtualFFT::FFT(1, &n_size, "R2C ES K");
                if (!fft_own) return;
                fft_own->SetPoints(WaveD);
                fft_own->Transform();

                Double_t *re_full = new Double_t[Wnum];
                Double_t *im_full = new Double_t[Wnum];
                fft_own->GetPointsComplex(re_full, im_full);

                for(int i=0;i<n_size-1;++i) {
                    double mag = sqrt(re_full[i]*re_full[i] + im_full[i]*im_full[i]);
                    if(mag>1e-8) hFreq2D->Fill(i, mag);
                }
                for(int i=60;i<=Wnum-60;++i) {re_full[i] *= 0.0;im_full[i] *= 0.0;}


                TVirtualFFT *fft_back = TVirtualFFT::FFT(1, &n_size, "C2R M K");
                fft_back->SetPointsComplex(re_full,im_full);
                fft_back->Transform();
                TH1 *hb = 0;
                hb = TH1::TransformHisto(fft_back,hb,"Re");
                hb->SetTitle("The backward transform result");

                for(int i=0;i<Wnum;++i) {hb->SetBinContent(i+1,hb->GetBinContent(i+1)/Wnum); WaveD[i]=hb->GetBinContent(i+1);}
                delete hb;delete re_full;delete im_full;delete fft_own;delete fft_back;
                
                int rise_bin = 0;
                Fall_time=Fall_Time_Get(WaveD,t_axis,max_bin,p_fbin);
                Rise_time=Rise_Time_Get(WaveD,t_axis,max_bin, rise_bin);
                
                sum = 0.;
                for(int i=max_bin-FSL_HALF;i<max_bin+FSR_HALF&&i<Wnum-25;++i) {
                    sum=sum+(t_axis[i+1]-t_axis[i])*(w_axis[i]+w_axis[i+1])/2;
                }
                charge=sum/50.; 

               //if(Rise_time>4){
               if(charge/1.6>0.5&&charge/1.6<1.5){
               //RISET[ai]=Rise_time;
                  for(int iii=0;iii<310;++iii)
                  {
                     if(rise_bin-150+iii<=Wnum-25){
                     Move_Peak_W[iii]=Move_Peak_W[iii] - WaveD[max_bin-150+iii];}
                  }
                  WaveNum ++;
               }
               delete WaveD;
            } 
            sum=0; //sum must be taken zero!be careful!
        
            if(max_bin<Tmax_bin-FSL_HALF||max_bin>Tmax_bin+ FSR_HALF)  //the expected range of signal is ensential
            {  
               for(i=Tmax_bin-FSL_HALF;i<Tmax_bin+FSR_HALF;++i)
               {  
                  sum=sum+(t_axis[i+1]-t_axis[i])*(w_axis[i]+w_axis[i+1])/2;
               }
               Rise_time=0;
               Fall_time=0;
               charge=sum/50.;
               hcharge->Fill(charge);
               Container_result->Fill();
               continue;
            }
            for(i=max_bin-FSL_HALF;i<max_bin+FSR_HALF&&i<Wnum-25;++i) {
                sum=sum+(t_axis[i+1]-t_axis[i])*(w_axis[i]+w_axis[i+1])/2;
            }
            charge=sum/50.;
            hcharge->Fill(charge);
            if(Rise_time>0.01&&Fall_time>0.01){
                hRise_time->Fill(Rise_time);
                hFall_time->Fill(Fall_time);
            }
            Container_result->Fill();

         }

         for(int i=0;i<310;i++) Move_Peak_W[i] /= WaveNum;
         cout<<"WaveNum ==>"<<WaveNum<<endl;
         Container_resultf_Charge.cd();
         TGraph *AverageWave=new TGraph(310, T_Move, Move_Peak_W);
         AverageWave->SetName(Form("AverageWave_run%d_pmt%d", run, pmtid));
         AverageWave->Write();
         hFreq2D->Write();

         Double_t rtinf[5]={0}, ftinf[5]={0};
         timeinf_get(hRise_time,rtinf,pmtid,1,run);
         int a=timeinf_get(hFall_time,ftinf,pmtid,0,run);
       
         
         Container_result->Write();
         int fit_result=Parameters_Get(hcharge,PMTParameters, pmtid, ii, FitResults);
         if(LogGain_HV_Need==0)
         {
            Parameter_out<<pmtid<<'\t'<<PMTParameters[0]<<'\t'<<PMTParameters[1]<<'\t'<<rtinf[0]<<'\t'<<ftinf[0]<<'\t'
                        <<PMTParameters[2]<<'\t'<<PMTParameters[3]<<'\t'<<PMTParameters[4]<<'\t'<<PMTParameters[5]<<'\t'
                        <<PMTParameters[6]<<'\t'<<PMTParameters[7]<<'\t'<<PMTParameters[8]<<'\t'<<PMTParameters[9]<<endl;

            cout<<pmtid<<'\t'<<"Mu:"<<PMTParameters[0]<<'\t'<<"Gain:"<<PMTParameters[1]<<'\t'<<"riset:"<<rtinf[0]<<'\t'
            <<"fallt:"<<ftinf[0]<<'\t'<<"Res:"<<PMTParameters[2]<<'\t'<<"P/V:"<<PMTParameters[3]<<'\t'
            <<"Threshold:"<<PMTParameters[4]<<'\t'<<"mb1:"<<PMTParameters[5]<<'\t'<<"Sig1:"<<PMTParameters[6]<<'\t'
            <<"mb2:"<<PMTParameters[7]<<'\t'<<"Sig2:"<<PMTParameters[8]<<'\t'<<"S/N:"<<PMTParameters[9]<<endl;
         } 
         if(LogGain_HV_Need==1)
         {
            Gain_pmt[pmtid-101][ii-begin_file_num]=log10(PMTParameters[1]);
            HV_pmt  [pmtid-101][ii-begin_file_num]=HiVol[pmtid-101]-150+50*ii;
            Parameter_out<<pmtid<<'\t'<<HV_pmt[pmtid-101][ii]<<'\t'<<log10(PMTParameters[1])<<endl;
         }
         delete hRise_time;delete hFall_time;delete hcharge;
      }   
      N_id=LAST_PMT-FIRST_PMT+1;
      Parameter_out.close();
      ++fit_n;
      
   }
   //Container_resultf_Charge.Close();
   //Container_resultf_Amp.Close(); 
   if(LogGain_HV_Need==1)
   {
      HV_LogGain_Get(HV_pmt,Gain_pmt,FIRST_PMT-101,N_id,fit_n,begin_file_num);
   }

   }
   cout<<"Finished Good!"<<endl;
   
}

#ifndef _CINT_
int main()
{
    container();
    return 0;
}
#endif


     
