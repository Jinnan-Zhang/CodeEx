#ifndef HelloWorld_h
#define HelloWorld_h

#include <cuda_runtime.h>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cublas_v2.h>
#include "cublas_utils.h"
#include "time_macro.h"
__global__ void helloworld(void);
void random_ints(int *a, int n);
__global__ void mul(int *a, int *b, int *sub_sum);
void DoVector();


#endif