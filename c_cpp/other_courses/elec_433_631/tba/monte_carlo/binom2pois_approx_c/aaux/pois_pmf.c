#include "pois_pmf.h" 

#include <math.h>

// #define USE_MATLAB_API
#define USE_GSL_LIB

#ifdef USE_MATLAB_API

#include "mex.h"
#include "matrix.h"

#elif defined USE_GSL_LIB

#include <gsl/gsl_randist.h>

#endif

void
plugInPoissonPMFValues
(
  const double        lam ,
  const unsigned int  nSize ,
        Binom2PoisResultsContainer
          ** resPtr
)
{
  Binom2PoisResultsContainer *res = *resPtr;
  unsigned int ii;
  
  for ( ii = 0 ; ii < nSize ; ii++ )
  {
#ifdef USE_MATLAB_API
    
    std::vector<double> myRange( res[ii].myRange.begin() , res[ii].myRange.end() );
    
    mxArray *mx_in[2], *mx_out[1];
    mx_in[0] = mxCreateDoubleMatrix( 1 , res[ii].myRange.size() , mxREAL );
    std::copy( myRange.begin() , myRange.end() , (double *) mxGetPr( mx_in[0] ) );
    mx_in[1] = mxCreateDoubleScalar( lam );
    
    mexCallMATLAB(1,mx_out,2,mx_in,"poisspdf");
    
    std::vector<double> 
      tmp
        (
          (double *) ( mxGetPr( mx_out[0] ) ) ,
          ( (double *) mxGetPr( mx_out[0] ) ) + mxGetNumberOfElements( mx_out[0] )
        );
    res[ii].pmfPoisson = tmp;
/*
    std::cout 
      << "Index :" << std::endl
      << "  " << ii << std::endl;
    std::cout 
      << "Size of myRange in res :" << std::endl
      << "  " << res[ii].myRange.size() << std::endl;
    std::cout 
      << "Size of myRange :" << std::endl
      << "  " << myRange.size() << std::endl;
    std::cout 
      << "Size of mx_in[0] :" << std::endl
      << "  " << mxGetNumberOfElements( mx_in[0] ) << std::endl;
    std::cout 
      << "Size of mx_in[1] :" << std::endl
      << "  " << mxGetNumberOfElements( mx_in[1] ) << std::endl;
    std::cout 
      << "Size of mx_out[0] :" << std::endl
      << "  " << mxGetNumberOfElements( mx_out[0] ) << std::endl;
    std::cout 
      << "Size of tmp :" << std::endl
      << "  " << tmp.size() << std::endl;
    std::cout 
      << "Size of pmfPoisson in res :" << std::endl
      << "  " << res[ii].pmfPoisson.size() << std::endl;
*/
    mxDestroyArray( mx_in[0] );
    mxDestroyArray( mx_in[1] );
    mxDestroyArray( mx_out[0] );
    
#elif defined USE_GSL_LIB
    
    double *tmp = (double *) calloc( res[ii].size , sizeof(double) );
    unsigned int jj;
    
    for ( jj = 0 ; jj < res[ii].size ; jj++ )
    {
      tmp[jj] = gsl_ran_poisson_pdf( res[ii].myRange[jj] , lam );
    }
    
    os_sstests_Binom2PoisResultsContainer_set_pmfPoisson
      ( &(res[ii]) , tmp , res[ii].size );
    free(tmp);
#endif

  } // for
}

#ifdef USE_MATLAB_API
#undef USE_MATLAB_API
#endif

#ifdef USE_GSL_LIB
#undef USE_GSL_LIB
#endif
