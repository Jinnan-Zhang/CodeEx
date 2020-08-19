// #include <TGraph.h>
// #include <iostream>
// #include <fstream>
// #include <vector>
// #include <strstream>
// #include <TCanvas.h>
// #include <TLegend.h>
// #include <TLine.h>
// #include <TMarker.h>
// #include <TAxis.h>
// #include <TH1.h>
// #include <TROOT.h>
// #include <TGaxis.h>
// #include <TMultiGraph.h>
// using namespace std;
// void draw_dyb()
{
     double DYBrateDay[6] = {56, 84, 112, 140, 168, 217};
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
          //        day.push_back((300+a*50));
          //	day.push_back(1.3506e+09+a*50*86400);
          day.push_back(300 + a * 50);
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

     const double max = 0.02;

     TCanvas *c1 = new TCanvas("sensitivity", "sensitivity", 800, 500);
     TMultiGraph *mg = new TMultiGraph();
     mg->Add(DYBrateSen);
     mg->Add(Sen8AD);
     Sen8AD->SetLineColor(kRed + 2);
     Sen8AD->SetMarkerColor(kRed + 2);
     DYBrateSen->SetLineColor(kRed + 2);
     Sen8AD->SetLineWidth(3);
     DYBrateSen->SetLineWidth(3);
     mg->Draw("AC");
     //     Sen8AD->GetXaxis()->SetTitle("Time(Years)");
     mg->GetYaxis()->SetRangeUser(0, max);
     mg->GetXaxis()->SetLabelFont(132);
     mg->GetXaxis()->SetLabelOffset(0.01);
     mg->GetXaxis()->SetLabelSize(0.05);
     mg->GetXaxis()->SetTitleSize(0.05);
     mg->GetXaxis()->SetTitleFont(132);
     mg->GetYaxis()->SetTitle("Error of sin^{2}2#theta_{13}");
     mg->GetXaxis()->SetTitle("Time(days)");
     mg->GetYaxis()->SetLabelFont(132);
     mg->GetYaxis()->SetLabelOffset(0.01);
     mg->GetYaxis()->SetLabelSize(0.05);
     mg->GetYaxis()->SetTitleSize(0.05);
     mg->GetYaxis()->SetTitleOffset(1.3);
     mg->GetYaxis()->SetTitleFont(132);
     Sen8AD_stat->SetLineColor(kRed + 2);
     Sen8AD_stat->SetMarkerColor(kRed + 2);
     Sen8AD_stat->SetLineStyle(2);
     Sen8AD_stat->Draw("C");

     TLegend *leg1 = new TLegend(0.4, 0.6, 0.89, 0.89);
     leg1->AddEntry(Sen8AD, "Total uncertainty", "l");
     leg1->AddEntry(Sen8AD_stat, "Statistic only", "l");
     leg1->Draw();

     TLine l1(217, 0.00950983, 300, 0.00950983);
     l1.SetLineColor(kBlue + 2);
     l1.SetLineWidth(1);
     l1.Draw();
     TLine l2(217, 0.00850847, 300, 0.00850847);
     l2.SetLineColor(kBlue + 2);
     l2.SetLineWidth(1);
     l2.Draw();

     //DYB experiment data
     TMarker dyb1(56, 0.0171092, 20);
     dyb1.SetMarkerColor(kBlue + 2);
     dyb1.SetMarkerStyle(4);
     dyb1.Draw();

     TMarker dyb2(140, 0.0110815, 20);
     dyb2.SetMarkerColor(kBlue + 2);
     dyb2.SetMarkerStyle(4);
     dyb2.Draw();

     TMarker dyb3(217, 0.00850847, 20);
     dyb3.SetMarkerColor(kBlue + 2);
     dyb3.SetMarkerSize(1.2);
     dyb3.Draw();

     TMarker dyb4(621, 0.005, 20);
     dyb4.SetMarkerColor(kBlue + 2);
     dyb4.SetMarkerSize(1.2);
     dyb4.Draw();

     //legend
     /*     TText *a1 = new TText(2013,max-0.003,"Stat. Only");
     TText *a2 = new TText(2014.5,max-0.003,"Total");
     TText *a4 = new TText(2015.5,max-0.007,"Projection");
     TLine cc1(2013.3,max-0.006,2013.7,max-0.006);
     TLine cc2(2014.5,max-0.006,2014.9,max-0.006);
     cc1->SetLineStyle(2);

     a1->Draw();
     a2->Draw();
     a4->Draw();
     cc1.Draw();
     cc2.Draw();
*/
}
