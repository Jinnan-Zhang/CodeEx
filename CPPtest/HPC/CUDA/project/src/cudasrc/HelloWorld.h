#ifndef HelloWorld_cuh
#define HelloWorld_cuh
#pragma once
/*
usage:
StartTimeChrono(num);
...
StopTimeChrono(num);
PrintTimeChrono(num,"discription")
*/
#include <chrono>

#define StartTimeChrono(_num) \
    auto start##_num = std::chrono::high_resolution_clock::now()

#define StopTimeChrono(_num) \
    auto stop##_num = std::chrono::high_resolution_clock::now()

#ifdef _WIN32
#define PrintTimeChrono(_num, _str)                                                                    \
    auto dura##_num = std::chrono::duration_cast<std::chrono::microseconds>(stop##_num - start##_num); \
    printf("Time for calculating %s is %f millisecond.\n", _str, dura##_num.count())
#else
#define PrintTimeChrono(_num, _str)                                                                    \
    auto dura##_num = std::chrono::duration_cast<std::chrono::microseconds>(stop##_num - start##_num); \
    printf("Time for calculating %s is %.8f second.\n", _str, dura##_num.count() / 1.e6)
#endif

#include <cuda_runtime.h>

__global__ void helloworld(void);
void random_ints(int *a, int n);
__global__ void mul(int *a, int *b, int *sub_sum);
void DoVector();


#endif