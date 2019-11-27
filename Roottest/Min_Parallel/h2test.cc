#include <TH2.h>
#include <TF2.h>
#include <iostream>

using namespace std;

int h2test(){
    TF2 *f2=new TF2("f2","x*x+y*y",-10,10,-10,10);
    TH2D *h1=new  TH2D("h2","",200,-1,1,200,-1,1);
    h1->FillRandom("f2",1e4);
    //h1->Draw("surf");hist/draw2dopt.C
    f2->Draw("surf3");
    return  0;
}