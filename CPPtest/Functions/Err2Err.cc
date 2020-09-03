#include <iostream>
#include <cmath>

using namespace std;

int Err2Err()
{
    //input sin^2(2theta) error
    double sigma_0 = 0.0027;
    // double Y_0 = 0.0856;//2018
    double Y_0 = 0.0841;//2016

    double Sigma_1 = 0.25 * sqrt(1 - Y_0) * sigma_0;
    cout << Sigma_1 << endl;
    return 0;
}