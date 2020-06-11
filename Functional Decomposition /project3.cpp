//Onur Sasmaz
//CS475 - Project3
#include <math.h>
#include <stdlib.h>
#include <stdio.h> //stderr
#include <time.h>
#include <omp.h>

//  State Global Variables
// Basic time step will be one month
// Units of grain growth are inches.
// Units of temperature are degrees Fahrenheit (°F).
// Units of precipitation are inches.
int	NowYear;		// 2020 - 2025
int	NowMonth;		// 0 - 11
int CountMonth;
int NowRabbit;


float	NowPrecip;		// inches of rain per month
float	NowTemp;		// temperature this month
float	NowHeight;		// grain height in inches
int	NowNumDeer;		// number of deer in the current population



unsigned int seed = 0;

const float GRAIN_GROWS_PER_MONTH =		  9.0;
const float ONE_DEER_EATS_PER_MONTH =		1.0;

const float AVG_PRECIP_PER_MONTH =		  7.0;	// average
const float AMP_PRECIP_PER_MONTH =	   	6.0;	// plus or minus
const float RANDOM_PRECIP =		         	2.0;	// plus or minus noise

const float AVG_TEMP =				          60.0;	// average
const float AMP_TEMP =				          20.0;	// plus or minus
const float RANDOM_TEMP =			          10.0;	// plus or minus noise

const float MIDTEMP =				            40.0;
const float MIDPRECIP =				          10.0;

void GrainDeer();
void Grain();
void Watcher();
void Rabbit();

//Check for OpenMP on the System
int VerifyOpenMP(){
	#ifndef _OPENMP
		fprintf( stderr, "No OpenMP support!\n" );
		return 0;
	#endif
		return 1;
}

float
Ranf( unsigned int *seedp,  float low, float high )
{
        float r = (float) rand_r( seedp );              // 0 - RAND_MAX
        return(   low  +  r * ( high - low ) / (float)RAND_MAX   );
}


int
Ranf( unsigned int *seedp, int ilow, int ihigh )
{
        float low = (float)ilow;
        float high = (float)ihigh + 0.9999f;

        return (int)(  Ranf(seedp, low,high) );
}

float SQR( float x ){  return x*x; }

int main( int argc, char *argv[ ] )
{
	VerifyOpenMP();

  // starting date and time:
  NowMonth =    0;
  NowYear  = 2020;


  // starting state (feel free to change this if you want):
  NowNumDeer = 1;
  NowHeight =  1.;
	NowRabbit = 1;


  omp_set_num_threads( 4 );	// same as # of sections
  #pragma omp parallel sections
  {
  	#pragma omp section
  	{
  		GrainDeer( );
  	}

  	#pragma omp section
  	{
  		Grain( );
  	}

  	#pragma omp section
  	{
  		Watcher( );
  	}

  	#pragma omp section
  	{
  		Rabbit( );	// your own
  	}
  }       // implied barrier -- all functions must return in order
  	// to allow any of them to get past here
	return 0;
}


// The GrainGrowth and GrainDeer threads will each compute the next grain height and
// the next number of deer based on the current set of global state variables.
// hey will compute these into local, temporary, variables.
// They both then will hit the DoneComputing barrier.

void Grain(){
  while( NowYear < 2026 )
  {
  	// compute a temporary next-value for this quantity
  	// based on the current state of the simulation:
    float tempFactor = exp(   -SQR(  ( NowTemp - MIDTEMP ) / 10.  )   );
    float precipFactor = exp(   -SQR(  ( NowPrecip - MIDPRECIP ) / 10.  )   );

    float nextHeight = NowHeight;
    nextHeight += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
    nextHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;

    //Be sure to clamp nextHeight against zero. (Assign Zero)
    if(nextHeight < 0.){
      nextHeight = 0.;
    }
  	// DoneComputing barrier:
  	#pragma omp barrier
    NowHeight = nextHeight;

  	// DoneAssigning barrier: Wait
  	#pragma omp barrier

  	// DonePrinting barrier: Wait
  	#pragma omp barrier

  }
}

