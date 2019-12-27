#include <map>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;
void avec()
{
    double BkgRatio[5];
    BkgRatio[0] = 0.9 / 60;
    //Fast neutron bkg
    BkgRatio[1] = 0.1 / 60;
    //9Li8He bkg
    BkgRatio[2] = 1.6 / 60;
    //alpha n bkg
    BkgRatio[3] = 0.05 / 60;
    //Geo-nus bkg
    BkgRatio[4] = 1.1 / 60;
    vector<double> sigma1 = {0.01, 1, 0.2, 0.5, 0.3};
    vector<double> sigma = {0, 0.2, 0.1, 0.5, 0.05};
    double give = 0;
    for (int i = 0; i < 5; i++)
    {
        give += BkgRatio[i] * sigma[i]*BkgRatio[i] * sigma[i];
    }
    cout <<sqrt(give)<<endl;
}
int vect()
{
    avec();
    // avec();
    return 0;
}
//结论： 函数内部的vector在函数执行完之后内存会被释放。