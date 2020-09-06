/*
* @compile: nvcc -o HelloWorld.cu.o HelloWorld.cu
*/
#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include <cuda.h>
#include <curand.h>
#define N 48

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

__global__ void helloworld(void)
{
    printf("Hello World!\n");
}
void random_ints(int *a, int n)
{
    for (int i = 0; i < n; i++)
        *(a + i) = rand() % 10;
}
__global__ void mul(int *a, int *b, int *sum)
{
    __shared__ int c[N];
    c[threadIdx.x] = a[threadIdx.x] * b[threadIdx.x];
    __syncthreads();
    for (int i = N / 2; i > 0; i = i / 2)
    {
        if (threadIdx.x < i)
        {
            c[threadIdx.x] += (c[threadIdx.x + i]);
        }
        __syncthreads();
    }
    if (threadIdx.x == 0)
        *sum = c[threadIdx.x];
}

void DoVector()
{
    int *a, *b, sum;        //host copies
    int *d_a, *d_b, *d_sum; //device copies
    int size = N * sizeof(int);

    cudaMalloc((void **)&d_a, size);
    cudaMalloc((void **)&d_b, size);
    cudaMalloc((void **)&d_sum, sizeof(int));

    a = (int *)malloc(size);
    random_ints(a, N);
    b = (int *)malloc(size);
    random_ints(b, N);
    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);
    StartTimeChrono(1);
    mul<<<1, N>>>(d_a, d_b, d_sum);

    StopTimeChrono(1);
    cudaMemcpy(&sum, d_sum, sizeof(int), cudaMemcpyDeviceToHost);
    StartTimeChrono(2);
    int sum_cpu = 0;
    for (int i = 0; i < N; i++)
    {
        // printf("%d\t%d\n", a[i], b[i]);
        sum_cpu += (a[i] * b[i]);
    }
    StopTimeChrono(2);
    printf(" GPU result:%d\t CPU result:%d\n", sum, sum_cpu);
    PrintTimeChrono(1, "GPU");
    PrintTimeChrono(2, "CPU");
    free(a), free(b);
    cudaFree(d_a), cudaFree(d_b), cudaFree(d_sum);
    cudaDeviceReset();

}

int main(void)
{
    // helloworld<<<1,32>>>();
    // cudaDeviceReset();
    DoVector();

    return 0;
}