import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import LinearSegmentedColormap
plt.style.use("./Style/Paper.mplstyle")


cdict = {
    "red": [(0.0, 0.0, 0.0), (0.5, 1.0, 1.0), (1.0, 1.0, 1.0)],
    "green": [(0.0, 0.0, 0.0), (0.25, 0.0, 0.0), (0.75, 1.0, 1.0),
              (1.0, 1.0, 1.0)],
    "blue": [(0.0, 0.0, 0.0), (0.5, 0.0, 0.0), (1.0, 1.0, 1.0)],
}

colors = [(0, 0, 1), (0, 1, 0), (1, 0, 0)]
cm = LinearSegmentedColormap("cmap", cdict, N=32)

data = np.loadtxt("DataProfile.txt")

x = data[:, 0].reshape(100, 50).swapaxes(1, 0)
y = data[:, 1].reshape(100, 50).swapaxes(1, 0)
z = data[:, 2].reshape(100, 50).swapaxes(1, 0)
zx = np.average(z, 0)
zy = np.average(z, 1)

ax0 = plt.subplot2grid((2, 3), (0, 0), 1, 2)
ax1 = plt.subplot2grid((2, 3), (1, 0), 1, 2)
ax2 = plt.subplot2grid((2, 3), (1, 2), 1, 1)

ax0.step(np.arange(100), zx, "k")
ax0.set_xticklabels([])
ax2.step(zy, np.arange(0, 50), "k")
ax2.set_yticklabels([])
ax1.imshow(z, cmap=cm, interpolation="nearest", origin="lower", aspect="auto")
ax1.set_aspect("auto")

plt.sca(ax0)
plt.xlim(0, 99)
plt.sca(ax2)
plt.ylim(0, 49)
plt.sca(ax1)
plt.xticks(np.arange(0, 100, 9), x[0, ::9].astype("int"))
plt.yticks(np.arange(0, 50, 7), y[::7, 0])

plt.subplots_adjust(wspace=0, hspace=0)
plt.show()
