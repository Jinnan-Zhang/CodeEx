//目的：类的成员函数作为TMinuit的函数：
#include <TMinuit.h>
#include <TF1.h>
#include<TH1.h>

class TestFCN
{
private:
    /* data */
    double a_res = 1.2 / 1e2;
    double b = 0.24 / 1e2;
    TF1 *f_1;
    TMinuit *mMinuit;

public:
    TestFCN(/* args */);
    static void TFCN(Int_t &npar, Double_t *grad, Double_t &fval, Double_t *par, Int_t flag);
    static double TTF1(double *x, double *par) { return x[0] * x[0]; }
    ~TestFCN();
};

TestFCN::TestFCN(/* args */)
{
    f_1=new TF1("f1",TestFCN::TTF1,-5,5,0);
    f_1->Draw();
}

TestFCN::~TestFCN()
{
}

int ClassTMinuit()
{
    TestFCN tf;

    return 0;
}