#include <TXMLEngine.h>
#include <TXMLParser.h>
#include <stdio.h>
#include <string>
// using namespace std;
void DisplayNode(TXMLEngine &xml, XMLNodePointer_t node, Int_t level);
int ScanNode(TXMLEngine &xml, XMLNodePointer_t node);
void xmlnewfile(const char *filename);
void myNewXML(const char *filename);
void myReadXML(const char *filename);
void LoadXMLConfig(const char *VariableName,
                   double &Variable,
                   const char *filename);
const char *LoadXMLConfig(const char *VariableName,
                          const char *filename);
void LoadXMLConfig(const char *VariableName, const char *XMLNameSpace, double &Variable, const char *filename);

int XML1()
{
   // const char *filename = "modify.xml";
   // // First create engine
   // TXMLEngine xml;

   // // Now try to parse xml file
   // // Only file with restricted xml syntax are supported
   // XMLDocPointer_t xmldoc = xml.ParseFile(filename);
   // if (!xmldoc)
   //    return 0;

   // // take access to main node
   // XMLNodePointer_t mainnode = xml.DocGetRootElement(xmldoc);

   // // display recursively all nodes and subnodes
   // DisplayNode(xml, mainnode, 1);

   // // Release memory before exit
   // xml.FreeDoc(xmldoc);
   // myReadXML("modify.xml");

   const char *filename = "JUNOGlobalConfigs.xml";
   myNewXML(filename);
   // double BinWidth, E_LP, E_UP;
   // LoadXMLConfig("BinWidth", BinWidth, "JUNOConfigs.xml");
   // LoadXMLConfig("E_LP", E_LP, "JUNOConfigs.xml");
   // LoadXMLConfig("E_UP", E_UP, "JUNOConfigs.xml");
   // printf("BinWidth:%f\n", BinWidth);
   // printf("E_LP:%f\n", E_LP);
   // printf("E_UP:%f\n", E_UP);
   // printf("BinNUM:%d\n", (int)((E_UP - E_LP) / BinWidth));
   // const char *DefaultData = LoadXMLConfig("DefaultData", filename);
   // printf("DefaultData:%s\n", DefaultData);
   double dmsq32_NO;
   LoadXMLConfig("dmsq32_NO", "JUNOYB", dmsq32_NO, filename);
   printf("dmsq32_NO:%f\n", dmsq32_NO);
   return 0;
}
const char *LoadXMLConfig(const char *VariableName,
                          const char *filename)
{
   TXMLEngine tXML;
   XMLDocPointer_t tXMLDoc = tXML.ParseFile(filename);
   XMLNodePointer_t mainNode = tXML.DocGetRootElement(tXMLDoc);
   XMLNodePointer_t tNode0 = tXML.GetChild(mainNode);
   while (tNode0 != NULL)
   {
      if (strcmp(VariableName, tXML.GetNodeName(tNode0)) == 0)
      {
         return tXML.GetNodeContent(tNode0);
      }
      tNode0 = tXML.GetNext(tNode0);
   }
   return NULL;
}
void LoadXMLConfig(const char *VariableName,
                   const char *XMLNameSpace,
                   double &Variable,
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
            Variable = std::stod(std::string(tXML.GetNodeContent(tNode0)));
         }
      }
      tNode0 = tXML.GetNext(tNode0);
      tNS = tXML.GetNS(tNode0);
   }
}
void LoadXMLConfig(const char *VariableName,
                   double &Variable,
                   const char *filename)
{
   TXMLEngine tXML;
   XMLDocPointer_t tXMLDoc = tXML.ParseFile(filename);
   XMLNodePointer_t mainNode = tXML.DocGetRootElement(tXMLDoc);
   XMLNodePointer_t tNode0 = tXML.GetChild(mainNode);
   while (tNode0 != NULL)
   {
      if (strcmp(VariableName, tXML.GetNodeName(tNode0)) == 0)
      {
         Variable = std::stod(std::string(tXML.GetNodeContent(tNode0)));
      }
      tNode0 = tXML.GetNext(tNode0);
   }
}

