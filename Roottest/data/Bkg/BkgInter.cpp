// to interpolate before calculation Bkg?
#include <TFile.h>
#include <TH1.h>
#include <TString.h>

void ffcn(TString aname)
{
    printf("%s\n", aname.Data());
}
int BkgInter()
{
    ffcn("aa");
    return 0;
}