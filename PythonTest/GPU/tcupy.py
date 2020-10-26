#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import cupy as cp
import numpy as np
import ROOT


def MatMultiply(filename="../plots/Contour/DataProfile.txt"):
    data = np.loadtxt(filename)
    R_x = data[:, 0].reshape(100, 50)
    Cos_y = data[:, 1].reshape(100, 50)
    nPE_z = data[:, 2].reshape(100, 50)
    Response_M = np.matrix(nPE_z)
    M_gpu = cp.asarray(Response_M)
    print(M_gpu[0][0])
    ans_gpu = cp.dot(cp.asarray(R_x[:, 0]), M_gpu)
    print(ans_gpu)


if __name__ == "__main__":
    MatMultiply()