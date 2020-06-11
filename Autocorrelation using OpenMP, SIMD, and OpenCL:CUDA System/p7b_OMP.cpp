#include <math.h>
#include <stdlib.h>
#include <stdio.h> //stderr
#include <time.h>
#include <omp.h>

// how many tries to discover the maximum performance:
#ifndef NUMTRIES
#define NUMTRIES	10
#endif

#ifndef NUMT
#define NUMT	1
#endif

//Easier to pass/Calcualte etc.

int     Size;
float * A;
float * Sums;
FILE *  fp;
FILE * writeFile;

//Check for OpenMP on the System
int VerifyOpenMP(){
	#ifndef _OPENMP
		fprintf( stderr, "No OpenMP support!\n" );
		return 0;
	#endif
		return 1;
}

void writeResult(){

}

int main(){
  //Check for OpenMP on the system

  VerifyOpenMP();

  int     i;

  omp_set_num_threads(NUMT);

	//Read data from the File
  fp = fopen( "signal.txt", "r" );
  if( fp == NULL )
  {
  	fprintf( stderr, "Cannot open file 'signal.txt'\n" );
  	exit( 1 );
  }
  fscanf( fp, "%d", &Size );
  A =     (float *)malloc( 2 * Size * sizeof(float) );
  Sums  = (float *)malloc( 1 * Size * sizeof(float) );
  for( i = 0; i < Size; i++ )
  {
  	fscanf( fp, "%f", &A[i] );
  	A[i+Size] = A[i];		// duplicate the array
  }
  fclose( fp );

  //OpenMP Code Here we goo...
  double maxPerformance = 0.;
  double sumPerformance = 0.;

  for( int t = 0; t < NUMTRIES; t++)
  {
    double time0 = omp_get_wtime( );
    float total = 0;

    // using an OpenMP for loop and a reduction:
    #pragma omp parallel for default(none), shared(Size, A, Sums)
    for( int shift = 0; shift < Size; shift++ )
    {
    	float sum = 0.;
    	for( int i = 0; i < Size; i++ )
    	{
    		sum += A[i] * A[i + shift];
    	}
    	Sums[shift] = sum;	// note the "fix #2" from false sharing if you are using OpenMP
    }
    double time1 = omp_get_wtime( );

    double megaSizePerSecond = (double)(Size*Size) / ( time1 - time0 ) / 1000000.;
		if(maxPerformance < megaSizePerSecond){
			maxPerformance = megaSizePerSecond;
		}
		sumPerformance += megaSizePerSecond;
  }
	double averagePerformance = sumPerformance/(double)NUMTRIES;

	printf("NUMT %d\n",NUMT);
  printf("Max Performance: %f\n",maxPerformance);
	printf("Average Performance: %f\n",averagePerformance);


  writeFile = fopen("result_OMP.txt", "w" );
  if(!(writeFile)){
    fprintf( stderr, "Cannot open file 'result_OMP.txt'\n" );
  	exit( 1 );
  }

	// Sums[1] ... Sums[512] will be enough to reveal it.
  for(int i=1; i<513; i++){
    fprintf(writeFile, "%f\n", Sums[i]);
  }

  //Close the writeFile
  fclose(writeFile);


	free(A);
	free(Sums);

  //Done with the Program
  return 0;
}
