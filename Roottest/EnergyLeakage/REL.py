import sys
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
evt.GetEntry(int(sys.argv[1]))
hitTime=np.asarray(evt.hitTime)
print np.sum(hitTime<1200),hitTime.size
x_min=float(sys.argv[2])
x_max=float(sys.argv[3])
h_hit=ROOT.TH1D("hitTime","",200,x_min,x_max)
for i in hitTime:
    h_hit.Fill(i)
c = ROOT.TCanvas("myCanvasName","The Canvas Title",800,600)
h_hit.Draw()
c.SaveAs("hitTime.png")