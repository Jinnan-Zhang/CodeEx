/*
* @compile: nvcc -o HelloWorld.cu.o HelloWorld.cu
*/
#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include <cuda.h>
#include <curand.h>
#include <HelloWorld.h>
#define N (2048 * 2048)
#define THREAD_PER_BLOCK 512
#define BLOCKS_NUM (N / THREAD_PER_BLOCK)



__global__ void helloworld(void)
{
    printf("Hello World!\n");
}
void random_ints(int *a, int n)
{
    for (int i = 0; i < n; i++)
        *(a + i) = rand() % 10;
}
__global__ void mul(int *a, int *b, int *sub_sum)
{
    __shared__ int c[THREAD_PER_BLOCK];
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    c[threadIdx.x] = a[index] * b[index];
    __syncthreads();
    for (int i = THREAD_PER_BLOCK / 2; i > 0; i = i / 2)
    {
        if (threadIdx.x < i)
        {
            c[threadIdx.x] += (c[threadIdx.x + i]);
        }
        __syncthreads();
    }
    if (threadIdx.x == 0)
        sub_sum[blockIdx.x] = c[threadIdx.x];
}

void DoVector()
{
    int *a, *b, *sub_sum, sum;  //host copies
    int *d_a, *d_b, *d_sub_sum; //device copies
    int size = N * sizeof(int);

    cudaMalloc((void **)&d_a, size);
    cudaMalloc((void **)&d_b, size);
    cudaMalloc((void **)&d_sub_sum, sizeof(int) * BLOCKS_NUM);

    a = (int *)malloc(size);
    random_ints(a, N);
    b = (int *)malloc(size);
    random_ints(b, N);
    sub_sum = (int *)malloc(sizeof(int) * BLOCKS_NUM);
    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);
    StartTimeChrono(1);
    mul<<<BLOCKS_NUM, THREAD_PER_BLOCK>>>(d_a, d_b, d_sub_sum);

    StopTimeChrono(1);
    cudaMemcpy(sub_sum, d_sub_sum, sizeof(int) * BLOCKS_NUM, cudaMemcpyDeviceToHost);
    sum = 0;
    for (int i = 0; i < BLOCKS_NUM; i++)
        sum += sub_sum[i];
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
    free(a), free(b), free(sub_sum);
    cudaFree(d_a), cudaFree(d_b), cudaFree(d_sub_sum);
    cudaDeviceReset();
}

int main(void)
{
    // helloworld<<<1,32>>>();
    // cudaDeviceReset();
    DoVector();

    return 0;
}