#include <iostream>
#include <math.h>
#define PI 3.14159265358979323846

using namespace std;
double tff(double x);
double Gdiff(int N);

//test the necessary number of sample points of Gauss Legendre method
int GLint()
{
    // Given the number of sampling points this routine fills the
    // arrays x and w.
    for (int i = 1; i < 2000; i += 40)
        cout << "n: " << i << '\t' << Gdiff(i) << endl;

    return 1;
}
double Gdiff(int N)
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
    double a, b;
    a = 0;
    b = PI / 2.;
    double a0 = (a + b) / 2.;
    double b0 = (b - a) / 2.;
    double xx, result = 0;
    for (int i = 0; i < fNum; i++)
    {
        xx = a0 + b0 * fX[i];
        result += fW[i] * tff(xx);
    }
    result *= b0;
    return result;
}
double tff(double x)
{
    double a = sin(1001 * x);
    double b = sin(x);
    return a * b;
}