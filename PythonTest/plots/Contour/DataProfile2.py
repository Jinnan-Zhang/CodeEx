import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import LinearSegmentedColormap
from matplotlib.ticker import MultipleLocator, AutoMinorLocator


def setLocator(ax, majorX, minorX, majorY, minorY):
    ax.xaxis.set_major_locator(MultipleLocator(majorX))
    ax.xaxis.set_minor_locator(AutoMinorLocator(minorX))
    ax.yaxis.set_major_locator(MultipleLocator(majorY))
    ax.yaxis.set_minor_locator(AutoMinorLocator(minorY))


def swapLine(ax):
    lineX, lineY = ax.lines[0].get_data()
    ax.lines[0].set_data(lineY, lineX)
    limX = ax.get_xlim()
    limY = ax.get_ylim()
    ax.set_xlim(limY)
    ax.set_ylim(limX)


plt.style.use("./Style/Paper.mplstyle")

Nx, Ny = 100, 50
majorX, majorY = 9, 7  # (100-1)/9=11 (50-1)/7=7
minorX, minorY = 9, 7  # 9/9=1 7/7=1
majorInt, minorInt = 25, 5  # 25/5=5

cdict = {
    "red": [(0.0, 0.0, 0.0), (0.5, 1.0, 1.0), (1.0, 1.0, 1.0)],
    "green": [(0.0, 0.0, 0.0), (0.25, 0.0, 0.0), (0.75, 1.0, 1.0), (1.0, 1.0, 1.0)],
    "blue": [(0.0, 0.0, 0.0), (0.5, 0.0, 0.0), (1.0, 1.0, 1.0)],
}
cmap = LinearSegmentedColormap("cmap", cdict, N=32)

data = np.loadtxt("DataProfile.txt")

x = data[:, 0].reshape(Nx, Ny).swapaxes(1, 0)
y = data[:, 1].reshape(Nx, Ny).swapaxes(1, 0)
z = data[:, 2].reshape(Nx, Ny).swapaxes(1, 0)
zx = np.average(z, 0)
zy = np.average(z, 1)
zx = np.concatenate((zx[[0]], zx))
zy = np.concatenate((zy, zy[[-1]]))

ax0 = plt.subplot2grid((2, 4), (0, 0), 1, 3)
ax1 = plt.subplot2grid((2, 4), (1, 0), 1, 3)
ax2 = plt.subplot2grid((2, 4), (1, 3), 1, 1)

ax0.step(np.arange(-1, Nx) + 0.5, zx, "k")
ax0.set_xticklabels([])
ax0.set_xlim(-0.5, Nx - 0.5)
setLocator(ax0, majorX, minorX, majorInt, minorInt)

ax2.step(np.arange(-1, Ny) + 0.5, zy, "k")
swapLine(ax2)
ax2.set_yticklabels([])
ax2.set_ylim(-0.5, Ny - 0.5)
setLocator(ax2, majorInt, minorInt, majorY, minorY)

ax1.imshow(z, cmap=cmap, interpolation="nearest", origin="lower", aspect="auto")
ax1.set_aspect("auto")
setLocator(ax1, majorX, minorX, majorY, minorY)

plt.sca(ax1)
plt.xticks(np.arange(0, Nx, majorX), x[0, ::majorX].astype("int"))
plt.yticks(np.arange(0, Ny, majorY), y[::majorY, 0])

plt.subplots_adjust(wspace=0, hspace=0)
plt.show()
