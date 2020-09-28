#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import cupy as cp
import numpy as np
import ROOT


def MatMultiply(filename="../plots/Contour/DataProfile.txt"):
    data = np.loadtxt(filename)
    print(data.size)
    R_x = data[:, 0].reshape(50, 50)
    Cos_x = data[:, 1].reshape(50, 50)
    nPE_y = data[:, 2].reshape(50, 50)


if __name__ == "__main__":
    MatMultiply()