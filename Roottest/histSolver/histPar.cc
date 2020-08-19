//目标：指针传参会被改变吗
//clone 和copy都不行
#include <TH1.h>
#include <iostream>

using namespace std;
void tfunc(TH1 *);

int histPar()
{
    TH1 *h0;
    tfunc(h0);
    h0->Draw();
    return 0;
}

void tfunc(TH1 *ht)
{
    TH1D *h00 = new TH1D("h00", "", 200, 0, 10);
    // ht->Copy(h00);
    ht->FillRandom("gaus");
}