import sys
import ROOT

try:
    import numpy as np
except:
    print("Failed to import numpy.")
    exit()
#data path
HXD1 ="/junofs/users/huangx/production/J19v1r0-Pre3bk/IBD/uniform/IBD/detsim/user-detsim-10939.root"
HXD= "/junofs/users/huangx/production/J19v1r0-Pre3bk/IBD/uniform/IBD/detsim/user-detsim-"
if __name__ == "__main__":    
    ROOT.ROOT.EnableImplicitMT()
    evt=ROOT.TChain("evt")
    geninfo=ROOT.TChain("geninfo")
    for nn in range(10000,10001):
        if nn!=10216:
            evt.Add(HXD+str(nn)+".root")
            geninfo.Add(HXD+str(nn)+".root")

    evt.SetBranchStatus("*", 0)
    evt.SetBranchStatus("hitTime", 1)
    evt.SetBranchStatus("totalPE", 1)
    # evt.GetEntry(int(sys.argv[1]))
    for i in range(1,evt.GetEntries()):
        evt.GetEntry(i)
        hitTime=np.asarray(evt.hitTime)
        print(hitTime.size)
    # print float(np.sum(hitTime<1200))/hitTime.size

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