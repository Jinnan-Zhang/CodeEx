#!/usr/bin/env python
# -*- coding: utf-8 -*-
try:
    import numpy as np
except:
    print("Failed to import numpy.")
    exit()
x,y=np.loadtxt("data/AntineutrinoSpectrum_238U.knt",unpack=True,skiprows=5)
print(x.shape)