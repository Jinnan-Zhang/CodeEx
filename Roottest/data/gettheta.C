#include <iostream>  
#include <fstream>  
#include <string>  
using namespace std;  
  
int CountLines(string filename)  
{  
    ifstream ReadFile;  
    int n=0;  
    string tmp;  
    ReadFile.open(filename.c_str(),ios::in);//ios::in ��ʾ��ֻ���ķ�ʽ��ȡ�ļ�  
    if(ReadFile.fail())//�ļ���ʧ��:����0  
    {  
        return 0;  
    }  
    else//�ļ�����  
    {  
        while(getline(ReadFile,tmp,'\n'))  
        {  
            n++;  
        }  
        ReadFile.close();  
        return n;  
    }  
}  
  
string ReadLine(string filename,int line)  
{  
    int lines,i=0;  
    string temp;  
    fstream file;  
    file.open(filename.c_str(),ios::in);  
    lines=CountLines(filename);  
  
    if(line<=0)  
    {  
        return "Error 1: �������󣬲���Ϊ0������";  
    }  
    if(file.fail())  
    {  
        return "Error 2: �ļ������ڡ�";  
    }  
    if(line>lines)  
    {  
        return "Error 3: ���������ļ����ȡ�";  
    }  
    while(getline(file,temp)&&i<line-1)  
    {  
        i++;  
    }  
    file.close();  
    return temp;  
}  
int gettheta()  
{  
    int line;  
    string filename;
    ofstream outFile;
    outFile.open("DYBshape_stat.txt");
//    outFile.open("DCtoyMC_stat.txt");

    for(int i=0;i<=67;i++) {
//    filename = Form("/publicfs/dyb/data/userdata/zhaoj/IbdAna/chi2/CombinedFit/RENO_stat/job/theta/log%i",i);
    filename = Form("/publicfs/dyb/data/userdata/zhaoj/IbdAna/chi2/RateShape_v0/job/stat/log%i",i);
//    filename = Form("/publicfs/dyb/data/userdata/zhaoj/IbdAna/chi2/CombinedFit/DC_stat/job/log%i",i);
    cout<<filename<<endl;

    outFile<<ReadLine(filename,CountLines(filename)-1)<<endl;
    }

    outFile.close();
//    cout<<"���ļ�����Ϊ��"<<CountLines(filename)<<endl;  
//    cout<<"\n������Ҫ��ȡ������:"<<endl;  
//    while(cin>>line)  
//    {  
//        cout<<"��"<<line<<"�е������� ��"<<endl;  
        cout<<ReadLine(filename,CountLines(filename)-1)<<endl;  
//        cout<<"\n\n������Ҫ��ȡ������:"<<endl; 
//    delete filename; 
} 