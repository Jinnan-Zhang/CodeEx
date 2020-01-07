#include <math.h>
#include <iostream>
#define PI 3.14159265358979323846

using namespace std;
double a1 = 0, b1 = 1;
double a2 = 0, b2 = 1;

double in2D(int N);
double funt(double x, double y);
int GL2D()
{
    for (int i = 10; i < 300; i += 100)
        cout << "n: " << i << '\t' <<0.158529 - in2D(i) << endl;
    return 0;
}

double in2D(int N)
{
    int fNum = N;
    double *fX, *fW;
    double fEpsRel = 1e-6;
    if (fNum <= 0 || fEpsRel <= 0)
        return 0;

    if (fX == 0)
        delete[] fX;

    if (fW == 0)
        delete[] fW;

    fX = new double[fNum];
    fW = new double[fNum];

    // The roots of symmetric is the interval, so we only have to find half of them
    const unsigned int m = (fNum + 1) / 2;

    double z, pp, p1, p2, p3;

    // Loop over the desired roots
    for (unsigned int i = 0; i < m; i++)
    {
        z = std::cos(3.14159265358979323846 * (i + 0.75) / (fNum + 0.5));

        // Starting with the above approximation to the i-th root, we enter
        // the main loop of refinement by Newton's method
        do
        {
            p1 = 1.0;
            p2 = 0.0;

            // Loop up the recurrence relation to get the Legendre
            // polynomial evaluated at z
            for (int j = 0; j < fNum; j++)
            {
                p3 = p2;
                p2 = p1;
                p1 = ((2.0 * j + 1.0) * z * p2 - j * p3) / (j + 1.0);
            }
            // p1 is now the desired Legendre polynomial. We next compute pp, its
            // derivative, by a standard relation involving also p2, the polynomial
            // of one lower order
            pp = fNum * (z * p1 - p2) / (z * z - 1.0);
            // Newton's method
            z -= p1 / pp;

        } while (std::fabs(p1 / pp) > fEpsRel);

        // Put root and its symmetric counterpart
        fX[i] = -z;
        fX[fNum - i - 1] = z;

        // Compute the weight and put its symmetric counterpart
        fW[i] = 2.0 / ((1.0 - z * z) * pp * pp);
        fW[fNum - i - 1] = fW[i];
    }

    const double a01 = (b1 + a1) / 2;
    const double b01 = (b1 - a1) / 2;
    const double a02 = (b2 + a2) / 2;
    const double b02 = (b2 - a2) / 2;

    double tSum = 0;
    double x, y;
    for (int ij = 0; ij < fNum * fNum; ij++)
    {
        int i = ij / fNum;
        int j = ij % fNum;
        x = a01 + b01 * fX[i];
        y = a02 + b02 * fX[j];

        tSum += (fW[i] * fW[j] * funt(x, y));
    }
    tSum = tSum * b01 * b02;
    return tSum;
}
double funt(double x, double y)
{
    return x * sin(y*x);
}