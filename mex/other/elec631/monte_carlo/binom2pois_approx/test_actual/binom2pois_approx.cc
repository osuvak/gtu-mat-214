#include "binom2pois_approx.hh"
#include "prng/prng_uniform.hh"

#include <memory>
#include <algorithm>
#include <iostream>

#include <omp.h>

// #define USE_EXTRA_ALLOCATION

void
binom2pois_approx
(
  const double                       lam ,
  const std::vector<unsigned int>  & n ,
  const unsigned int                 noMCTests ,
        std::vector<Binom2PoisResultsContainer> 
          & res
)
{
  int threadNo;
  
  // compute p probabilities corresponding to n
  // also construct empty results vector
  std::vector<double> 
    p( n.size() , 0 );
  
  for ( unsigned int ii=0 ;  ii < p.size() ; ii++ )
  {
    p[ii] = lam / ( (double) n[ii] );
    res.emplace_back();
    ( *( res.rbegin() ) ).n = n[ii];
    ( *( res.rbegin() ) ).p = p[ii];
  }
/*
  std::cout 
    << "Size of n :" << std::endl 
    << "  " << n.size() << std::endl;
  std::cout 
    << "Size of p :"    << std::endl 
    << "  " << p.size()    << std::endl;
  std::cout 
    << "Size of res :"    << std::endl 
    << "  " << res.size()    << std::endl;
*/

#pragma omp parallel private(threadNo)
{
  #pragma omp for schedule(static) nowait
  // perform the actual tests
  for ( unsigned int kk=0 ;  kk < res.size() ; kk++ )
  {
    using namespace os_prng_tests::in_progress;
    
    std::shared_ptr< std::vector<double> >
      rNumbers( PRNG_Uniform::getNumbers( res[kk].n * noMCTests ) );
#ifdef USE_EXTRA_ALLOCATION
    std::vector<unsigned int>
      bSamples( res[kk].n * noMCTests , 0 );
#endif
      
    // create alias
    std::vector<double> &rNumbersRef = *rNumbers;
/*    
    std::cout 
      << "Size of rNumbersRef :" << std::endl 
      << "  " << rNumbersRef.size() << std::endl;
    std::cout 
      << "Size of bSamples :"    << std::endl 
      << "  " << bSamples.size()    << std::endl;
*/    

    // to compute sums
    std::vector<unsigned int>
      sums( noMCTests , 0 );

    // define macros
#define rNumbersRef(i,j) (rNumbersRef[(i)*noMCTests + (j)])
#ifdef USE_EXTRA_ALLOCATION
#define bSamples(i,j) (bSamples[(i)*noMCTests + (j)])
#endif
      
#ifdef USE_EXTRA_ALLOCATION
    for ( unsigned int ii=0 ;  ii < res[kk].n ; ii++ )
    {
      for ( unsigned int jj=0 ;  jj < noMCTests ; jj++ )
      {
        if ( rNumbersRef(ii,jj) < res[kk].p )
          bSamples(ii,jj) = 1;
//         else
//           bSamples(ii,jj) = 0;
      }
    }
    
    for ( unsigned int jj=0 ;  jj < noMCTests ; jj++ )
    {
      sums[jj] = 0;
      for ( unsigned int ii=0 ;  ii < res[kk].n ; ii++ )
      {
        sums[jj] += bSamples(ii,jj);
      }
    }
#else
    for ( unsigned int ii=0 ;  ii < res[kk].n ; ii++ )
      for ( unsigned int jj=0 ;  jj < noMCTests ; jj++ )
        if ( rNumbersRef(ii,jj) < res[kk].p )
          sums[jj]++;
#endif
      
    // find min max in range
    unsigned int minInRange, maxInRange;
    
    minInRange = *std::min_element( sums.begin() , sums.end() );
    maxInRange = *std::max_element( sums.begin() , sums.end() );
    
    // fill in range and pmf binomial
    for ( unsigned int ii=minInRange ;  ii <= maxInRange ; ii++ )
    {
      res[kk].myRange.push_back( ii );
      
      // find and count all occurences of ii in ensemble
      auto it = sums.begin();
      unsigned int cnt = 0;
      
      while ( it != sums.end() )
      {
        it = std::find_if
          ( 
            it , 
            sums.end() ,  
            [&] (unsigned int number) { return (number == ii); }
          );
        
        if ( it != sums.end() )
        {
          cnt++;
        }
        else
        {
          break;
        }
        
        it++;
      } // while
      
      res[kk].pmfBinomial.push_back( ((double) cnt ) / ((double) noMCTests ) );
    } // for
    
    // undefine macros
#undef rNumbersRef
#ifdef USE_EXTRA_ALLOCATION
#undef bSamples
#endif

    #pragma omp critical
    {
      std::cout << "Test Index :" << "  " << kk << std::endl;
    }

  } // for
} // pragma
}

