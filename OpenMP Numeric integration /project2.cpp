#include <math.h>
#include <stdlib.h>
#include <stdio.h> //stderr
#include <time.h>
#include <omp.h>

// setting the number of threads:
#ifndef NUMT
#define NUMT		1
#endif

// setting the N:
#ifndef N
#define N		4
#endif

// setting the number of Nodes:
#ifndef NUMNODES
#define NUMNODES	10
#endif

// how many tries to discover the maximum performance:
#ifndef NUMTRIES
#define NUMTRIES	10
#endif

#define XMIN     -1.
#define XMAX      1.
#define YMIN     -1.
#define YMAX      1.

float Height( int iu, int iv )	// iu,iv = 0 .. NUMNODES-1
{
	float x = -1.  +  2.*(float)iu /(float)(NUMNODES-1);	// -1. to +1.
	float y = -1.  +  2.*(float)iv /(float)(NUMNODES-1);	// -1. to +1.

	float xn = pow( fabs(x), (double)N );
	float yn = pow( fabs(y), (double)N );
	float r = 1. - xn - yn;
	if( r < 0. )
	        return 0.;
	float height = pow( 1. - xn - yn, 1./(float)N );
	return height;
}

//Check for OpenMP on the System
int VerifyOpenMP(){
	#ifndef _OPENMP
		fprintf( stderr, "No OpenMP support!\n" );
		return 0;
	#endif
		return 1;
}

int main( int argc, char *argv[ ] )
{
	VerifyOpenMP();

	float maxHeight = 0, volume = 0;
	omp_set_num_threads( NUMT );	// set the number of threads to use in the for-loop:`

	// the area of a single full-sized tile:
	float fullTileArea = (  ( ( XMAX - XMIN )/(float)(NUMNODES-1) )  *
	( ( YMAX - YMIN )/(float)(NUMNODES-1) )  );
	 // printf("%8.2lf", fullTileArea);
	for( int t = 0; t < NUMTRIES; t++)
	{
		double time0 = omp_get_wtime( );
		float total = 0;

		// using an OpenMP for loop and a reduction:
		#pragma omp parallel for default(none), shared(fullTileArea), reduction(+:total)
		for( int i = 0; i < NUMNODES*NUMNODES; i++ )
		{
			// iu Number of places over to right
			// iv Number of places over to up
			float base;
			int iu = i % NUMNODES;
			int iv = i / NUMNODES;

			// multiply the -Height area you get by 2.
			// add the Edges height goes 0.
			float z = (Height( iu, iv ) * 2 );
			// We are at the corner
			if((iu == 0 || iu == NUMNODES - 1) && (iv == 0 || iv == NUMNODES - 1)){
				//Tiles in the corners are quarter-sized.
				base = (fullTileArea/4);
			}//We are at the edge
			else if ((iu == 0 || iu == NUMNODES - 1) || (iv == 0 || iv == NUMNODES - 1)){
				//Tiles along the edges are half-sized.
				base = (fullTileArea/2);
			}else{
				//The tiles in the middle of the floor are full-sized tiles
				base = fullTileArea;
			}
			total += (z * base);


		}

		//MegaHeights Computed Per Second
		double time1 = omp_get_wtime( );
		double megaHeightsPerSecond = (double)NUMNODES*NUMNODES / ( time1 - time0 ) / 1000000.;
		if( megaHeightsPerSecond > maxHeight ){
			maxHeight = megaHeightsPerSecond;
			// sum up the weighted heights into the variable "volume"
			volume = total;
		}
	}
	//Print the outcome
	printf("%d, %d, %8.2lf, %8.2lf\n", NUMT, NUMNODES, volume, maxHeight);
	return 0;
}
