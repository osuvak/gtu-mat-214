#include <stdio.h>
#include <stdlib.h>

#include "prng_uniform.h"

int
main
()
{
  const unsigned int howMany = 10;
  unsigned int ii;
  
  os_prng_initRNG();
  
  double *numbersPtr = os_prng_getUniformlyDistRV(howMany);
  
  printf( "\nRandom Numbers :\n\n" );
  for( ii=0 ; ii < howMany ; ii++ )
  {
    printf ( "  %.6e\n" , numbersPtr[ii] );
  }
  
  free(numbersPtr);
  
  return 0;
}
