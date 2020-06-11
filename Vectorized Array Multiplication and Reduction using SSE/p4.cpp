
//Onur Sasmaz
//CS475 - Project4
#include <xmmintrin.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h> //stderr
#include <time.h>
#include <omp.h>

// setting the SSE_WIDTH:
#ifndef SSE_WIDTH
#define SSE_WIDTH		4
#endif


// setting the number of Nodes:
#ifndef ARRAYSIZE
#define ARRAYSIZE	1000000
#endif

// how many tries to discover the maximum performance:
#ifndef NUMTRIES
#define NUMTRIES	10
#endif

//Define Arrays with specified sizes
float A[ARRAYSIZE];
float B[ARRAYSIZE];
float C[ARRAYSIZE];

//Check for OpenMP on the System
int VerifyOpenMP(){
	#ifndef _OPENMP
		fprintf( stderr, "No OpenMP support!\n" );
		return 0;
	#endif
		return 1;
}

//the assignment is just for SimdMulSum( ) - Mike Bailey (piazza)
float
SimdMulSum( float *a, float *b, int len )
{
	float sum[4] = { 0., 0., 0., 0. };
	int limit = ( len/SSE_WIDTH ) * SSE_WIDTH;
	register float *pa = a;
	register float *pb = b;

	__m128 ss = _mm_loadu_ps( &sum[0] );
	for( int i = 0; i < limit; i += SSE_WIDTH )
	{
		ss = _mm_add_ps( ss, _mm_mul_ps( _mm_loadu_ps( pa ), _mm_loadu_ps( pb ) ) );
		pa += SSE_WIDTH;
		pb += SSE_WIDTH;
	}
	_mm_storeu_ps( &sum[0], ss );

	for( int i = limit; i < len; i++ )
	{
		sum[0] += a[i] * b[i];
	}

	return sum[0] + sum[1] + sum[2] + sum[3];
}

float NormalMulSum( float *a, float *b, int len ){
	float sum = 0.;
	for(int i = 0; i<len; i++){
		sum += a[i] * b[i];
	}
	return sum;
}

int main(){
	VerifyOpenMP();
	float maxMultiplicationSIMD = 0., maxMultiplicationNORMAL = 0.;

	for( int t = 0; t < NUMTRIES; t++)
	{
		double time0 = omp_get_wtime( );

		SimdMulSum(A,B, ARRAYSIZE);

		double time1 = omp_get_wtime( );

		NormalMulSum(A,B, ARRAYSIZE);

		double time2 = omp_get_wtime( );



		//Piazza
		//double megaMulsPerSecond = (float)ARRAY_SIZE / (time1 - time0) / 1000000.0;
		double calculation1 = (float)ARRAYSIZE / ( time1 - time0 ) / 1000000.;
		if( calculation1 > maxMultiplicationSIMD ){
			maxMultiplicationSIMD = calculation1;
		}
		double calculation2 = (float)ARRAYSIZE / ( time2 - time1 ) / 1000000.;
		if( calculation2 > maxMultiplicationNORMAL ){
			maxMultiplicationNORMAL = calculation2;
		}


	}
	printf("%8.2d, %8.2lf,%8.2lf, %8.2lf,%8.2lf \n",ARRAYSIZE ,(maxMultiplicationSIMD/maxMultiplicationNORMAL),(maxMultiplicationNORMAL/maxMultiplicationSIMD), maxMultiplicationSIMD, maxMultiplicationNORMAL);
	return 0;
}
