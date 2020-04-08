//目的：如何正确返回值
#include <TH1.h>

TH1 *gethist();
int HistReturn()
{
    TH1 *h_0 = gethist();
    h_0->FillRandom("gaus");
    h_0->Draw();
    return 0;
}
TH1 *gethist()
{
    // static
    TH1D *h = new TH1D("hh", "", 100, 0, 10);
    return h;
}
//结论：使用new产生的指针可以返回