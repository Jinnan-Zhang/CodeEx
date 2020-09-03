/*
* @Compile comment g++ -I `root-config --incdir` -o IntOpenMP.cpp.o IntOpenMP.cpp -fopenmp `root-config --libs` 
*/
#include <TF1.h>
#include <omp.h>
#include <TH1.h>
const double x_low = 0;
const double x_up = 10;
void TestIntgral(int BinNUM = 10);

int main()
{
    TestIntgral();
    return 0;
}

// * @param BinNUM: bin number to do the integral
void TestIntgral(int BinNUM)
{
    TF1 *f_0 = new TF1("f_0", "x^2-1", x_low, x_up);
    TH1D *h_1 = new TH1D("h_1", "", BinNUM, x_low, x_up);
    const int N = BinNUM;
    double a_data[N];
    double Edges[N + 2];
    h_1->GetLowEdge(Edges);
    Edges[N] = x_up;
    double w = h_1->GetBinWidth(1);
#pragma omp parallel for
    for (int i = 0; i < BinNUM; i++)
    {
        TF1 *f_t = new TF1(Form("f_s%d", i), "x^2-1", x_low, x_up);
        // (TF1*)f_0->Clone(Form("f_s%d",i));
        a_data[i] = f_t->Integral(Edges[i], Edges[i + 1]);
        // a_data[i] = f_t->Eval(Edges[i]);
        // a_data[i]=Edges[i]+ Edges[i + 1]*10;
        printf("a: %f\t b: %f\t v: %f\n", Edges[i], Edges[i + 1], a_data[i]);
        delete f_t;
    }
    // for (int i = 0; i < BinNUM; i++)
    //     printf("a: %f\t b: %f\t v: %f\n", Edges[i], Edges[i + 1], a_data[i]);
}