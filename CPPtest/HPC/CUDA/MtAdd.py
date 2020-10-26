#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
from numba import vectorize


@vectorize(['float32(float32,float32)'], target='cuda')
def Add(a, b):
    return a + b


if __name__ == "__main__":
    N = 10000
    A = np.ones(N, dtype=np.float32)
    B = np.ones(A.shape, dtype=A.dtype)
    C = np.empty_like(A, dtype=A.dtype)

    C = Add(A, B)
