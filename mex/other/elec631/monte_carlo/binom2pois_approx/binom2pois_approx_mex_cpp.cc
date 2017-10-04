#include "mex.h"
#include "matrix.h"

#include "binom2pois_approx.hh"
#include "pois_pmf.hh"
#include "mex2matlab.hh"

#include <cmath>
#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>

// mexFunction
void mexFunction
(
        int        nlhs ,
        mxArray  * plhs [] ,
        int        nrhs ,
  const mxArray  * prhs []
)
// int
// main
// (void) 
{
  double                     lam; //= 10.0;
  std::vector<unsigned int>  n;
  unsigned int               noMCTests; //= 20000;
  
  std::vector<Binom2PoisResultsContainer> res;
  
  unsigned int cnt_arg;
  
  std::stringstream ssMEXNAME;
  ssMEXNAME << "binom2pois_approx_mex_cpp";
  
/*  
  // fill n
  unsigned int nLength = 11;
  double nMinExp = 1.3 , nMaxExp = 2.3;
  for ( unsigned int ii = 0 ; ii < nLength ; ii++ )
  {
    double tmp 
      = nMinExp + (nMaxExp - nMinExp) / ((double) (nLength-1)) * ((double) ii);
    tmp = exp( tmp * log( 10.0 ) );
    n.push_back( (unsigned int) ceil(tmp) );
  }
*/

  // check inputs
  cnt_arg = 0;
  argcheck_binom2pois_io_input_required
    ( 
      nlhs , 
      plhs , 
      nrhs-cnt_arg , 
      &prhs[cnt_arg] ,
      ssMEXNAME ,
      lam ,
      n ,
      noMCTests
    );

  // compute
  binom2pois_approx
  (
    lam ,
    n ,
    noMCTests ,
    res
  );
  
  plugInPoissonPMFValues
  (
    lam ,
    res
  );

  std::cout << "Now Here!" << std::endl;
/*  
  // report
  std::cout << std::endl << "Report :" << std::endl;
  for ( unsigned int ii = 0 ; ii < res.size() ; ii++ )
  {
    std::cout 
      << std::endl << "index :" 
      << std::endl << "  " << ii << std::endl;
    std::cout 
      << "n :" << std::endl 
      << "  " << res[ii].n << std::endl;
    std::cout 
      << "p :" << std::endl 
      << "  " << res[ii].p << std::endl;
    
    std::cout << std::endl;
    
    for ( unsigned int jj = 0 ; jj < res[ii].myRange.size() ; jj++ )
    {
      printf
      ( 
        "%5d  %.4e  %.4e\n" , 
        res[ii].myRange[jj] ,
        res[ii].pmfBinomial[jj] ,
        res[ii].pmfPoisson[jj]
      );
    }
  } // for
*/  
  // transfer
  cnt_arg = 0;
  binom2pois_mex2matlab
  (
    nlhs-cnt_arg , 
    &plhs[cnt_arg] , 
    nrhs , 
    prhs ,
    res
  );

//   return 0;
}