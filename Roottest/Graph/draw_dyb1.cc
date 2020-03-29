#include <TGraph.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <strstream>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>
#include <TMarker.h>
#include <TAxis.h>
#include <TH1.h>
#include <TROOT.h>
#include <TGaxis.h>
#include <TMultiGraph.h>

using namespace std;

void draw_dyb1()
{
   const Double_t mk_size = 1.4;
   double DYBrateDay[6] = {2011.978 + 56 * 1. / 365, 2011.978 + 84 * 1. / 365, 2011.978 + 112 * 1. / 365, 2011.978 + 140 * 1. / 365, 2011.978 + 168 * 1. / 365, 2011.978 + 217 * 1. / 365};
   double DYBrate[6] = {0.0171092, 0.0137752, 0.0121306, 0.0110435, 0.0104718, 0.00950983};

   vector<double> day;
   vector<double> theta8AD;
   vector<double> theta8AD_stat;

   std::ifstream inputFile;
   char buffer[250];
   inputFile.open("../data/DYBshape.txt");
   int a = 0;
   while (inputFile.getline(buffer, sizeof(buffer)))
   {
      double b, c, d;
      istrstream(buffer) >> b >> c >> d;
      //        day.push_back((300+a*50)*1./365);
      //      day.push_back(1.3506e+09+a*50*86400);
      day.push_back(2011.978 + (300 + a * 50) * 1. / 365);
      if (c > d)
         theta8AD.push_back(c);
      else
         theta8AD.push_back(d);
      a++;
   }

   std::ifstream inputFile1;
   char buffer1[250];
   inputFile1.open("../data/DYBshape_stat.txt");
   while (inputFile1.getline(buffer1, sizeof(buffer1)))
   {
      double b, c, d;
      istrstream(buffer1) >> b >> c >> d;
      if (c > d)
         theta8AD_stat.push_back(c);
      else
         theta8AD_stat.push_back(d);
   }

   TGraph *DYBrateSen = new TGraph(6, DYBrateDay, DYBrate);
   TGraph *Sen8AD = new TGraph();
   TGraph *Sen8AD_stat = new TGraph();

   for (int i = 0; i < day.size(); i++)
   {
      Sen8AD->SetPoint(i, day[i], theta8AD[i]);
      Sen8AD_stat->SetPoint(i, day[i], theta8AD_stat[i]);
   }
   vector<double> DYBshapeDaydelta;
   vector<double> DYBshapedelta;
   vector<double> DYBshape_statdelta;

   std::ifstream inputFile6;
   char buffer6[250];
   inputFile6.open("../data/DYBshapeDelta.txt");
   a = 0;
   while (inputFile6.getline(buffer6, sizeof(buffer6)))
   {
      double b, c, d;
      istrstream(buffer6) >> b >> c >> d;
      DYBshapeDaydelta.push_back(2011.978 + (300 + a * 50) * 1. / 365);
      //if(c>d) DYBshape.push_back(c*1000);
      DYBshapedelta.push_back(d * 1000);
      a++;
      // cout<<b<<" "<<c<<" "<<d<<endl;
      cout << d << endl;
   }

   // std::ifstream inputFile_s;
   // char buffer_s[250];
   // inputFile_s.open("../data/DYBshapeDelta_stat.txt");
   // while (inputFile_s.getline(buffer_s, sizeof(buffer_s)))
   // {
   //    double b, c, d;
   //    istrstream(buffer_s) >> b >> c >> d;
   //    //if(c>d) DYBshape_stat.push_back(c*1000);
   //    DYBshape_statdelta.push_back(d * 1000);
   // }

   // TGraph *DYBshapeSendelta = new TGraph();
   // TGraph *DYBshapeSen_statdelta = new TGraph();

   // for (int i = 0; i < DYBshapeDaydelta.size(); i++)
   // {
   //    DYBshapeSendelta->SetPoint(i, DYBshapeDaydelta[i], DYBshapedelta[i]);
   //    DYBshapeSen_statdelta->SetPoint(i, DYBshapeDaydelta[i], DYBshape_statdelta[i]);
   // }
   //
   // Example showing how to superimpose a TGraph with a different range
   // using a transparent pad.
   //

   //    gROOT->ForceStyle(0);
   //    TCanvas *c1 = new TCanvas("c1", "gerrors2", 200, 10, 700, 500);
   //    TPad *pad = new TPad("pad", "", 0, 0, 1, 1);
   //    pad->SetGrid();
   //    pad->Draw();
   //    pad->cd();

   //    // draw a frame to define the range
   //    TH1F *hr = c1->DrawFrame(2011.5, 0, 2021, 0.02);
   //    hr->SetYTitle("Uncertainty of sin^{2}2#theta_{13}");
   //    hr->GetXaxis()->SetNdivisions(505);
   //    hr->GetYaxis()->SetNdivisions(505);
   //    hr->GetYaxis()->SetTitleOffset(1.2);

   //    // create first graph
   //    Sen8AD_stat->SetLineStyle(2);
   //    Sen8AD->SetLineWidth(4);
   //    DYBrateSen->SetLineWidth(4);
   //    Sen8AD_stat->SetLineWidth(4);
   //    Sen8AD->Draw("C");
   //    DYBrateSen->Draw("C");
   //    Sen8AD_stat->Draw("C");

   //    TMarker dyb1(2011.978 + 56 * 1. / 365, 0.0171092, 20);
   //    dyb1.SetMarkerColor(kBlue + 2);
   //    dyb1.SetMarkerStyle(4);
   //    dyb1.SetMarkerSize(1.3);
   //    dyb1.Draw();

   //    TMarker dyb2(2011.978 + 140 * 1. / 365, 0.0110815, 20);
   //    dyb2.SetMarkerColor(kBlue + 2);
   //    dyb2.SetMarkerStyle(4);
   //    dyb2.SetMarkerSize(1.3);
   //    dyb2.Draw();

   //    TMarker dyb3(2011.978 + 300 * 1. / 365, 0.00850847, 20);
   //    dyb3.SetMarkerColor(kBlue + 2);
   //    dyb3.SetMarkerSize(mk_size);
   //    dyb3.Draw();

   //    TMarker dyb4(2011.978 + 621 * 1. / 365, 0.005, 20);
   //    dyb4.SetMarkerColor(kBlue + 2);
   //    dyb4.SetMarkerSize(mk_size);
   //    dyb4.Draw();

   //    TLine l1(2011.978 + 217 * 1. / 365, 0.00950983, 2011.978 + 300 * 1. / 365, 0.00950983);
   //    l1.SetLineColor(kBlue + 2);
   //    l1.SetLineWidth(1);
   //    l1.Draw();

   //    // create second graph
   //    //create a transparent pad drawn on top of the main pad
   //    c1->cd();
   //    TPad *overlay = new TPad("overlay", "", 0, 0, 1, 1);
   //    overlay->SetFillStyle(0);
   //    overlay->SetFillColor(0);
   //    overlay->SetFrameFillStyle(0);
   //    overlay->Draw("FA");
   //    overlay->cd();
   //    double xmin = pad->GetUxmin();
   //    double xmax = pad->GetUxmax();
   //    double ymin = 0;
   //    double ymax = 0.2;
   //    TH1F *hframe = overlay->DrawFrame(xmin, ymin, xmax, ymax);
   //    //   hframe->GetXaxis()->SetLabelOffset(99);
   //    hframe->GetXaxis()->SetNdivisions(505);
   //    hframe->GetYaxis()->SetNdivisions(505);
   //    hframe->GetYaxis()->SetLabelOffset(99);
   //    DYBshapeSendelta->SetLineColor(2);
   //    DYBshapeSen_statdelta->SetLineStyle(2);
   //    DYBshapeSen_statdelta->SetLineColor(2);
   //    DYBshapeSendelta->Draw("C");
   //    DYBshapeSen_statdelta->Draw("C");

   //    TMarker dyb5(2011.978 + 300 * 1. / 365, 0.188, 20);
   //    dyb5.SetMarkerColor(kRed + 2);
   //    dyb5.SetMarkerSize(mk_size);
   //    dyb5.Draw();

   //    TMarker dyb6(2011.978 + 621 * 1. / 365, 0.11, 20);
   //    dyb6.SetMarkerColor(kRed + 2);
   //    dyb6.SetMarkerSize(mk_size);
   //    dyb6.Draw();

   //    TLegend *leg1 = new TLegend(0.4, 0.6, 0.89, 0.89);
   //    leg1->AddEntry(DYBshapeSendelta, "Total uncertainty", "l");
   //    leg1->AddEntry(DYBshapeSen_statdelta, "Statistical uncertainty only", "l");
   //    leg1->Draw();

   //    TLegend *leg2 = new TLegend(0.4, 0.6, 0.89, 0.89);
   //    leg2->AddEntry(Sen8AD, "sin^{2}2#theta_{13}", "l");
   //    leg2->AddEntry(DYBshapeSendelta, "|#Deltam_{ee}^{2}|", "l");
   //    leg2->Draw();
   //    // */
   //    //legend
   //    /*     double max = 0.2;
   //      TText *a1 = new TText(2015,max-0.04,"Current Systematics");
   //      TText *a2 = new TText(2016.2,max-0.04,"Statistic only");
   //      TLine b1(2015.3,max-0.08,2015.7,max-0.08);
   //      b1->SetLineWidth(3);
   //      TLine b2(2016.5,max-0.08,2016.9,max-0.08);
   //      b2->SetLineWidth(3);
   //      b2->SetLineStyle(2);
   //      TText *a3 = new TText(2015.5,max-0.009,"theta13");
   //      TText *a4 = new TText(2015.5,max-0.013,"deltaMee");
   //      TLine cc1(2013.3,max-0.012,2013.7,max-0.012);
   //      TLine cc2(2014.5,max-0.012,2014.9,max-0.012);
   //      cc1->SetLineStyle(2);
   //      cc1->SetLineColor(2);
   //      cc2->SetLineColor(2);
   //      a1->Draw();
   //      a2->Draw();
   //      a3->Draw();
   //      a4->Draw();
   //      b1.Draw();
   //      b2.Draw();
   //      cc1.Draw();
   //      cc2.Draw();
   // // */
   //    //Draw an axis on the right side
   //    TGaxis *axis = new TGaxis(xmax, ymin, xmax, ymax, ymin, ymax, 510, "+L");
   //    axis->SetLineColor(kRed);
   //    axis->SetLabelColor(kRed);
   //    axis->SetTitle("Uncertainty of |#Deltam_{ee}^{2}|[10^{-3}eV^{2}]");
   //    axis->SetTitleColor(kRed);
   //    axis->SetTitleOffset(1.);
   //    axis->SetNdivisions(505);
   //    axis->Draw();
}
