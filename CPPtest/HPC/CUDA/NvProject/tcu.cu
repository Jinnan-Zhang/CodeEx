#include "particle.h"
#include <stdlib.h>
#include <stdio.h>

__global__ void advanceParticles(float dt, particle * pArray, int nParticles)
{
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	if(idx < nParticles)
	{
		pArray[idx].advance(dt);
	}
}