void myReadXML(const char *filename)
{
   TXMLEngine myXML;
   XMLDocPointer_t myXMLDoc = myXML.ParseFile(filename);
   XMLNodePointer_t mainNode = myXML.DocGetRootElement(myXMLDoc);
   XMLNodePointer_t C1 = myXML.GetChild(mainNode);
   double BinWidth;

   //find what we need
   while (C1 != NULL)
   {
      if (strcmp(myXML.GetNodeName(C1), "BinWidth") == 0)
         BinWidth = std::stod(std::string(myXML.GetNodeContent(C1)));
      C1 = myXML.GetNext(C1);
   }

   // DisplayNode(myXML,mainNode,1);
   printf("%s=%f\n", myXML.GetNodeName(C1), BinWidth);

   myXML.FreeDoc(myXMLDoc);
}
//Create configration xml file
void myNewXML(const char *filename)
{
   TXMLEngine myXML;

   XMLNodePointer_t JUNONode = myXML.NewChild(0, 0, "JUNOConfigs");
   XMLNodePointer_t BinWith = myXML.NewChild(JUNONode, 0, "BinWidth", "0.02");
   myXML.NewAttr(BinWith, 0, "type", "double");
   myXML.NewAttr(BinWith, 0, "Note", "Analysis Energy Spectrum BinWidth");
   myXML.NewAttr(BinWith, 0, "Units", "MeV");
   XMLNodePointer_t E_LP = myXML.NewChild(JUNONode, 0, "E_LP", "1.3109989");
   myXML.NewAttr(E_LP, 0, "type", "double");
   myXML.NewAttr(E_LP, 0, "Note", "Lower Bound of Prompt Energy Spectrum");
   myXML.NewAttr(E_LP, 0, "Units", "MeV");
   XMLNodePointer_t E_UP = myXML.NewChild(JUNONode, 0, "E_UP", "8.5109989");
   myXML.NewAttr(E_UP, 0, "type", "double");
   myXML.NewAttr(E_UP, 0, "Note", "Upper Bound of Prompt Energy Spectrum");
   myXML.NewAttr(E_UP, 0, "Units", "MeV");
   XMLNodePointer_t JunoRuntime = myXML.NewChild(JUNONode, 0,
                                                 "JunoRuntime",
                                                 "2000");
   myXML.NewAttr(JunoRuntime, 0, "type", "double");
   myXML.NewAttr(JunoRuntime, 0, "Note", "Default JUNO Runtime in Analysis");
   myXML.NewAttr(JunoRuntime, 0, "Units", "day");
   XMLNodePointer_t a_res_Default = myXML.NewChild(JUNONode, 0,
                                                   "a_res_Default",
                                                   "2.62e-2");
   myXML.NewAttr(a_res_Default, 0, "type", "double");
   myXML.NewAttr(a_res_Default, 0, "Note", "Default JUNO Energy Resolution Model: a Term");
   myXML.NewAttr(a_res_Default, 0, "Units", "\\");
   XMLNodePointer_t b_res_Default = myXML.NewChild(JUNONode, 0,
                                                   "b_res_Default",
                                                   "0.73e-2");
   myXML.NewAttr(b_res_Default, 0, "type", "double");
   myXML.NewAttr(b_res_Default, 0, "Note", "Default JUNO Energy Resolution Model: b Term");
   myXML.NewAttr(b_res_Default, 0, "Units", "\\");
   XMLNodePointer_t c_res_Default = myXML.NewChild(JUNONode, 0,
                                                   "c_res_Default",
                                                   "1.38e-2");
   myXML.NewAttr(c_res_Default, 0, "type", "double");
   myXML.NewAttr(c_res_Default, 0, "Note", "Default JUNO Energy Resolution Model: b Term");
   myXML.NewAttr(c_res_Default, 0, "Units", "\\");
   XMLNodePointer_t dm21sq = myXML.NewChild(JUNONode, 0,
                                            "dm21sq",
                                            "7.54e-5");
   myXML.NewAttr(dm21sq, 0, "type", "double");
   myXML.NewAttr(dm21sq, 0, "Note", "DeltaM_21^2 Value Used in JUNO Yellow Book");
   myXML.NewAttr(dm21sq, 0, "Units", "eV^2");
   myXML.NewNS(dm21sq, "DOI:10.1088/0954-3899/43/3/030401", "JUNOYB");

   XMLNodePointer_t dmsq32_NO = myXML.NewChild(JUNONode, 0,
                                               "dmsq32_NO",
                                               "0.0023923");
   myXML.NewAttr(dmsq32_NO, 0, "type", "double");
   myXML.NewAttr(dmsq32_NO, 0, "Note", "DeltaM_32^2 Value for Normal Ordering Used in JUNO Yellow Book");
   myXML.NewAttr(dmsq32_NO, 0, "Units", "eV^2");
   myXML.NewNS(dmsq32_NO, "DOI:10.1088/0954-3899/43/3/030401", "JUNOYB");

   XMLNodePointer_t dmsq32_IO = myXML.NewChild(JUNONode, 0,
                                               "dmsq32_IO",
                                               "-0.0024177");
   myXML.NewAttr(dmsq32_IO, 0, "type", "double");
   myXML.NewAttr(dmsq32_IO, 0, "Note", "DeltaM_32^2 Value for Normal Ordering Used in JUNO Yellow Book");
   myXML.NewAttr(dmsq32_IO, 0, "Units", "eV^2");
   myXML.NewNS(dmsq32_IO, "DOI:10.1088/0954-3899/43/3/030401", "JUNOYB");

   XMLNodePointer_t sinsq12 = myXML.NewChild(JUNONode, 0,
                                             "sinsq12",
                                             "0.308");
   myXML.NewAttr(sinsq12, 0, "type", "double");
   myXML.NewAttr(sinsq12, 0, "Note", "sin^2(theta_12) Value Used in JUNO Yellow Book");
   myXML.NewAttr(sinsq12, 0, "Units", "\\");
   myXML.NewNS(sinsq12, "DOI:10.1088/0954-3899/43/3/030401", "JUNOYB");

   XMLNodePointer_t sinsq13_NO = myXML.NewChild(JUNONode, 0,
                                                "sinsq13_NO",
                                                "0.0234");
   myXML.NewAttr(sinsq13_NO, 0, "type", "double");
   myXML.NewAttr(sinsq13_NO, 0, "Note", "sin^2(theta_1) Value for Normal Ordering Used in JUNO Yellow Book");
   myXML.NewAttr(sinsq13_NO, 0, "Units", "\\");
   myXML.NewNS(sinsq13_NO, "DOI:10.1088/0954-3899/43/3/030401", "JUNOYB");

   XMLNodePointer_t sinsq13_IO = myXML.NewChild(JUNONode, 0,
                                                "sinsq13_IO",
                                                "0.0240");
   myXML.NewAttr(sinsq13_IO, 0, "type", "double");
   myXML.NewAttr(sinsq13_IO, 0, "Note", "sin^2(theta_1) Value for Normal Ordering Used in JUNO Yellow Book");
   myXML.NewAttr(sinsq13_IO, 0, "Units", "\\");
   myXML.NewNS(sinsq13_IO, "DOI:10.1088/0954-3899/43/3/030401", "JUNOYB");

   XMLNodePointer_t DefaultData = myXML.NewChild(JUNONode, 0,
                                                 "DefaultData",
                                                 "SoCallData_NO.root");
   myXML.NewAttr(DefaultData, 0, "type", "string");
   myXML.NewAttr(DefaultData, 0, "Note", "Default Prompt Signal Spectrum Data File Path");
   myXML.NewAttr(DefaultData, 0, "Units", "\\");
   XMLNodePointer_t DefaultBkg = myXML.NewChild(JUNONode, 0,
                                                "DefaultBkg",
                                                "../data/Background/JunoBkg.root");
   myXML.NewAttr(DefaultBkg, 0, "type", "string");
   myXML.NewAttr(DefaultBkg, 0, "Note", "Default Backgrounds Spectra Data File Path");
   myXML.NewAttr(DefaultBkg, 0, "Units", "\\");
   XMLNodePointer_t DefaultDataObj = myXML.NewChild(JUNONode, 0,
                                                    "DefaultDataObj",
                                                    "h_NMO");
   myXML.NewAttr(DefaultDataObj, 0, "type", "string");
   myXML.NewAttr(DefaultDataObj, 0, "Note", "Default ROOT::TObject Name of Prompt Signal Spectrum");
   myXML.NewAttr(DefaultDataObj, 0, "Units", "\\");
   XMLNodePointer_t JUNO_NL_file = myXML.NewChild(JUNONode, 0,
                                                  "JUNO_NL_file",
                                                  "../data/JunoFullNL.root");
   myXML.NewAttr(JUNO_NL_file, 0, "type", "string");
   myXML.NewAttr(JUNO_NL_file, 0, "Note", "Default Liquid Scintillator Nonlinearity Data File Path");
   myXML.NewAttr(JUNO_NL_file, 0, "Units", "\\");
   XMLNodePointer_t DefaultNLObj = myXML.NewChild(JUNONode, 0,
                                                  "DefaultNLObj",
                                                  "positronFullNL");
   myXML.NewAttr(DefaultNLObj, 0, "type", "string");
   myXML.NewAttr(DefaultNLObj, 0, "Note", "Default ROOT::TObject Name of Liquid Scintillator Nonlinearity Curve");
   myXML.NewAttr(DefaultNLObj, 0, "Units", "\\");
   XMLNodePointer_t FluxDataFile = myXML.NewChild(JUNONode, 0,
                                                  "FluxDataFile",
                                                  "../data/Flux/HuberMuellerFlux.root");
   myXML.NewAttr(FluxDataFile, 0, "type", "string");
   myXML.NewAttr(FluxDataFile, 0, "Note", "Default Reactor Neutrino Flux Model Data File Path");
   myXML.NewAttr(FluxDataFile, 0, "Units", "\\");

   XMLDocPointer_t myXMLdoc = myXML.NewDoc();
   myXML.DocSetRootElement(myXMLdoc, JUNONode);
   myXML.SaveDoc(myXMLdoc, filename);
   myXML.FreeDoc(myXMLdoc);
}

