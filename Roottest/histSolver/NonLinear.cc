#include <iostream>
#include <TFile.h>
#include <TH1.h>
#include <math.h>
#include <TPad.h>

double E_low = 0.09;
double E_up = 10;
const int BinNUM = 5000;
using namespace std;
double Sfunc(double E_dep);
class JunoNonLinearity
{
public:
    JunoNonLinearity() { ; }
    ~JunoNonLinearity() { ; }
    void SetAbsE_Scale(double A) { A_NL = A; }
    void SetBirkCoe(double kB) { this->kB = kB; }
    void SetAbsCherenkov(double k_C) { this->k_C = k_C; }
    void SetElecNonLinearAMP(double alpha_EleNL) { alpha_NL = alpha_EleNL; }
    void SetDecayConstant_ElecNL(double tau_NL) { this->tau_NL = tau_NL; }
    //Full nonlinearity: E_dep E_dep this =E_vis (central value)
    double GetFullNLEdep2Erec(double E_dep)
    {
        double FullNL = 0;
        double E_vis = GetVisibleEnergy_positron(E_dep);
        FullNL = E_vis / E_dep * GetElecNL(E_vis);
        return FullNL;
    }
    double GetVisibleEnergy_positron(double E_dep)
    {
        double T_e = E_dep - 2. * M_electron; //electron knetic energy
        double f_eLSNL = GetScintNL(T_e);     //scintillator nonlinearity
        double E_gamma_vis = GetVisibleEnergy_gamma(M_electron);
        double resl = 0;
        resl = T_e * f_eLSNL + 2. * E_gamma_vis;
        return resl;
    }
    double GetVisibleEnergy_gamma(double E_dep);
    double GetVisibleEnergy_electron(double E_dep);
    double GetElecNL(double E_vis)
    {
        double res;
        res = 1. + alpha_NL * (exp(-E_vis / tau_NL) - exp(-E_ref / tau_NL));
        return res;
    }
    double GetScintNL(double E_dep)
    {
        return 0;
    }

private:
    double M_electron = 0.51099895; //MeV
    double A_NL = 1.013;            //Absolute energy scale
    double kB = 15.2e-3;            //Birks' coefficient g/cm^2/MeV
    double k_C = 0.019;             //Absolute Cherenkov contribution
    double alpha_NL = 0.104;        //Amplitude of the electronics nonlinearity
    double tau_NL = 2.30;           //Decay constant of the electronics NL MeV
    double E_ref = 8.05;            //reference energy, for neutron capture on gadolinium, is 8.05 MeV
};

//purpose:
//to get a proper pseudo function to describe Nonlinearity
//and generate pseudo data for that.
int NonLinear()
{
    // TFile *fl = TFile::Open("JunoNonL.root", "RECREATE");
    TH1D *h1 = new TH1D("JunoNonL", "Nonlinear data", BinNUM, E_low, E_up);
    double xi, yi;
    double width = (E_up - E_low) / BinNUM;
    for (int i = 0; i < BinNUM; i++)
    {
        xi = E_low + (i + 0.5) * width;
        yi = Sfunc(xi);
        h1->SetBinContent(i + 1, yi);
    }
    h1->Draw();
    // gPad->SetLogy();
    gPad->SetLogx();

    // h1->Write();
    // fl->Close();
    cout << Sfunc(0.5) << endl;
    return 0;
}
double Sfunc(double E_dep)
{

    // double K = 0.4;
    // double a = 0.5;
    // double b = 0.95;
    // double inp = 0.63;
    // return inp + K / (1 + exp(a - b * E_dep));
    //淬火曲线
    double a = 1;
    double b = -1;
    double c = -1;
    double d = -3;
    double resl;
    resl = a+b*exp(d+c*log10(E_dep));
    return resl;
    // //切仑科夫
    // double Coe = 2.104;
    // double n = 1.6;
    // E_dep = E_dep + 0.511;
    // double beta = sqrt(E_dep * E_dep - 0.511 * 0.511) / E_dep;

    // double res;
    // res = Coe * (1. - pow(1. / (beta * n), 2));
    // return res;
}