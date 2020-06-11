
#include <xmmintrin.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h> //stderr
#include <time.h>
#include <omp.h>

#define SSE_WIDTH		4

#ifndef NUMTRIES
#define NUMTRIES 4
#endif

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


int main(){
	VerifyOpenMP();
	int     Size;
	float * A;
	float * Sums;
	FILE  * fp;

	float maxPerformanceSIMD = 0.;
	float avgPerformanceSIMD = 0.;

	fp = fopen( "signal.txt", "r" );
  if( fp == NULL )
  {
  	fprintf( stderr, "Cannot open file 'signal.txt'\n" );
  	exit( 1 );
  }

  fscanf( fp, "%d", &Size );
  A    = (float *)malloc( 2 * Size * sizeof(float) );
  Sums  = (float *)malloc( 1 * Size * sizeof(float) );
  for(int i = 0; i < Size; i++ )
  {
  	fscanf( fp, "%f", &A[i] );
  	A[i+Size] = A[i];		// duplicate the array
  }
  fclose( fp );

	for(int t=0; t < NUMTRIES; t++){
		double time0 = omp_get_wtime( );
	  for( int shift = 0; shift < Size; shift++ )
	  {
	  	float sum = 0.;
	  	Sums[shift] = SimdMulSum( &A[0], &A[0+shift], Size );
	  }
		double time1 = omp_get_wtime( );
		double calculation = (double)(Size * Size) / ( time1 - time0 ) / 1000000.;
		if(maxPerformanceSIMD < calculation){
			maxPerformanceSIMD = calculation;
		}
		avgPerformanceSIMD += calculation;

	}

	avgPerformanceSIMD = (avgPerformanceSIMD/NUMTRIES);
	//Write output to File
	printf("Max Perfomance: %lf\n", maxPerformanceSIMD);
	printf("Avg Perfomance: %lf\n", avgPerformanceSIMD);

	FILE *simdWrite;
  simdWrite = fopen("result_SIMD.txt", "w");
	// Sums[1] ... Sums[512] will be enough to reveal it.
  for(int i=1; i < 513; i++){
    fprintf(simdWrite, "%lf\n", Sums[i]);
  }
	fprintf(simdWrite,"Max Perfomance: %lf\n", maxPerformanceSIMD);
	fprintf(simdWrite,"Avg Perfomance: %lf\n", avgPerformanceSIMD);
  fclose(simdWrite);

  return 0;
}
