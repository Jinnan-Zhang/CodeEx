#include <map>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    map<string,double> erm;
    erm["me"]=1.002;
    cout<<erm["me"]<<endl;
    return 1;
}