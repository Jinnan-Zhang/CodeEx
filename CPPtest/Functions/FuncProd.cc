//purpose: see if there is any difference between
//pure product of functions or, a media variable
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;
double f1(double x)
{
    double a = 10;
    double re = a * exp(x - a);
    return re;
}
double f2(double x)
{
    double b = 5;
    double re = sin(b * x) + 5;
    return re;
}
double f3(double x)
{
    double c = 2;
    double re = log(c * x) + sqrt(exp(x + c));
    return re;
}

int FuncProd()
{
    double tSum = 0;
    double x = 1;
    for (int i = 0; i < 1e6; i++)
    {
        x = 1+i / 1e-9;
        tSum += (f1(x) * f2(x) * f3(x));
    }
    cout << tSum << endl;
    return 0;
}