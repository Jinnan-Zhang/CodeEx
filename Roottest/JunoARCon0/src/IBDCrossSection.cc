#include "IBDCrossSection.hh"
#include <TMath.h>
#include <iostream>

IBDCrossSection::IBDCrossSection()
{
    M_proton=938.27203;
    M_neutron=939.56536;//in MeV
    E_electron=0.;
    P_electron=0.;
    M_electron=0.51099892;

    A=-0.07056;
    B=0.02018;
    C=-0.01953;
}

double IBDCrossSection::GetIBDCrossSection(double *E_nu,double *par)
//https://arxiv.org/abs/astro-ph/0302055v2
{
    double E_neutrino=E_nu[0];
    E_electron=E_neutrino-(M_neutron-M_proton);
    P_electron=sqrt(E_electron * E_electron - M_electron * M_electron);
    double PowerofEnu;
    PowerofEnu=TMath::Power(E_neutrino, 
                    (A +B * TMath::Log(E_neutrino)+C *3. * TMath::Log(E_neutrino)));
    SigmaTotal=1e-43 * P_electron * E_electron * PowerofEnu;

    return SigmaTotal;
}