//目的：类的成员函数作为TMinuit的函数：
#include <TMinuit.h>
#include <TF1.h>
#include <TH1.h>
#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"

class TestFCN
{
private:
    /* data */
    double a_res = 1.2 / 1e2;
    double b = 0.24 / 1e2;

    TMinuit *mMinuit;

public:
    TestFCN(/* args */);
    static void TFCN(Int_t &npar, Double_t *grad, Double_t &fval, Double_t *par, Int_t flag)
    {
        fval = par[0];
    }
    static double VFCN(const double *var)
    {
        return var[0] * var[0] + 1 + var[1] * var[1];
    }
    static double TTF1(double *x, double *par)
    {
        double x1 = xinFCN(x[0]);
        return x1;
    }
    static double xinFCN(double x) { return x * x; }
    ~TestFCN();
};
TestFCN::TestFCN(/* args */)
{
    ROOT::Math::Minimizer *minimum =
        ROOT::Math::Factory::CreateMinimizer("Minuit2", "MINIMIZE");
    minimum->SetMaxFunctionCalls(1000000); // for Minuit/Minuit2
    minimum->SetMaxIterations(10000);      // for GSL
    minimum->SetTolerance(0.001);
    minimum->SetPrintLevel(1);

    ROOT::Math::Functor f(&TestFCN::VFCN, 2);
    minimum->SetFunction(f);
    minimum->SetVariable(0, "x", 0, 0.01);
    minimum->SetVariable(0, "y", 0, 0.01);
    minimum->Minimize();
}

TestFCN::~TestFCN()
{
}

class TestFCN1 : public TestFCN
{
private:
    /* data */
    TF1 *f_1;

public:
    TestFCN1(/* args */);
    ~TestFCN1();
};

TestFCN1::TestFCN1(/* args */)
{
    // f_1 = new TF1("f1", TestFCN::TTF1, -5, 5, 0);
    // f_1->Draw();
    TMinuit minn;
    minn.SetFCN(TestFCN::TFCN);
}

TestFCN1::~TestFCN1()
{
}

int ClassTMinuit()
{
    TestFCN1 tf;

    return 0;
}