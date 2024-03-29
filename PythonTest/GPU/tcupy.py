#!/usr/bin/env python3
# -*- coding: utf-8 -*-
from turtle import up
import numpy as np
import uproot


def get_parser():
    import argparse
    parser = argparse.ArgumentParser(description="Options in this test")
    parser.add_argument("--Mul",
                        action="store_true",
                        default=False,
                        help="Test matrix multiply")
    parser.add_argument("--Mul-file",
                        default="../plots/Contour/DataProfile.txt",
                        help="Test matrix multiply input filename")
    parser.add_argument("--numpy-IO",
                        action="store_true",
                        default=False,
                        help="Test numpy file IO")
    parser.add_argument("--numpy-IO-file",
                        default="tnumpy",
                        help="Test numpy file IO filename")
    parser.add_argument('-D',
                        '--tDot',
                        action='store_true',
                        default=False,
                        help='Test the dot operation.')
    parser.add_argument('-R',
                        '--Response',
                        action='store_true',
                        default=False,
                        help='Test response matrix.')

    return parser


def MatMultiply(filename="../plots/Contour/DataProfile.txt"):
    import ROOT
    import cupy as cp
    data = np.loadtxt(filename)
    R_x = data[:, 0].reshape(100, 50)
    Cos_y = data[:, 1].reshape(100, 50)
    nPE_z = data[:, 2].reshape(100, 50)
    Response_M = np.matrix(nPE_z)
    M_gpu = cp.asarray(Response_M)
    ans_gpu = cp.dot(cp.asarray(R_x[:, 0]), M_gpu)
    print("GPU:")
    # print(ans_gpu)
    print("CPU:")
    ans_cpu = np.dot(R_x[:, 0], Response_M)
    # print(ans_cpu)
    diff = cp.asnumpy(ans_gpu) - ans_cpu
    print("diff:\n", diff)


def t_npIO(filename):
    x_data = np.linspace(0, 10)
    np.savez(filename, x_data=x_data)


def Test_dot():
    try:
        import cupy as np
    except:
        import numpy as np
    # import numpy as np
    A = np.random.rand(1024, 1024)
    B = np.random.rand(1024, 1024)
    print(np.matmul(A, B))


def T_Mres():
    file_response=uproot.open("respMatrix_fill.root")
    


if __name__ == "__main__":
    parser = get_parser()
    args = parser.parse_args()
    if args.Mul:
        MatMultiply(filename=args.Mul_file)
    elif args.numpy_IO:
        t_npIO(args.numpy_IO_file)
    if args.tDot:
        Test_dot()
    if args.Response:
        T_Mres()

    # MatMultiply()
