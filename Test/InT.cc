#include <TF1.h>
#include <TH1.h>
#include "ROOT/TProcessExecutor.hxx"
#include "ROOT/TSeq.hxx"
#include "thread"

double ax9(double *, double *);
// Total amount of numbers
const UInt_t nNumbers = 20000000U;
// The number of workers
const UInt_t nWorkers = 8U;
TH1 *h1;
TF1 *f1;
int InT()
{
    TF1 *f0 = new TF1("f0", ax9, -10, 10, 1);
    TH1D *h2 = new TH1D("h2", "h2", 200, -10, 10);
    f1 = f0;
    h1 = h2;
    f1->SetParameter(0, 2);
    ROOT::EnableThreadSafety();
    auto workItem = [](UInt_t workerID) {
        for (int i = 0; i < 1e8; i++)
        {

            double a, b, c;
            a = -10 + i * 1e-4;
            b = -10 + (i + 1) * 1e-4;
            c = f1->Integral(a, b);
            h1->Fill(-10 + c * 1e-6);
        }
        return 0;
    };
    // Create the collection which will hold the threads, our "pool"
    std::vector<std::thread> workers;

    // Fill the "pool" with workers
    for (auto workerID : ROOT::TSeqI(nWorkers))
    {
        workers.emplace_back(workItem, workerID);
    }
    // Now join them
    for (auto &&worker : workers)
        worker.join();
    return 0;
}
double ax9(double *x, double *par)
{
    return x[0] * x[0] * par[0] - x[0];
}