#include <TF1.h>
#include <TMath.h>

using namespace std;
double s2t(double *x,double *par)
{
    return 4.*x[0]*(1-x[0]);
}

int sin2t()
{
    TF1 * f1=new TF1("sin^2(2x)",s2t,0,1,0);
    f1->Draw();
    return 1;
}