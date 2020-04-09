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
evt.SetBranchStatus("totalPE", 1)
evt.GetEntry(int(sys.argv[1]))
hitTime=np.asarray(evt.hitTime)
# print float(np.sum(hitTime<1200))/hitTime.size

x_min=0
# float(sys.argv[2])
x_max=np.max(hitTime)
# float(sys.argv[3])
h_hit=ROOT.TH1D("myhist","",200,x_min,x_max)
print h_hit.GetEntries(),evt.totalPE
evt.Draw("totalPE>>+myhist","hitTime>1200")
# for i in hitTime:
#     h_hit.Fill(i)
# c = ROOT.TCanvas("myCanvasName","The Canvas Title",800,600)
# h_hit.Draw()
# c.SaveAs("hitTime.png")