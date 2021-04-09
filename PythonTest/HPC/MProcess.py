#!/usr/bin/env python
# -*- coding=utf8 -*-
def get_parser():
    import argparse
    parser = argparse.ArgumentParser(description="Multiprocess")
    parser.add_argument(
        "--MulP",
        action="store_true",
        default=False,
        help="Simple multi-process."
    )

    return parser
def fun(x):
    return x**2

def tMulP():
    from multiprocessing import Pool
    
    p=Pool()
    print(p.map(fun,[1,2,3]))

if __name__=="__main__":
    parser = get_parser()
    args = parser.parse_args()
    if args.MulP:
        tMulP()