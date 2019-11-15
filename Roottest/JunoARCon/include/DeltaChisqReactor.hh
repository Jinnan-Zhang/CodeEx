#ifndef DeltaChisqReactor_hh
#define DEltaChisqReactor_hh
#include "JunoARCon.hh"


double GeDataDeltaChisqReactor(double *dm31,double *par={0});
//vector<double>  EnergyBin_Rea(200);//{bin edeges} 
double CalculateDeltaChisqRea(double *dm31sq,double *pullpar);//pullpar:1-4:correlated reactor uncertainty, uncorrelated r u, spectrum shape uncertainty, detector-related uncertainty.
double intgreralinterval=1e-5;
double BinWidth=(E_Upper - E_Lower) / (double)NumOfBins;
double CofBin=0;//center of bins

void Ini_EB();

#endif