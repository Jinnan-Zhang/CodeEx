//Purpose: test return arrays
//need avoid using static variable.
#include <iostream>
#include <vector>
using namespace std;
#pragma once
/*
usage:
StartTimeChrono(num);
...
StopTimeChrono(num);
PrintTimeChrono(num,"discription")
*/
#include <chrono>

#define StartTimeChrono(_num) \
    auto start##_num = std::chrono::high_resolution_clock::now()

#define StopTimeChrono(_num) \
    auto stop##_num = std::chrono::high_resolution_clock::now()

#ifdef _WIN32
#define PrintTimeChrono(_num, _str)                                                                    \
    auto dura##_num = std::chrono::duration_cast<std::chrono::microseconds>(stop##_num - start##_num); \
    printf("Time for calculating %s is %f millisecond.\n", _str, dura##_num.count())
#else
#define PrintTimeChrono(_num, _str)                                                                    \
    auto dura##_num = std::chrono::duration_cast<std::chrono::microseconds>(stop##_num - start##_num); \
    printf("Time for calculating %s is %f second.\n", _str, dura##_num.count() / 1.e6)
#endif
double *GetArr();
#include <map>
#include <TXMLEngine.h>
#define xmlfilePath "../../Roottest/xml/JUNOGlobalConfigs.xml"
const double LoadXMLConfig(const char *VariableName,
                           const char *XMLNameSpace,
                           const char *filename)
{
    TXMLEngine tXML;
    XMLDocPointer_t tXMLDoc = tXML.ParseFile(filename);
    XMLNodePointer_t mainNode = tXML.DocGetRootElement(tXMLDoc);
    XMLNodePointer_t tNode0 = tXML.GetChild(mainNode);
    XMLNsPointer_t tNS = tXML.GetNS(tNode0);
    while (tNode0 != NULL)
    {
        if (tNS != NULL && strcmp(XMLNameSpace, tXML.GetNSName(tNS)) == 0)
        {
            if (strcmp(VariableName, tXML.GetNodeName(tNode0)) == 0)
            {
                return std::stod(std::string(tXML.GetNodeContent(tNode0)));
            }
        }
        tNode0 = tXML.GetNext(tNode0);
        tNS = tXML.GetNS(tNode0);
    }
    printf("VariableName:%s or XMLNameSpace:%s not FOUND!\n", VariableName, XMLNameSpace);
    return 0;
}

int Arrays()
{
    double N = 3e8;
    double a[5] = {1, 3, 4, 2, 0};
    vector<double> b = {1, 3, 4, 2, 0};
    map<int, double> c = {{1, 1}, {2, 3}, {3, 4}, {4, 2}, {0, 0}};
    double sum(0);
    StartTimeChrono(1);
    for (int i = 0; i < N; i++)
    {
        sum += b[2];
    }
    StopTimeChrono(1);
    PrintTimeChrono(1, "vector");
    sum = 0;
    StartTimeChrono(2);
    for (int i = 0; i < N; i++)
    {
        sum += a[2];
    }
    StopTimeChrono(2);
    PrintTimeChrono(2, "array");
    sum = 0;
    double cc=LoadXMLConfig("sinsq12","JUNOYB",xmlfilePath);
    StartTimeChrono(3);
    for (int i = 0; i < N; i++)
    {
        // double cc = 1;
        // sum += c[2];
        sum += cc;
    }
    StopTimeChrono(3);
    PrintTimeChrono(3, "xml");
    return 0;
}
double *GetArr()
{
    static double Target[10];
    for (int i = 0; i < 10; i++)
    {
        Target[i] = 10 - i;
    }
    return Target;
}