#include<iostream>
#include<cstdio>

#include "diode_circuit_exp.hh"
#include "diode_circuit_log.hh"

#include "bisection_internals.hh"
#include "bisection.hh"

#include "callback_diode.hh"

#include "mex.h"
#include "matrix.h"

int
argcheck_DoubleScalar
(
        int       nlhs ,
        mxArray * plhs[] ,
        int       nrhs ,
  const mxArray * prhs[]
);

// mexFunction
void mexFunction
(
        int       nlhs ,
        mxArray * plhs[] ,
        int       nrhs ,
  const mxArray * prhs[]
)
{
  // this mex interface is an illustration for the diode circuit (with log) only
  
  using namespace userdefn;
  using namespace nummethods;
  
  // variables for the diode circuit
  double R   = 1e3;
  double IS  = 3e-15;
  double VIN = 3.3;
  double VT  = 25e-3;
  
  // polymorphic pointers declared and initialized
  DiodeCircuit *d_log = 
    new DiodeCircuitWithLog( R , IS , VIN , VT );
    
  int flag_argcheck;
  int cnt_arg;
  unsigned int cnt;
  
           double limLeft , limRight , abstol , reltol , ftol;
  unsigned int    maxIter;
  
  // check the inputs for the rest of the initialization
  if ( nrhs < 2 )
  {
    mexErrMsgTxt("Expects at least 2 input arguments as left and right limit of the initial interval.");
  }
  else
  {
    cnt_arg = 0;
    if ( 0 != argcheck_DoubleScalar( nlhs , plhs , nrhs-cnt_arg , &prhs[cnt_arg] ) )
      mexErrMsgTxt("1st input (left limit) should be a double scalar.");
    else
      limLeft  = mxGetScalar( prhs[cnt_arg] );
    
    cnt_arg = 1;
    if ( 0 != argcheck_DoubleScalar( nlhs , plhs , nrhs-cnt_arg , &prhs[cnt_arg] ) )
      mexErrMsgTxt("2nd input (right limit) should be a double scalar.");
    else
      limRight = mxGetScalar( prhs[cnt_arg] );
  }
  
  // now check the optional inputs
  cnt_arg = 2;
  flag_argcheck = argcheck_DoubleScalar( nlhs , plhs , nrhs-cnt_arg , &prhs[cnt_arg] );
  if ( -1 == flag_argcheck )
  {}
  else
  {
    if ( 0 != flag_argcheck )
      mexErrMsgTxt("3rd input (abstol) should be a double scalar.");
    else
      abstol = mxGetScalar( prhs[cnt_arg] );
  }
  
  cnt_arg = 3;
  flag_argcheck = argcheck_DoubleScalar( nlhs , plhs , nrhs-cnt_arg , &prhs[cnt_arg] );
  if ( -1 == flag_argcheck )
  {}
  else
  {
    if ( 0 != flag_argcheck )
      mexErrMsgTxt("4th input (reltol) should be a double scalar.");
    else
      reltol = mxGetScalar( prhs[cnt_arg] );
  }
  
  cnt_arg = 4;
  flag_argcheck = argcheck_DoubleScalar( nlhs , plhs , nrhs-cnt_arg , &prhs[cnt_arg] );
  if ( -1 == flag_argcheck )
  {}
  else
  {
    if ( 0 != flag_argcheck )
      mexErrMsgTxt("5th input (ftol) should be a double scalar.");
    else
      ftol = mxGetScalar( prhs[cnt_arg] );
  }
  
  cnt_arg = 5;
  flag_argcheck = argcheck_DoubleScalar( nlhs , plhs , nrhs-cnt_arg , &prhs[cnt_arg] );
  if ( -1 == flag_argcheck )
  {}
  else
  {
    if ( 0 != flag_argcheck )
      mexErrMsgTxt("6th input (maxIter) should be a double scalar. It will be cast into \"unsigned int\".");
    else
      maxIter = (unsigned int) mxGetScalar( prhs[cnt_arg] );
  }
  
  // initialize solver
  BisectionMethod *B;
  
  // do not consider arguments after the sixth
  int nrhs_ = nrhs;
  if ( nrhs_ > 6 )
    nrhs_ = 6;
  
  switch(nrhs_-1)
  {
    case 5:
      B = new BisectionMethod
        ( callback_diode , static_cast<void*>(d_log) , 
          limLeft , limRight , abstol , reltol , ftol , maxIter );
      break;
    case 4:
      B = new BisectionMethod
        ( callback_diode , static_cast<void*>(d_log) , 
          limLeft , limRight , abstol , reltol , ftol );
      break;
    case 3:
      B = new BisectionMethod
        ( callback_diode , static_cast<void*>(d_log) , 
          limLeft , limRight , abstol , reltol );
      break;
    case 2:
      B = new BisectionMethod
        ( callback_diode , static_cast<void*>(d_log) , 
          limLeft , limRight , abstol );
      break;
      
    default:
      B = new BisectionMethod
        ( callback_diode , static_cast<void*>(d_log) , 
          limLeft , limRight );
      break;
  }
    
  // compute
  B->compute();
  
  // prepare the output to be returned to matlab prompt
  const std::list<SolnItem> &llist = B->getList();
  const char *field_names[] = { "val" , "fval" , "err_x" , "err_f" };
  mwSize dims[2] = { 1 , llist.size() };
  
  int       field_val , field_fval , field_err_x , field_err_f;
  mxArray * value;
  
  if ( -1 == B->getFlag() )
  {
    plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
  }
  else
  {
    plhs[0] = mxCreateStructArray(2, dims, 4, field_names);
  
    field_val   = mxGetFieldNumber( plhs[0] , "val"   );
    field_fval  = mxGetFieldNumber( plhs[0] , "fval"  );
    field_err_x = mxGetFieldNumber( plhs[0] , "err_x" );
    field_err_f = mxGetFieldNumber( plhs[0] , "err_f" );
    
    if (llist.size() > 0)
    {
      cnt = 0;
      for 
        (
          std::list<SolnItem>::const_iterator 
            it = llist.begin() ; 
          it != llist.end() ; 
          ++it
        )
      {
        value = mxCreateDoubleScalar( (*it).point.val );
        mxSetFieldByNumber( plhs[0] , cnt , field_val    , value );
        value = mxCreateDoubleScalar( (*it).point.fval );
        mxSetFieldByNumber( plhs[0] , cnt , field_fval   , value );
        value = mxCreateDoubleScalar( (*it).err_x );
        mxSetFieldByNumber( plhs[0] , cnt , field_err_x  , value );
        value = mxCreateDoubleScalar( (*it).err_f );
        mxSetFieldByNumber( plhs[0] , cnt , field_err_f  , value );
        
        cnt++;
      }
    }
  }
  
  // the second output (if required)
  if ( nlhs >= 2 )
  {
    plhs[1] = mxCreateDoubleScalar( (double) B->getFlag() );
  }

  // destroy allocated space
  delete d_log;
  delete B;
  
  return;
}