void DisplayNode(TXMLEngine &xml, XMLNodePointer_t node, Int_t level)
{
   // this function display all accessible
   // information about xml node and its children

   printf("%*c node: %s\n",
          level, ' ', xml.GetNodeName(node));

   // display namespace
   XMLNsPointer_t ns = xml.GetNS(node);
   if (ns != 0)
      printf("%*c namespace: %s refer: %s\n",
             level + 2, ' ',
             xml.GetNSName(ns), xml.GetNSReference(ns));

   // display attributes
   XMLAttrPointer_t attr = xml.GetFirstAttr(node);
   while (attr != 0)
   {
      printf("%*c attr: %s value: %s\n",
             level + 2, ' ',
             xml.GetAttrName(attr), xml.GetAttrValue(attr));
      attr = xml.GetNextAttr(attr);
   }

   // display content (if exists)
   const char *content = xml.GetNodeContent(node);
   if (content != 0)
      printf("%*c cont: %s\n", level + 2, ' ', content);

   // display all child nodes
   XMLNodePointer_t child = xml.GetChild(node);
   while (child != 0)
   {
      DisplayNode(xml, child, level + 2);
      child = xml.GetNext(child);
   }
}
// scan node and returns number of childs
// for each child create info node with name and number of childs
int ScanNode(TXMLEngine &xml, XMLNodePointer_t node)
{
   int cnt = 0;
   XMLNodePointer_t child = xml.GetChild(node);
   while (child)
   {
      cnt++;

      int numsub = ScanNode(xml, child);

      // create new <info> node
      XMLNodePointer_t info = xml.NewChild(node,
                                           xml.GetNS(child), "info");

      // set name and num attributes of info node
      xml.NewAttr(info, 0, "name", xml.GetNodeName(child));
      if (numsub > 0)
         xml.NewIntAttr(info, "num", numsub);

      // move it after current node
      xml.AddChildAfter(node, info, child);

      // set pointer to new node
      child = info;

      xml.ShiftToNext(child);
   }
   return cnt;
}
void xmlnewfile(const char *filename)
{
   // First create engine
   TXMLEngine xml;

   // Create main node of document tree
   XMLNodePointer_t mainnode = xml.NewChild(0, 0, "main");

   // Simple child node with content inside
   xml.NewChild(mainnode, 0, "child1", "Content of child1 node");

   // Other child node with attributes
   XMLNodePointer_t child2 = xml.NewChild(mainnode, 0, "child2");
   xml.NewAttr(child2, 0, "attr1", "value1");
   xml.NewAttr(child2, 0, "attr2", "value2");

   // Child node with subnodes
   XMLNodePointer_t child3 = xml.NewChild(mainnode, 0, "child3");
   xml.NewChild(child3, 0, "subchild1", "subchild1 content");
   xml.NewChild(child3, 0, "subchild2", "subchild2 content");
   xml.NewChild(child3, 0, "subchild3", "subchild3 content");

   // Child node with subnodes and namespace
   XMLNodePointer_t child4 = xml.NewChild(mainnode, 0, "child4");
   XMLNsPointer_t ns4 = xml.NewNS(child4, "http://website/webpage");
   xml.NewChild(child4, ns4, "subchild1", "subchild1 content");
   xml.NewChild(child4, ns4, "subchild2", "subchild2 content");
   xml.NewChild(child4, ns4, "subchild3", "subchild3 content");

   // now create document and assign main node of document
   XMLDocPointer_t xmldoc = xml.NewDoc();
   xml.DocSetRootElement(xmldoc, mainnode);

   // Save document to file
   xml.SaveDoc(xmldoc, filename);

   // Release memory before exit
   xml.FreeDoc(xmldoc);
}