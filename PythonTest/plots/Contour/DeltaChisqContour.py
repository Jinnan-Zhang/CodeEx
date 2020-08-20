#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
import ROOT
import matplotlib.pyplot as plt


def ShowContour(FileName="CosProfile.txt"):
    DataPts = np.loadtxt(fname=FileName, skiprows=1)
    x = DataPts[:, 1]
    y = DataPts[:, 0]
    # plt.scatter(x,y)
    plt.plot(x,y)
    plt.show()


if __name__ == "__main__":
    ShowContour()