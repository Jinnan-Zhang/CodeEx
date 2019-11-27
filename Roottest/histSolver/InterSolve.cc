#include <TF1.h>
#include <TH1.h>
#include <iostream>
#include <cmath>

using namespace std;
using namespace std::placeholders;
double bisection(double a, double b, double Value, TH1 *func, double EPSILON = 1e-6);

int InterSolve()
{
    TH1D *h1 = new TH1D("h1", "h1", 200, 0, 10);
    h1->FillRandom("gaus");
    h1->SetLineColor(kYellow);
    cout<<bisection(0,10,50,h1);
    return 0;
}
double bisection(double a, double b, double Value,  TH1 *func, double EPSILON)
{
    double c = (a + b) / 2.;
    double fa = func->Interpolate(a)-Value;
    double fb = func->Interpolate(b)-Value;
    double fc = func->Interpolate(c)-Value;
    do
    {
        c = (a + b) / 2.;
        fa = func->Interpolate(a)-Value;
        fb = func->Interpolate(b)-Value;
        fc = func->Interpolate(c)-Value;
        if (fa * fc < 0)
        {
            b = c;
        }
        else if (fb * fc < 0)
        {
            a = c;
        }
        else
        {
            break;
        }
        
    } while (abs(func->Interpolate(c)-Value) > EPSILON);
    return c;
}