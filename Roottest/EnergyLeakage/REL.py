#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
import ROOT

try:
    import numpy as np
except:
    print("Failed to import numpy.")
    exit()
#data path
HXD1 = "/junofs/users/huangx/production/J19v1r0-Pre3bk/IBD/uniform/IBD/detsim/user-detsim-10939.root"
HXD = "/junofs/users/huangx/production/J19v1r0-Pre3bk/IBD/uniform/IBD/detsim/user-detsim-"
#range and bin number
Ran_x = [0, 5300]
Ran_y = [-1, 1]
NBinx = 100
NBiny = 50


def AddFile2TChain(tree, NFiles=1):
    for nn in range(10000, 10000 + NFiles):
        if nn != 10216:
            tree.Add(HXD + str(nn) + ".root")


def DoR3CosThetaProfile(NFiles, SaveFileName="hitTime.png"):
    # ROOT.EnableImplicitMT()
    evt = ROOT.TChain("evt")
    geninfo = ROOT.TChain("geninfo")
    prmtrkdep = ROOT.TChain("prmtrkdep")
    for nn in range(10000, 10000 + NFiles):
        if nn != 10216:
            evt.Add(HXD + str(nn) + ".root")
            geninfo.Add(HXD + str(nn) + ".root")
            prmtrkdep.Add(HXD + str(nn) + ".root")

    evt.SetBranchStatus("*", 0)
    geninfo.SetBranchStatus("*", 0)
    prmtrkdep.SetBranchStatus("*", 0)
    evt.SetBranchStatus("hitTime", 1)
    # evt.SetBranchStatus("edep", 1)
    prmtrkdep.SetBranchStatus("edep", 1)
    # evt.SetBranchStatus("totalPE", 1)
    geninfo.SetBranchStatus("InitX", 1)
    geninfo.SetBranchStatus("InitY", 1)
    geninfo.SetBranchStatus("InitZ", 1)
    # prmtrkdep.GetEntry(int(sys.argv[1]))
    # hitTime=np.asarray(evt.hitTime)
    # print(np.asarray(prmtrkdep.edep))
    h_ep = ROOT.TH2F("EnergyProfile", "Simulation", NBinx, Ran_x[0], Ran_x[1],
                     NBiny, Ran_y[0], Ran_y[1])
    h_ep.SetXTitle("R^{3} (m^{3})")
    h_ep.SetYTitle("cos#theta")
    # entries in each bin
    BinValue = np.zeros(h_ep.GetSize())
    for i in range(0, evt.GetEntries()):
        evt.GetEntry(i)
        geninfo.GetEntry(i)
        prmtrkdep.GetEntry(i)
        edep = np.asarray(prmtrkdep.edep)
        PromptCount = np.sum(np.asarray(evt.hitTime) < 1200)
        EvtPos = ROOT.TVector3(geninfo.InitX[0] / 1e3, geninfo.InitY[0] / 1e3,
                               geninfo.InitZ[0] / 1e3)
        R_cubic = EvtPos.Mag2()**1.5
        Costheta = EvtPos.CosTheta()
        Photon2edep = float(PromptCount) / edep[0]
        ithBIN = h_ep.Fill(R_cubic, Costheta, Photon2edep)
        if (ithBIN > 0):
            BinValue[ithBIN - 1] += 1
    for i in range(0, BinValue.size):
        Contenti = h_ep.GetBinContent(i + 1)
        if BinValue[i] > 1:
            Contenti /= BinValue[i]
            h_ep.SetBinContent(i + 1, Contenti)
            # print("num:",BinValue[i],Contenti)
    c = ROOT.TCanvas("myCanvasName", "The Canvas Title", 800, 600)
    h_ep.Draw("colz")
    c.SaveAs("JUNOEnergyProfile.png")
    ff_EL = ROOT.TFile.Open("JUNOEnergyLeakage.root", "RECREATE")
    ff_EL.cd()
    h_ep.Write()
    ff_EL.Close()

    # x_min=0
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
    c.SaveAs(SaveFileName)


def nPE2R3profile(NFiles, SaveFileName="nPE2R3"):
    evt = ROOT.TChain("evt")
    prmtrkdep = ROOT.TChain("prmtrkdep")
    geninfo = ROOT.TChain("geninfo")
    AddFile2TChain(evt, NFiles=NFiles)
    AddFile2TChain(prmtrkdep, NFiles=NFiles)
    AddFile2TChain(geninfo, NFiles=NFiles)
    evt.SetBranchStatus("*", 0)
    prmtrkdep.SetBranchStatus("*", 0)
    geninfo.SetBranchStatus("*", 0)
    evt.SetBranchStatus("hitTime", 1)
    prmtrkdep.SetBranchStatus("edep", 1)
    geninfo.SetBranchStatus("InitX", 1)
    geninfo.SetBranchStatus("InitY", 1)
    geninfo.SetBranchStatus("InitZ", 1)
    h_PER3 = ROOT.TH2F("EnergyProfile", "Total PE", NBinx, Ran_x[0], Ran_x[1],
                       NBinx, 1200, 1600)
    h_PER3.SetXTitle("R^{3} (m^{3})")
    h_PER3.SetYTitle("totalPE/MeV")
    for i in range(0, evt.GetEntries()):
        evt.GetEntry(i)
        geninfo.GetEntry(i)
        prmtrkdep.GetEntry(i)
        edep = np.asarray(prmtrkdep.edep)
        PromptCount = np.sum(np.asarray(evt.hitTime) < 1200)
        EvtPos = ROOT.TVector3(geninfo.InitX[0] / 1e3, geninfo.InitY[0] / 1e3,
                               geninfo.InitZ[0] / 1e3)
        R_cubic = EvtPos.Mag2()**1.5
        Photon2edep = float(PromptCount) / edep[0]
        # print(R_cubic,Photon2edep,edep)
        h_PER3.Fill(R_cubic,Photon2edep)
    c = ROOT.TCanvas("myCanvasName", "The Canvas Title", 800, 600)
    h_PER3.Draw("colz")
    c.SaveAs(SaveFileName+".png")
    ff_PER3=ROOT.TFile.Open(SaveFileName+".root", "RECREATE")
    ff_PER3.cd()
    h_PER3.Write()
    ff_PER3.Close()


if __name__ == "__main__":
    # DoR3CosThetaProfile(NFiles=int(sys.argv[1]))
    nPE2R3profile(NFiles=int(sys.argv[1]))