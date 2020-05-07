//purpose: test template function method
#include <TXMLEngine.h>

template <class AnyType>
void LoadXMLConfig(const char *VariableName,
                   AnyType &Variable,
                   const char *filename)
{
    TXMLEngine tXML;
    XMLDocPointer_t tXMLDoc = tXML.ParseFile(filename);
    XMLNodePointer_t mainNode = tXML.DocGetRootElement(tXMLDoc);
    XMLNodePointer_t tNode0 = tXML.GetChild(mainNode);
    while (tNode0 != NULL)
    {
        if (strcmp(VariableName, tXML.GetNodeName(tNode0)) == 0)
            Variable = stod(string(tXML.GetNodeContent(tNode0)));
        tNode0 = tXML.GetNext(tNode0);
    }
}

int TemFCN()
{
}