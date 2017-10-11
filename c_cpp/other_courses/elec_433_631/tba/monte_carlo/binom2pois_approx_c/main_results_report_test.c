#include "prng_uniform.h"
#include "binom2pois_approx.h"
#include "pois_pmf.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int
main
(void) 
{
  os_prng_initRNG();
  
  // parameters
  double         lam = 10.0;
  unsigned int * n;
  unsigned int   noMCTests = 50000;
  
  Binom2PoisResultsContainer * res;
  Binom2PoisResultsContainer **resPtr = &res;
  
  // utility
  unsigned int ii, jj, kk;
  
  // fill n
  unsigned int nLength = 11;
  double nMinExp = 1.3 , nMaxExp = 2.3;
  
  n = 
    (unsigned int *) 
    malloc( nLength * sizeof(unsigned int) );
  for ( ii = 0 ; ii < nLength ; ii++ )
  {
    double tmp 
      = nMinExp + (nMaxExp - nMinExp) / ((double) (nLength-1)) * ((double) ii);
    tmp = exp( tmp * log( 10.0 ) );
    n[ii] = (unsigned int) ceil(tmp);
  }

  // compute
  os_sstests_binom2pois_approx
  (
      lam ,
      n ,
      nLength ,
      noMCTests ,
      resPtr
  );

  plugInPoissonPMFValues
  (
    lam ,
    nLength ,
    resPtr
  );
  printf( "Now Here!\n" );
  
  // report
  printf( "\nReport :\n" );
  
  for ( ii = 0 ; ii < nLength ; ii++ )
  {
    printf( "\nindex :\n  %d\n" , ii );
    printf( "n :\n  %d\n"     , res[ii].n );
    printf( "p :\n  %.6e\n"   , res[ii].p );
    
    printf( "\n" );

    printf( "Index  Binomial PMF  Poisson PMF\n" );
    printf( "--------------------------------\n" );
    for ( jj = 0 ; jj < res[ii].size ; jj++ )
    {
      printf
      ( 
        "%5d  %12.4e  %11.4e\n" , 
        res[ii].myRange[jj] ,
        res[ii].pmfBinomial[jj] ,
        ( (res[ii].flag_set_pmfPoisson == false) ? 0.0 : res[ii].pmfPoisson[jj] )
      );
    }

  } // for
  
  // free memory
  free(n);
  os_sstests_Binom2PoisResultsContainer_destroyArray
    ( res , nLength );
  free(res);
  
  printf( "Now Here!\n" );

  return 0;
} 
