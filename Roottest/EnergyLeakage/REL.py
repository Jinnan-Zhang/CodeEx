import ROOT

try:
    import numpy as np
except:
    print("Failed to import numpy.")
    exit()
HXD1 ="/junofs/users/huangx/production/J19v1r0-Pre3bk/IBD/uniform/IBD/detsim/user-detsim-10939.root"
# ROOT.ROOT.EnableImplicitMT()
evt=ROOT.TChain("evt")
evt.Add(HXD1)
evt.SetBranchStatus("*", 0)
evt.SetBranchStatus("hitTime", 1)
evt.GetEntry(1)
hitTime=np.asarray(evt.hitTime)
h_hit=ROOT.TH1D("hitTime","",200,0,800)
for i in hitTime:
    h_hit.Fill(i)
c = ROOT.TCanvas("myCanvasName","The Canvas Title",800,600)
h_hit.Draw()
c.SaveAs("hitTime.png")