#include <stdio.h>
#include <cuda_runtime.h>

__global__ void helloworld(void)
{
    printf("Hello World!\n");
}

int main(void)
{
    helloworld<<<1,1>>>();
    cudaDeviceReset();
    return 0;
}