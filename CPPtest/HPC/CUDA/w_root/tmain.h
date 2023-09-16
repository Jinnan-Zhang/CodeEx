#ifndef tmain_h
#define tmain_h
#include <cuda_runtime.h>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cublas_v2.h>
#include "cublas_utils.h"
#include "time_macro.h"
// return alpha*A*B+beta*C: a m x k matrix
//* @param alpha: The prodcution coefficient
//* @param A: input matrix 1-d as array, true shape m x n
//* @param B: input matrix as 1-d array, true shape n x k
//* @param C: output matrix as 1-d array, true shape m x k
template <typename T>
std::vector<T> &GetMatProdcut(const std::vector<T> A, const int m, const int n, const int k, const std::vector<T> B, std::vector<T> &C, const T alpha = 1.0, const T beta = 0.0)
{
    cublasHandle_t cublasH = NULL;
    cudaStream_t stream = NULL;

    // leading dimension of two-dimensional array used to store the matrix A.
    const int lda = m;
    // leading dimension of two-dimensional array used to store the matrix B.
    const int ldb = n;
    // leading dimension of two-dimensional array used to store the matrix C.
    const int ldc = m;

    // devicce data
    T *d_A = nullptr;
    T *d_B = nullptr;
    T *d_C = nullptr;

    // transpose or not
    cublasOperation_t transa = CUBLAS_OP_N;
    cublasOperation_t transb = CUBLAS_OP_N;

    // printf("A\n");
    // print_matrix(m, k, A.data(), lda);
    // printf("=====\n");

    // printf("B\n");
    // print_matrix(k, n, B.data(), ldb);
    // printf("=====\n");

    /* step 1: create cublas handle, bind a stream */
    CUBLAS_CHECK(cublasCreate(&cublasH));

    CUDA_CHECK(cudaStreamCreateWithFlags(&stream, cudaStreamNonBlocking));
    CUBLAS_CHECK(cublasSetStream(cublasH, stream));

    /* step 2: copy data to device */
    CUDA_CHECK(cudaMalloc(reinterpret_cast<void **>(&d_A), sizeof(T) * A.size()));
    CUDA_CHECK(cudaMalloc(reinterpret_cast<void **>(&d_B), sizeof(T) * B.size()));
    CUDA_CHECK(cudaMalloc(reinterpret_cast<void **>(&d_C), sizeof(T) * C.size()));

    CUDA_CHECK(cudaMemcpyAsync(d_A, A.data(), sizeof(T) * A.size(), cudaMemcpyHostToDevice,
                               stream));
    CUDA_CHECK(cudaMemcpyAsync(d_B, B.data(), sizeof(T) * B.size(), cudaMemcpyHostToDevice,
                               stream));

    /* step 3: compute */
    CUBLAS_CHECK(
        cublasDgemm(cublasH, transa, transb, m, n, k, &alpha, d_A, lda, d_B, ldb, &beta, d_C, ldc));


    /* step 4: copy data to host */
    CUDA_CHECK(cudaMemcpyAsync(C.data(), d_C, sizeof(T) * C.size(), cudaMemcpyDeviceToHost,
                               stream));

    CUDA_CHECK(cudaStreamSynchronize(stream));

    // printf("C\n");
    // print_matrix(m, n, C.data(), ldc);
    // printf("=====\n");

    /* free resources */
    CUDA_CHECK(cudaFree(d_A));
    CUDA_CHECK(cudaFree(d_B));
    CUDA_CHECK(cudaFree(d_C));

    CUBLAS_CHECK(cublasDestroy(cublasH));

    CUDA_CHECK(cudaStreamDestroy(stream));

    CUDA_CHECK(cudaDeviceReset());

    return C;
}

#endif