#!/usr/bin/python
# -*- coding: utf-8 -*-
from REL import *
# import sys
# import ROOT

# try:
#     import numpy as np
# except:
#     print("Failed to import numpy.")
#     exit()

if __name__ == "__main__":
    ROOT.EnableImplicitMT()
    evt = ROOT.TChain("evt")
    for nn in range(10000, 10001):
        if nn != 10216:
            evt.Add(HXD + str(nn) + ".root")
    evt.SetBranchStatus("*", 0)
    evt.SetBranchStatus("hitTime", 1)
    evt.GetEntry(int(sys.argv[1]))
    x_min=0
    # float(sys.argv[2])
    # x_max=np.max(hitTime)
    # float(sys.argv[3])
    # h_hit=ROOT.TH1D("myhist","",200,x_min,x_max)
    # print h_hit.GetEntries(),evt.totalPE
    # evt.Draw("totalPE>>+myhist","hitTime>1200")
    # for i in hitTime:
    #     h_hit.Fill(i)
    # c = ROOT.TCanvas("myCanvasName","The Canvas Title",800,600)
    # h_hit.Draw()
    # c.SaveAs("hitTime.png")