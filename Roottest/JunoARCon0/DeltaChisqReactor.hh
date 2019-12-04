#ifndef DeltaChisqReactor_hh
#define DeltaChisqReactor_hh

void GeDataHist(double *DefaultSinsq31, double RUNTIME);//DefaultSinsq31: 0 for normal order, 1 for invert order
double CalculateDeltaChisqRea_Poisson(const double *pullparandvar,double RUNTIME);
double CalculateDeltaChisqRea_Gaussian(const double *pullparandvar,double RUNTIME);
// pullparandvar:0-4:{correlated reactor uncertainty,
// uncorrelated r u,
// spectrum shape uncertainty,
// detector-related uncertainty,dm31sq}
double wrappercalChi_Poisson(const double *pullparandvar);
double wrappercalChi_Gaussian(const double *pullparandvar);
void MinimizeChisq(int randomSeed=0,int Chistyle=0);//Chistyle:0 for Poisson, 1 for gaussian
void Ini_alpha_ik();



double SmearedEpromptSpectrum1(double *E_pr,double *par);//par:dmsq31, runtime_d
double SmearedEpromptSpectrumFFT(double *E_pr,double *par);//par: dmsq31, runtime_d
double SmearedEpromptSpectrum2D(double *Ex,double *par);//Ex:E_pr,Evis; par: dmsq31, runtime_d 

#endif