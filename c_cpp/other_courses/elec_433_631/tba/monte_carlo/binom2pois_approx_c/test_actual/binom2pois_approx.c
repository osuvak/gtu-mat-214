#include "binom2pois_approx.h"
#include "prng/prng_uniform.h"

#include <stdlib.h>
#include <stdio.h>

// #define USE_OMP

#ifdef USE_OMP
#include <omp.h>
#endif

static
unsigned int
findMinInRange
(
  const unsigned int * arrayPtr ,
  const unsigned int   size
);

static
unsigned int
findMaxInRange
(
  const unsigned int * arrayPtr ,
  const unsigned int   size
);

static
unsigned int
countNumberOfOccurencesInRange
(
  const unsigned int * arrayPtr ,
  const unsigned int   size ,
  const unsigned int   check
);

void
os_sstests_binom2pois_approx
(
  const double          lam ,
  const unsigned int  * n ,
  const unsigned int    nSize ,
  const unsigned int    noMCTests ,
        Binom2PoisResultsContainer
          ** resPtr
)
{
  int threadNo;
  unsigned int ii, jj, kk;
  Binom2PoisResultsContainer *res;
  
  double       *rNumbers , 
               *rNumbersRef;
  unsigned int *sums;
  
  unsigned int *myRange;
//   double       *pmfPoisson;
  double       *pmfBinomial;
  
  // compute p probabilities corresponding to n
  // also construct empty results vector
  double *p = (double *) malloc( nSize * sizeof(double) );
  // free(p); // done below
  
  // allocate space for resPtr
  // the following item will not be freed in here
  *resPtr = 
    (Binom2PoisResultsContainer *)
    malloc( nSize * sizeof(Binom2PoisResultsContainer) );
  
  for ( ii=0 ;  ii < nSize ; ii++ )
  {
    p[ii] = lam / ( (double) n[ii] );
    
    (*resPtr)[ii].n = n[ii];
    (*resPtr)[ii].p = p[ii];
  }
  free(p); // done below
  
  res = *resPtr;

#ifdef USE_OMP
#pragma omp parallel \
  private(threadNo,rNumbers,rNumbersRef,sums,myRange,pmfBinomial) \
  shared(res)
{
  #pragma omp for schedule(static) nowait
#endif
  // perform the actual tests
  for ( kk=0 ;  kk < nSize ; kk++ )
  {
//     #pragma omp critical
//     {
    rNumbers
      = os_prng_getUniformlyDistRV( res[kk].n * noMCTests );
    // free(rNumbers); // done below
      
    // create alias
    rNumbersRef = rNumbers;

    // to compute sums (calloc initializes to zero)
    sums 
      = (unsigned int *) calloc( noMCTests , sizeof(unsigned int) );
    // free(sums); // done below
//     } // #pragma
    
// define macros
#define rNumbersRef(i,j) (rNumbersRef[(i)*noMCTests + (j)])
      
    for ( ii=0 ;  ii < res[kk].n ; ii++ )
      for ( jj=0 ;  jj < noMCTests ; jj++ )
        if ( rNumbersRef(ii,jj) < res[kk].p )
          sums[jj]++;

    // find min max in range
    unsigned int minInRange, maxInRange, sizeRange;
    
    minInRange = findMinInRange( sums , noMCTests );
    maxInRange = findMaxInRange( sums , noMCTests );
    
    sizeRange = maxInRange - minInRange + 1;
    res[kk].size = sizeRange;
    
    myRange 
      = (unsigned int *) calloc( sizeRange , sizeof(unsigned int) );
    pmfBinomial 
      = (double *)       calloc( sizeRange , sizeof(double) );
    // free(myRange);     // done below
    // free(pmfBinomial); // done below

    // fill in range and pmf binomial
    for ( ii=0 ;  ii <= maxInRange-minInRange ; ii++ )
    {
      myRange[ii] = ii + minInRange;
      unsigned int cnt 
        = countNumberOfOccurencesInRange( sums , noMCTests , ii+minInRange );
      pmfBinomial[ii] = ((double) cnt ) / ((double) noMCTests );
    } // for

// undefine macros
#undef rNumbersRef

    os_sstests_Binom2PoisResultsContainer_set_myRange
      ( &(res[kk]) , myRange     , sizeRange );
    os_sstests_Binom2PoisResultsContainer_set_pmfBinomial
      ( &(res[kk]) , pmfBinomial , sizeRange );

//     #pragma omp critical
//     {
      free(rNumbers);    // done below
      free(sums);        // done below
      free(myRange);     // done below
      free(pmfBinomial); // done below
//     } // #pragma

#ifdef USE_OMP
    #pragma omp critical
    {
#endif
      printf( "Test Index :  %d\n" , kk );
#ifdef USE_OMP
    } // #pragma
#endif
  } // for
#ifdef USE_OMP
} // pragma
#endif
}

static
unsigned int
findMinInRange
(
  const unsigned int * arrayPtr ,
  const unsigned int   size
)
{
  unsigned int ii;
  
  unsigned int val = arrayPtr[0];
  for ( ii=1 ; ii < size ; ii++ )
  {
    if ( arrayPtr[ii] < val )
      val = arrayPtr[ii];
  }
  return val;
}

static
unsigned int
findMaxInRange
(
  const unsigned int * arrayPtr ,
  const unsigned int   size
)
{
  unsigned int ii;
  
  unsigned int val = arrayPtr[0];
  for ( ii=1 ; ii < size ; ii++ )
  {
    if ( arrayPtr[ii] > val )
      val = arrayPtr[ii];
  }
  return val;
}

static
unsigned int
countNumberOfOccurencesInRange
(
  const unsigned int * arrayPtr ,
  const unsigned int   size ,
  const unsigned int   check
)
{
  unsigned int ii , cnt = 0;
  
  for ( ii=0 ; ii<size ; ii++ )
  {
    if ( arrayPtr[ii] == check )
      cnt++;
  }
  
  return cnt;
}