//If the number of graindeer exceeds NowHeight at the end of a month,
// decrease the number of graindeer by one. If the number of graindeer is less
//than this value at the end of a month, increase the number of graindeer by one.
void GrainDeer(){
  while( NowYear < 2026 )
  {
    int NewNumDeer = NowNumDeer;
    //If the number of graindeer exceeds NowHeight at the end of a month,
    // decrease the number of graindeer by one.
    if(NowNumDeer > NowHeight){
      NewNumDeer--;
      //Be sure to Deer number against negative numbers. (Assign Zero)

    }
		if(NewNumDeer < 0){
			NewNumDeer = 0;
		}
    //  If the number of graindeer is less than this value at the end of a month,
    //increase the number of graindeer by one.
   if(NowNumDeer < NowHeight){
     NewNumDeer++;
   }

  	// compute a temporary next-value for this quantity
  	// based on the current state of the simulation:
  	// DoneComputing barrier:
  	#pragma omp barrier
		NowNumDeer = NewNumDeer;

  	// DoneAssigning barrier: Wait
  	#pragma omp barrier

  	// DonePrinting barrier: Wait
  	#pragma omp barrier

  }
}


 // Watcher thread will print the current set of global state variables,
 // increment the month count, and then use the new month to compute
 // the new Temperature and Precipitation.
void Watcher(){
  while( NowYear < 2026 )
  {
  	// compute a temporary next-value for this quantity
  	// based on the current state of the simulation:

  	// DoneComputing barrier:  Wait
  	#pragma omp barrier


  	// DoneAssigning barrier: Wait
  	#pragma omp barrier
    // A table showing values for temperature, precipitation, number of graindeer,
    //  height of the grain, and your own-choice quantity as a function of month number.
		// Print Metric
		//Metric Calculations
		float	NowTempC = (5./9.)*(NowTemp - 32);
		float	NowHeightMetric = NowHeight * 2.54 ;		// grain height in CM
		float	NowPrecipMetric = NowPrecip * 2.54 ;		// CM of rain per month
		// printf("%2d", NowMonth);
		printf("%2d,%2f,%8.2lf,%8d,%8.2lf,%2d\n", CountMonth + 1, NowTempC, NowPrecipMetric, NowNumDeer, NowHeightMetric, NowRabbit);
		if(NowMonth > 11){
			NowYear++;
			NowMonth = 0;
		}
		NowMonth++;
		CountMonth++;
		float ang = (  30.*(float)NowMonth + 15.  ) * ( M_PI / 180. );
	  float temp = AVG_TEMP - AMP_TEMP * cos( ang );
	  NowTemp = temp + Ranf( &seed, -RANDOM_TEMP, RANDOM_TEMP );

	  float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
	  NowPrecip = precip + Ranf( &seed,  -RANDOM_PRECIP, RANDOM_PRECIP );

	  if( NowPrecip < 0. )
	  {
	    NowPrecip = 0.;
	  }
  	// DonePrinting barrier:
  	#pragma omp barrier

  }
}

//Implemented Fucntion Rabbit
//When there are too many Deers, Deers can't find enough grain
//They get so hungry that they consider eating 2 rabbits all together.
// If Deers dont eat the Rabbits, Rabbit number increment.
void Rabbit(){

  while( NowYear < 2026 )
  {
		unsigned int sum;
		srand(time(0));
		//Flip a Coin
		int FlipCoin = Ranf(&sum, 0,10);
		int Rabbit = NowRabbit;
		//If Dear nubmer is bigger than 3, Flip a coin if tails eat 2 rabbit
		if(NowNumDeer > 3 ){
			if(FlipCoin > 5){
				Rabbit -= 5;
			}
		//If Deer number is less, Rabbit number keep increasing
		}else if(NowNumDeer <= 4){
			Rabbit++;
		}
		if(Rabbit < 0){
			Rabbit = 0;
		}
  	// DoneComputing barrier:
  	#pragma omp barrier
		NowRabbit = Rabbit;

  	// DoneAssigning barrier: Wait
  	#pragma omp barrier

  	// DonePrinting barrier: Wait
  	#pragma omp barrier

  }
}
