#include "particle.h"
#include <stdlib.h>
#include <stdio.h>
#include "tcu.h"
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/sequence.h>
#include <thrust/transform.h>
#include <thrust/fill.h>
#include <iostream>

//try thrust
void TryThrust(int argc, char **argv)
{
	thrust::device_vector<int> X(10);
	thrust::device_vector<int> Y(10);
	thrust::device_vector<int> Z(10);

	thrust::sequence(X.begin(),X.end());
	thrust::transform(X.begin(),X.end(),Y.begin(),thrust::negate<int>());
	thrust::fill(Z.begin(),Z.end(),2);
	thrust::copy(Y.begin(),Y.end(),std::ostream_iterator<int>(std::cout,"\n"));
}

__global__ void advanceParticles(float dt, particle *pArray, int nParticles)
{
	int idx = threadIdx.x + blockIdx.x * blockDim.x;
	if (idx < nParticles)
	{
		pArray[idx].advance(dt);
	}
}

void DoParticle(int argc, char **argv)
{
	cudaError_t error;
	int n = 1000000;
	if (argc > 1)
	{
		n = atoi(argv[1]);
	} // Number of particles
	if (argc > 2)
	{
		srand(atoi(argv[2]));
	} // Random seed

	error = cudaGetLastError();
	if (error != cudaSuccess)
	{
		printf("0 %s\n", cudaGetErrorString(error));
		exit(1);
	}

	particle *pArray = new particle[n];
	particle *devPArray = NULL;
	cudaMalloc(&devPArray, n * sizeof(particle));
	cudaDeviceSynchronize();
	error = cudaGetLastError();
	if (error != cudaSuccess)
	{
		printf("1 %s\n", cudaGetErrorString(error));
		exit(1);
	}

	cudaMemcpy(devPArray, pArray, n * sizeof(particle), cudaMemcpyHostToDevice);
	cudaDeviceSynchronize();
	error = cudaGetLastError();
	if (error != cudaSuccess)
	{
		printf("2 %s\n", cudaGetErrorString(error));
		exit(1);
	}

	for (int i = 0; i < 100; i++)
	{
		float dt = (float)rand() / (float)RAND_MAX; // Random distance each step
		advanceParticles<<<1 + n / 256, 256>>>(dt, devPArray, n);
		error = cudaGetLastError();
		if (error != cudaSuccess)
		{
			printf("3 %s\n", cudaGetErrorString(error));
			exit(1);
		}

		cudaDeviceSynchronize();
	}
	cudaMemcpy(pArray, devPArray, n * sizeof(particle), cudaMemcpyDeviceToHost);

	v3 totalDistance(0, 0, 0);
	v3 temp;
	for (int i = 0; i < n; i++)
	{
		temp = pArray[i].getTotalDistance();
		totalDistance.x += temp.x;
		totalDistance.y += temp.y;
		totalDistance.z += temp.z;
	}
	float avgX = totalDistance.x / (float)n;
	float avgY = totalDistance.y / (float)n;
	float avgZ = totalDistance.z / (float)n;
	float avgNorm = sqrt(avgX * avgX + avgY * avgY + avgZ * avgZ);
	printf("Moved %d particles 100 steps. Average distance traveled is |(%f, %f, %f)| = %f\n",
		   n, avgX, avgY, avgZ, avgNorm);
}