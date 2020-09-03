import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import LinearSegmentedColormap
from matplotlib.ticker import MultipleLocator, AutoMinorLocator


def set_locator(ax, majorX, minorX, majorY, minorY):
    ax.xaxis.set_major_locator(MultipleLocator(majorX))
    ax.xaxis.set_minor_locator(AutoMinorLocator(minorX))
    ax.yaxis.set_major_locator(MultipleLocator(majorY))
    ax.yaxis.set_minor_locator(AutoMinorLocator(minorY))


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
zx = np.concatenate((zx[[-1]], zx))
zy = np.concatenate((zy[[-1]], zy))


ax0 = plt.subplot2grid((2, 4), (0, 0), 1, 3)
ax1 = plt.subplot2grid((2, 4), (1, 0), 1, 3)
ax2 = plt.subplot2grid((2, 4), (1, 3), 1, 1)

ax0.step(np.arange(-1, Nx) + 0.5, zx, "k")
ax0.set_xticklabels([])
set_locator(ax0, majorX, minorX, majorInt, minorInt)

ax2.step(zy, np.arange(-1, Ny) + 0.5, "k")
ax2.set_yticklabels([])
set_locator(ax2, majorInt, minorInt, majorY, minorY)

ax1.imshow(z, cmap=cmap, interpolation="nearest", origin="lower", aspect="auto")
ax1.set_aspect("auto")
set_locator(ax1, majorX, minorX, majorY, minorY)

plt.sca(ax0)
plt.xlim(-0.5, Nx - 0.5)
plt.tick_params(which="both", direction="in", top="on", right="on")

plt.sca(ax2)
plt.ylim(-0.5, Ny - 0.5)
plt.tick_params(which="both", direction="in", top="on", right="on")

plt.sca(ax1)
plt.xticks(np.arange(0, Nx, majorX), x[0, ::majorX].astype("int"))
plt.yticks(np.arange(0, Ny, majorY), y[::majorY, 0])
plt.tick_params(which="both", direction="in", top="on", right="on")

plt.subplots_adjust(wspace=0, hspace=0)
plt.show()
