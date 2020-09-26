import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import MultipleLocator, FormatStrFormatter

chisqIO=np.loadtxt("chisqIO.txt")
chisqNO=np.loadtxt("chisqNO.txt")

fig = plt.figure()
plt.plot(chisqIO[:, 0], chisqIO[:, 1], c="red",label = 'IH fit to NH')
plt.plot(chisqNO[:, 0], chisqNO[:, 1], c="black",label='NH fit to NH')

plt.legend(loc='best', fontsize=20)
plt.xlabel('$|\Delta m_{31}^2|(x 10^{-3} eV^2)$', fontsize=18)
plt.ylabel('$\Delta \chi^2$', fontsize=18)

xmajorLocator = MultipleLocator(0.02)  # 将x主刻度标签设置为2的倍数
xminorLocator = MultipleLocator(0.01)  # 将x轴次刻度标签设置为0.5的倍数
ymajorLocator = MultipleLocator(5)  # 将y轴主刻度标签设置为1的倍数
yminorLocator = MultipleLocator(2.5)  # 将此y轴次刻度标签设置为0.2的倍数
ax = plt.subplot(111)
ax.xaxis.set_major_locator(xmajorLocator)
ax.xaxis.set_minor_locator(xminorLocator)
ax.yaxis.set_major_locator(ymajorLocator)
ax.yaxis.set_minor_locator(yminorLocator)
plt.tick_params(labelsize=18)

plt.ylim(0, 25)
plt.xlim(2.35, 2.65)
plt.hlines(9, 2.1, 2.74, color='black', linestyles="dashed", alpha=0.7)
plt.hlines(16, 2.1, 2.74, color='black', linestyles="dashed", alpha=0.7)
plt.text(2.44, 9.25, "3$\sigma$", fontsize=18)
plt.text(2.44, 16.25, "4$\sigma$", fontsize=18)
plt.show()