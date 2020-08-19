#!/usr/bin/env python
# -*- coding: utf-8 -*-
from REL import *
# import sys
# import ROOT

# try:
#     import numpy as np
# except:
#     print("Failed to import numpy.")
#     exit()


def DrawNCaptureTime(NFiles, SaveFileName="nCapture.png"):
    # ROOT.EnableImplicitMT()
    evt = ROOT.TChain("evt")
    nCapture = ROOT.TChain("nCapture")
    AddFile2TChain(nCapture, NFiles=NFiles)
    AddFile2TChain(evt, NFiles=NFiles)
    evt.SetBranchStatus("*", 0)
    nCapture.SetBranchStatus("*", 0)
    # evt.SetBranchStatus("hitTime", 1)
    evt.SetBranchStatus("totalPE", 1)
    nCapture.SetBranchStatus("NeutronCaptureT", 1)
    # nCapture.GetEntry(0)
    evt.GetEntry(0)
    # NeutronCaptureT = np.asarray(nCapture.NeutronCaptureT)
    print(evt.totalPE)
    # nCapture.ls()
    # # evt.GetEntry(int(sys.argv[1]))
    # # nCapture.GetEntry(int(sys.argv[1]))
    # x_min =np.min(NeutronCaptureT)
    # # float(sys.argv[2])
    # x_max = np.max(NeutronCaptureT)
    # # float(sys.argv[3])
    # h_cap = ROOT.TH1F("myhist", "", 200, x_min, x_max)
    # # print h_cap.GetEntries(),evt.totalPE
    # c = ROOT.TCanvas("myCanvasName", "The Canvas Title", 800, 600)
    # # nCapture.Draw("NeutronCaptureT>>+myhist")
    # # for i in hitTime:
    # #     h_cap.Fill(i)
    # # h_cap.Draw()
    # c.SaveAs(SaveFileName)


def DrawHitTime(NFiles, WhichEntry=1, SaveFileName="hitTime.png"):
    evt = ROOT.TChain("evt")
    AddFile2TChain(evt, NFiles=NFiles)
    evt.SetBranchStatus("*", 0)
    evt.SetBranchStatus("hitTime", 1)
    # hitTime=np.asarray(evt.hitTime)
    c = ROOT.TCanvas("myCanvasName", "The Canvas Title", 800, 600)
    # evt.GetEntry(WhichEntry)
    evt.Draw("hitTime>>+h_hitTime(100,263e3,2.655e5", "", "", 1, WhichEntry)
    ROOT.gStyle.SetOptStat("ne")

    c.SaveAs(SaveFileName)

if __name__ == "__main__":
    DrawNCaptureTime(NFiles=int(sys.argv[1]))
    # DrawHitTime(NFiles=1,WhichEntry=int(sys.argv[1]))