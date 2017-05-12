
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ARR_SIZE		32*1024
#define NUMT			16

//#define SCHEDULER		static
#define SCHEDULER		dynamic

//#define CHUNK_SIZE		1
#define CHUNK_SIZE	4096


float arr[ARR_SIZE];

float Ranf( float low, float high )
{
	float r = (float) rand();		// 0 - RAND_MAX
	return(   low  +  r * ( high - low ) / (float)RAND_MAX   );
}

int main(){
	omp_set_num_threads(NUMT);

    for (int i = 0; i < ARR_SIZE - 1; i++) {
        arr[i] = Ranf(-1.f, 1.f);
    }

	float total;
	
	double time1, time2;
	time1 = omp_get_wtime();
	
	#pragma omp parallel for schedule(SCHEDULER,CHUNK_SIZE),private(total)
	for (int i = 0; i < ARR_SIZE-1; i++) {
		total = 1;
		for (int j = 0; j < i; j++) {
			total *= arr[j];
		}
	}
	
	time2 = omp_get_wtime();

	
	fprintf(stderr, "NUMT = %d\n%f\n", NUMT, (double)(ARR_SIZE*(ARR_SIZE+1)/2)/(time2-time1)/1000000.);
}

