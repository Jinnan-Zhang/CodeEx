#include "particle.h"
#include <stdlib.h>
#include <stdio.h>

__global__ void advanceParticles(float dt, particle * pArray, int nParticles);

void DoParticle(int , char**);
void TryThrust(int , char**);