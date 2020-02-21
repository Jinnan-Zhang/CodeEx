#include <vector>
#include <iostream>
#include <math.h>

std::vector<double> Weight_of_Cores =
    {
        0.0764138,
        0.0761638,
        0.0773795,
        0.0771245,
        0.078275,
        0.0780161,
        0.121396,
        0.121996,
        0.123435,
        0.124035,
        0.0275986,
        0.0181666};
std::vector<std::vector<double>> Power_and_BaseLine =
    {{2.9000000, 5274980.0},
     {2.9000000, 5283630.0},
     {2.9000000, 5241960.0},
     {2.9000000, 5250620.0},
     {2.9000000, 5211890.0},
     {2.9000000, 5220530.0},
     {4.6000000, 5270890.0},
     {4.6000000, 5257910.0},
     {4.6000000, 5227190.0},
     {4.6000000, 5214520.0},
     {17.400000, 21500000.},
     {17.400000, 26500000.}};

int L_over_E()
{
    double L_eff_0 = 0; //YJ and TS
    double L_eff_1 = 0; //DYB and HZ
    double sum0(0), sum1(0);
    double L0(0);
    for(int i=0;i<12;i++)
    {
        L0+=Power_and_BaseLine[i][1] * Weight_of_Cores[i];
    }
    printf("%e\t Overall BL: \n",L0);
    for (int i = 0; i < 10; i++)
    {
        Weight_of_Cores[i] = Power_and_BaseLine[i][0] / pow(Power_and_BaseLine[i][1], 2);
        sum0 += Weight_of_Cores[i];
    }

    for (int i = 10; i < 12; i++)
    {
        Weight_of_Cores[i] = Power_and_BaseLine[i][0] / pow(Power_and_BaseLine[i][1], 2);
        sum1 += Weight_of_Cores[i];
    }

    for (int i = 0; i < 10; i++)
    {
        Weight_of_Cores[i] *= (1. / sum0);
        L_eff_0 += Power_and_BaseLine[i][1] * Weight_of_Cores[i];
    }
    for (int i = 10; i < 12; i++)
    {
        Weight_of_Cores[i] *= (1. / sum1);
        L_eff_1 += Power_and_BaseLine[i][1] * Weight_of_Cores[i];
    }
    printf("%e\t YJ and TS: \n%e\t DYB and HZ: \n",L_eff_0,L_eff_1);
    return 0;
}