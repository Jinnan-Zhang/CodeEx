#include <map>
#include<vector>
#include<iostream>

using namespace std;
void avec(){
    vector<double> aa;
    for(int i=0;i<10;i++)
    {
        aa.push_back(i);
    }
    cout<<"size: "<<aa.size()<<endl;
}
int vect()
{  
    avec();
    avec();
    return 0;
    
}