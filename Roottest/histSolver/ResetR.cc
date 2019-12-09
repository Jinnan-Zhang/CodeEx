#include <iostream>
#include <vector>

using namespace std;

int ResetR()
{
    double width = 0;
    vector<vector<double>> OSParsRange = {{2.41e-3, 2.47e-3}, {0.302, 0.311}, {7.48e-5, 7.58e-5}, {0.019, 0.026}};
    // vector<vector<double>> OSP;
    for (int i = 0; i < 4; i++)
    {
        cout<<"par :"<<i<<endl;
        for (int j = 0; j < 5; j++)
        {
            width = (OSParsRange[i][1] - OSParsRange[i][0]) / 5.;
            vector<double> a = {OSParsRange[i][0] + j * width, OSParsRange[i][0] + (j + 1) * width};
            // OSP.push_back(a);
            cout << "{" << a[0] << "," << a[1] << "}," << endl;
        }
    }
    return 1;
}