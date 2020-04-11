#!/usr/bin/env python
# -*- coding: utf-8 -*-

from REL import *
from ViewTime import *
def TryChainFriend(NFiles):
    evt = ROOT.TChain("evt")
    prmtrkdep = ROOT.TChain("prmtrkdep")
    AddFile2TChain(evt,NFiles=NFiles)
    AddFile2TChain(prmtrkdep,NFiles=NFiles)
    evt.AddFriend("prmtrkdep")
    # evt.MakeSelector("GetPE2R3")
    evt.Process("GetPE2R3.C")
    # evt.ls()

if __name__ == "__main__":
    TryChainFriend(int(sys.argv[1]))