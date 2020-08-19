#include <iostream>  
#include <fstream>  
#include <string>  
using namespace std;  
  
int CountLines(string filename)  
{  
    ifstream ReadFile;  
    int n=0;  
    string tmp;  
    ReadFile.open(filename.c_str(),ios::in);//ios::in 表示以只读的方式读取文件  
    if(ReadFile.fail())//文件打开失败:返回0  
    {  
        return 0;  
    }  
    else//文件存在  
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
        return "Error 1: 行数错误，不能为0或负数。";  
    }  
    if(file.fail())  
    {  
        return "Error 2: 文件不存在。";  
    }  
    if(line>lines)  
    {  
        return "Error 3: 行数超出文件长度。";  
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
//    cout<<"该文件行数为："<<CountLines(filename)<<endl;  
//    cout<<"\n请输入要读取的行数:"<<endl;  
//    while(cin>>line)  
//    {  
//        cout<<"第"<<line<<"行的内容是 ："<<endl;  
        cout<<ReadLine(filename,CountLines(filename)-1)<<endl;  
//        cout<<"\n\n请输入要读取的行数:"<<endl; 
//    delete filename; 
} 
