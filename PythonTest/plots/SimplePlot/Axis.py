import matplotlib.pyplot as plt
from matplotlib.ticker import MultipleLocator, FormatStrFormatter
import numpy as np

myfontsize=24
labelsize_zjn=24
Ltick_zjn_M=24
Ltick_zjn_m=12
Wtick_zjn_M=2
Wtich_zjn_m=1
Titlex="x Title"
Titley="y Title"

x = np.linspace(-5, 5, 100)
y1 = 0.5 * x

fig, ax = plt.subplots()

plt.plot(x,y1)
ax.set_xlabel(Titlex,fontsize=myfontsize,x=0.8)
ax.set_ylabel(Titley,fontsize=myfontsize)

plt.tick_params(labelsize=labelsize_zjn,top=True,right=True)
plt.tick_params(which='major',length=Ltick_zjn_M,width=Wtick_zjn_M,direction="in")
plt.tick_params(which='minor',length=Ltick_zjn_m,width=Wtich_zjn_m,direction="in")
plt.minorticks_on()#次刻度线


ax.spines['bottom'].set_linewidth(4);###设置底部坐标轴的粗细
ax.spines['left'].set_linewidth(4);####设置左边坐标轴的粗细
ax.spines['right'].set_linewidth(4);###设置右边坐标轴的粗细
ax.spines['top'].set_linewidth(4);####设置上部坐标轴的粗细
plt.show()
