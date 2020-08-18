#define FCN_Epr2Enu(E_pr) ((E_pr-0.51099892)*1.0092217+1.2806751)

int Ee2Enu()
{
    double a=4;
    cout<<FCN_Epr2Enu(a)<<endl;
    return 0;
}