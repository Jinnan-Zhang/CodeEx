//Purpose: test return arrays
#include <iostream>
using namespace std;

double *GetArr();

int Arrays()
{
    double *at=GetArr();
    
    for (int i = 0; i < 10; i++)
    {
        printf("i:%f\n", at[i]);
    }
    return 0;
}
double *GetArr()
{
    static double Target[10];
    for (int i = 0; i < 10; i++)
    {
        Target[i] = 10 - i;
    }
    return Target;
}