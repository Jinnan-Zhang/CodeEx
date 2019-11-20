from ROOT import TH1,TF1,TCanvas

c1=TCanvas("c1")
f1=TF1("f1","sin(x)",-1,1)
f1.Draw()
c1.Update()
raw_input()