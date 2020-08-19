#!/usr/bin/env python
# -*- coding: utf-8 -*-

from REL import *
from ViewTime import *


def TryChainFriend(NFiles):
    evt = ROOT.TChain("evt")
    prmtrkdep = ROOT.TChain("prmtrkdep")
    geninfo = ROOT.TChain("geninfo")
    nCapture = ROOT.TChain("nCapture")
    AddFile2TChain(evt, NFiles=NFiles)
    AddFile2TChain(prmtrkdep, NFiles=NFiles)
    AddFile2TChain(geninfo, NFiles=NFiles)
    AddFile2TChain(nCapture, NFiles=NFiles)
    evt.AddFriend("prmtrkdep")
    evt.AddFriend("geninfo")
    evt.AddFriend("nCapture")
    # evt.MakeSelector("GetPE2R3")
    evt.Process("GetPE2R3.C+", "prmtrkdep geninfo nCapture")
    # evt.ls()


if __name__ == "__main__":
    TryChainFriend(int(sys.argv[1]))