// 
// argcheck_DoubleScalar
// 
// returns :
//    0 : OK
//   -1 : not enough input arguments
//   -2 : first input not double scalar
// 
int
argcheck_DoubleScalar
(
        int       nlhs ,
        mxArray * plhs[] ,
        int       nrhs ,
  const mxArray * prhs[]
)
{
  int retval = -99;
  
  if ( nrhs >= 1 )
  {
    if ( !( ( mxGetClassID(prhs[0]) == mxDOUBLE_CLASS ) &&
            ( mxGetNumberOfElements(prhs[0]) == 1 ) 
          ) )
      retval = -2;
    else
      retval = 0;
  }
  else
    retval = -1;
  
  return retval;
}


#if 0
int
main
(void)
{
  using namespace userdefn;
  using namespace nummethods;
  
  // variables for the diode circuit
  double R   = 1e3;
  double IS  = 3e-15;
  double VIN = 3.3;
  double VT  = 25e-3;
  
  // polymorphic pointers declared and initialized
  DiodeCircuit *d_exp = 
    new DiodeCircuitWithExp( R , IS , VIN , VT );
  
  DiodeCircuit *d_log = 
    new DiodeCircuitWithLog( R , IS , VIN , VT );
  
  // initialize solver
  BisectionMethod B
    ( callback_diode , static_cast<void*>(d_log) , 
      0.68 , 1.0 , 1e-30 , 1e-3 , 1e-5 );
    
  // compute
  B.compute();
  
  // report
  if ( -1 != B.getFlag() )
  {
    const std::list<SolnItem> &llist = B.getList();
    int cnt;
    
    printf("\nValues and Function Values\n\n");
    cnt = 0;
    for 
      (
        std::list<SolnItem>::const_iterator 
          it = llist.begin() ; 
        it != llist.end() ; 
        ++it
      )
    {
      cnt++;
      printf
        ( "Iter %d : %.16e %.16e\n" , cnt , 
          (*it).point.val , (*it).point.fval
        );
    }
    
    printf("\nErrors in Values and Function Values\n\n");
    cnt = 0;
    for 
      (
        std::list<SolnItem>::const_iterator 
          it = llist.begin() ; 
        it != llist.end() ; 
        ++it
      )
    {
      cnt++;
      printf
        ( "Iter %d : %.16e %.16e\n" , cnt , 
          (*it).err_x , (*it).err_f
        );
    }
  }
    
  // destroy allocated space
  delete d_exp;
  delete d_log;
  
  return 0;
}
#endif
