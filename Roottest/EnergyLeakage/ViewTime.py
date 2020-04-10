#!/usr/bin/python
# -*- coding: utf-8 -*-
from REL import *
import sys
import ROOT

try:
    import numpy as np
except:
    print("Failed to import numpy.")
    exit()

if __name__ == "__main__":
    ROOT.EnableImplicitMT()
    