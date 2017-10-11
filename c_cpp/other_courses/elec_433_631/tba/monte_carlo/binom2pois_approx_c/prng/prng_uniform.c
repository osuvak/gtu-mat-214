#include "prng_uniform.h" 

#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

/*
 * See the following webpage :
 * http://stackoverflow.com/questions/7343833/srand-why-call-it-only-once
 * */
void
os_prng_initRNG
()
{
  struct timeval t1;
  gettimeofday(&t1, NULL);
  srand(t1.tv_usec * t1.tv_sec);   // should only be called once
}

double *
os_prng_getUniformlyDistRV
(
  const unsigned int   howMany
)
{
  double *numbersPtr = 
    (double *) malloc( howMany * sizeof(double) );
    
  unsigned int ii;
  for( ii=0 ; ii < howMany ; ii++ )
  {
    numbersPtr[ii] = 
      ( ( (double) rand() ) / ( (double) RAND_MAX ) );
  }
    
  return numbersPtr;
}
