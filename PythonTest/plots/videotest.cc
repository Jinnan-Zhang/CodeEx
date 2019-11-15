#include <iostream>
#include <TF1.h>
#include <TMath.h>
#include <TF1Convolution.h>

using namespace std;

double tellmewhy(double *,double*);

int videotest()
{
    //TF1* f1=new TF1("f1","15*TMath::Landau([0]*x+[3],[1],[2])",-20,20);
    TF1* f1=new TF1("f1",tellmewhy,-20.,20.,1);
    double par[]={-1};
    f1->SetParameters(par);
    /*TF1* f2=new TF1("f2","TMath::Exp(-x*2)",-20,20);
    //f2->SetParameters(3,-2,0.5);
    TF1Convolution * f_con=new TF1Convolution(f1,f2);
    TF1 *f3=new TF1("f3",*f_con,-20,20,f_con->GetNpar());
    f3->SetParameters(-1,0.9,0.3,10);*/
    f1->Draw();
    /*f2->SetLineColor(kBlue);
    f3->SetLineColor(kGreen);
    f3->Draw("SAME");
    f2->Draw("same");*/
    return 0;
}

double tellmewhy(double *x,double *par)
{
    cout<<par[0]<<endl;
    return x[0]*par[0];
}

