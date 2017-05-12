
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMT 4
#define NUMPAD 13

// Globals
struct s {
	float value;
	int pad[NUMPAD];
} arr[4];


//Padding fix
void fix1() {
	omp_set_num_threads(NUMT);
	const int SomeBigNumber = 100000000;	// keep < 2B

	double time1, time2;
	time1 = omp_get_wtime();
	
	#pragma omp parallel for
	for (int i = 0; i < 4; i++) {
		unsigned int seed = 0;
		for (unsigned int j = 0; j < SomeBigNumber; j++) {
			arr[i].value = arr[i].value + (float)rand_r(&seed);
		}
	}
	
	time2 = omp_get_wtime();
	
	printf("NUMT: %i | NUMPAD: %i\n", NUMT, NUMPAD);
	fprintf(stderr, "MegaIncr/sec = %10.2lf\n\n", (double)SomeBigNumber/(time2-time1)/1000000.);
}

//Private fix
void fix2() {
	omp_set_num_threads(NUMT);
	const int SomeBigNumber = 100000000;	// keep < 2B

	double time1, time2;
	time1 = omp_get_wtime();
	
	#pragma omp parallel for
	for (int i = 0; i < 4; i++) {
		unsigned int seed = 0;
		float temp = arr[i].value;
		for (unsigned int j = 0; j < SomeBigNumber; j++) {
			temp = temp + (float)rand_r(&seed);
		}
		arr[i].value = temp;
	}
	
	time2 = omp_get_wtime();
	
	printf("NUMT: %i | NUMPAD: %i\n", NUMT, NUMPAD);
	fprintf(stderr, "MegaIncr/sec = %10.2lf\n\n", (double)SomeBigNumber/(time2-time1)/1000000.);
}

int main( int argc, char *argv[] )
{
	fix1();
	//fix2();
}


