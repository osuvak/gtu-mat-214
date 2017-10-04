#include "mex2matlab.hh" 

#include <algorithm>

void
argcheck_binom2pois_io_input_required
(
        int            nlhs ,
        mxArray      * plhs[] ,
        int            nrhs ,
  const mxArray      * prhs[] ,
  const std::stringstream         & ssMEXNAME ,
        double                    & lam ,
        std::vector<unsigned int> & n,
        unsigned int              & noMCTests
)
{
  // numbers of inputs
  int noRequiredInputs  = 3;
  
  // pointers for inputs
  double *
    ptr_lam;
//   double *
//     ptr_n;
  double *
    ptr_noMCTests;
  
  // check inputs
  if ( nrhs < noRequiredInputs )
  {
    std::stringstream ssID;
    std::stringstream ssMSG;
    
    ssID  << "MATLAB:" << ssMEXNAME.str().c_str() << ":nargin";
    ssMSG << ssMEXNAME.str().c_str() << " needs at least " << noRequiredInputs << " inputs.";
    mexErrMsgIdAndTxt
      (
        ssID.str().c_str() ,
        ssMSG.str().c_str()
      );
  }
  
  // obtain inputs
  int indexCurrent = 0;
  
  ptr_lam
    = (double *) mxGetPr(prhs[indexCurrent]);
  indexCurrent++; 
  unsigned int index_n = indexCurrent;
//   ptr_n
//     = (double *) mxGetPr(prhs[indexCurrent]);
  indexCurrent++;  
  ptr_noMCTests
    = (double *) mxGetPr(prhs[indexCurrent]);
  
  lam 
    = static_cast
    <double>
    (*ptr_lam);
  noMCTests 
    = static_cast
    <unsigned int>
    (*ptr_noMCTests);
  
  n.clear();
/*  
  for ( unsigned int ii = 0 ; ii < mxGetNumberOfElements( prhs[index_n] ) ; ii++ )
  {
    n.push_back( (unsigned int) *( ptr_n + ii ) );
  }
*/
  std::vector<unsigned int> 
    n_tmp
      (
        (double *) ( mxGetPr( prhs[index_n] ) ) ,
        ( (double *) mxGetPr( prhs[index_n] ) ) + mxGetNumberOfElements( prhs[index_n] )
      );
  n = n_tmp;

  if ( lam < 0.0 )
  {
    std::stringstream ssID;
    ssID  << "MATLAB:" << ssMEXNAME.str().c_str() << ":inputChecks";
    
    mexErrMsgIdAndTxt
      (
        ssID.str().c_str() ,
        "lam cannot be < 0.0."
      );
  }
  
  if ( noMCTests < 0 )
  {
    std::stringstream ssID;
    ssID  << "MATLAB:" << ssMEXNAME.str().c_str() << ":inputChecks";
    
    mexErrMsgIdAndTxt
      (
        ssID.str().c_str() ,
        "noMCTests cannot be < 0."
      );
  }
}

void
binom2pois_mex2matlab
(
        int            nlhs ,
        mxArray      * plhs[] ,
        int            nrhs ,
  const mxArray      * prhs[] ,
  const std::vector<Binom2PoisResultsContainer>
    & res
)
{
  // obtain output
  if ( res.size() <= 0 )
  {
    plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
  }
  else
  {
    unsigned int noDims   = 2;
    unsigned int noFields = 5;
    
//     unsigned int cntInternal;
    
    const char *field_names[] 
      = 
      { 
        "n" ,
        "p" ,
        "myRange" , 
        "pmfPoisson" ,
        "pmfBinomial"
      };
    mwSize dims[] = { 1 , res.size() };
    
    int      field_n ,  field_p ;
    mxArray *value_n , *value_p ;
    
    int      field_myRange ,  field_pmfPoisson ,  field_pmfBinomial ;
    mxArray *value_myRange , *value_pmfPoisson , *value_pmfBinomial ;
    
    plhs[0] = mxCreateStructArray(noDims, dims, noFields, field_names);
  
    field_n           = mxGetFieldNumber( plhs[0] , "n" );
    field_p           = mxGetFieldNumber( plhs[0] , "p" );
    field_myRange     = mxGetFieldNumber( plhs[0] , "myRange" );
    field_pmfPoisson  = mxGetFieldNumber( plhs[0] , "pmfPoisson" );
    field_pmfBinomial = mxGetFieldNumber( plhs[0] , "pmfBinomial" );
    
    for ( unsigned int cnt = 0 ; cnt < res.size() ; cnt++ )
    {
      value_n
        = mxCreateDoubleScalar( res[cnt].n );
      value_p
        = mxCreateDoubleScalar( res[cnt].p );
      
      value_myRange 
        = mxCreateDoubleMatrix( 1 , res[cnt].myRange.size()     , mxREAL );
      value_pmfPoisson 
        = mxCreateDoubleMatrix( 1 , res[cnt].pmfPoisson.size()  , mxREAL );
      value_pmfBinomial 
        = mxCreateDoubleMatrix( 1 , res[cnt].pmfBinomial.size() , mxREAL );
/*      
      cntInternal = 0;
      for 
        ( 
          auto it = res[cnt].myRange.begin() ; 
          it != res[cnt].myRange.end() ; 
          ++it 
        )
      {
        *( ( (double *) mxGetPr(value_myRange) ) + cntInternal ) = (*it);
        cntInternal++;
      }
*/
      std::vector<double> 
        myRange
          ( 
            res[cnt].myRange.begin() , 
            res[cnt].myRange.end() 
          );
      std::copy
        (  
          myRange.begin() ,
          myRange.end() ,
          (double *) mxGetPr(value_myRange)
        );
          
/*      
      cntInternal = 0;
      for 
        ( 
          auto it = res[cnt].pmfPoisson.begin() ; 
          it != res[cnt].pmfPoisson.end() ; 
          ++it 
        )
      {
        *( ( (double *) mxGetPr(value_pmfPoisson) ) + cntInternal ) = (*it);
        cntInternal++;
      }
*/
      std::copy
        (  
          res[cnt].pmfPoisson.begin() ,
          res[cnt].pmfPoisson.end() ,
          (double *) mxGetPr(value_pmfPoisson)
        );

/*
      cntInternal = 0;
      for 
        ( 
          auto it = res[cnt].pmfBinomial.begin() ; 
          it != res[cnt].pmfBinomial.end() ; 
          ++it 
        )
      {
        *( ( (double *) mxGetPr(value_pmfBinomial) ) + cntInternal ) = (*it);
        cntInternal++;
      }
*/
      std::copy
        (  
          res[cnt].pmfBinomial.begin() ,
          res[cnt].pmfBinomial.end() ,
          (double *) mxGetPr(value_pmfBinomial)
        );

      mxSetFieldByNumber( plhs[0] , cnt , field_n           , value_n );
      mxSetFieldByNumber( plhs[0] , cnt , field_p           , value_p );
      mxSetFieldByNumber( plhs[0] , cnt , field_myRange     , value_myRange );
      mxSetFieldByNumber( plhs[0] , cnt , field_pmfPoisson  , value_pmfPoisson );
      mxSetFieldByNumber( plhs[0] , cnt , field_pmfBinomial , value_pmfBinomial );
    } // for
    
  } // else
}