#include<stdio.h> 

#include "functions_objective.h"
#include "bisection_options.h"
#include "bisection_internals.h"
#include "bisection_core.h"

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
  // this mex interface is an illustration for func_bias_diode (with log) only
  
  // declarations and opt initialization
  BisectionOptions  opt;
  SolnIterates      soln;
  SolnLList        *cptr;
  
  int flag , flag_argcheck;
  int cnt_arg;
  unsigned int cnt;
  
  opt.fptr = func_bias_diode;
  
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
      opt.left  = mxGetScalar( prhs[cnt_arg] );
    
    cnt_arg = 1;
    if ( 0 != argcheck_DoubleScalar( nlhs , plhs , nrhs-cnt_arg , &prhs[cnt_arg] ) )
      mexErrMsgTxt("2nd input (right limit) should be a double scalar.");
    else
      opt.right = mxGetScalar( prhs[cnt_arg] );
  }
  
  // now check the optional inputs
  cnt_arg = 2;
  flag_argcheck = argcheck_DoubleScalar( nlhs , plhs , nrhs-cnt_arg , &prhs[cnt_arg] );
  if ( -1 == flag_argcheck )
    opt.abstol = 1.0e-30;
  else
  {
    if ( 0 != flag_argcheck )
      mexErrMsgTxt("3rd input (abstol) should be a double scalar.");
    else
      opt.abstol = mxGetScalar( prhs[cnt_arg] );
  }
  
  cnt_arg = 3;
  flag_argcheck = argcheck_DoubleScalar( nlhs , plhs , nrhs-cnt_arg , &prhs[cnt_arg] );
  if ( -1 == flag_argcheck )
    opt.reltol = 1.0e-3;
  else
  {
    if ( 0 != flag_argcheck )
      mexErrMsgTxt("4th input (reltol) should be a double scalar.");
    else
      opt.reltol = mxGetScalar( prhs[cnt_arg] );
  }
  
  cnt_arg = 4;
  flag_argcheck = argcheck_DoubleScalar( nlhs , plhs , nrhs-cnt_arg , &prhs[cnt_arg] );
  if ( -1 == flag_argcheck )
    opt.ftol = 1.0e-5;
  else
  {
    if ( 0 != flag_argcheck )
      mexErrMsgTxt("5th input (ftol) should be a double scalar.");
    else
      opt.ftol = mxGetScalar( prhs[cnt_arg] );
  }
  
  cnt_arg = 5;
  flag_argcheck = argcheck_DoubleScalar( nlhs , plhs , nrhs-cnt_arg , &prhs[cnt_arg] );
  if ( -1 == flag_argcheck )
    opt.maxIter = 50;
  else
  {
    if ( 0 != flag_argcheck )
      mexErrMsgTxt("6th input (maxIter) should be a double scalar. It will be cast into \"unsigned int\".");
    else
      opt.maxIter = (unsigned int) mxGetScalar( prhs[cnt_arg] );
  }
  
  // initialize soln
  inialize(&soln);
  
  // run
  flag = bisection_method( &opt , &soln );
  
  // prepare the output to be returned to matlab prompt
  const char *field_names[] = { "val" , "fval" , "err_x" , "err_f" };
  mwSize dims[2] = { 1 , size(&soln) };
  
  int       field_val , field_fval , field_err_x , field_err_f;
  mxArray * value;
  
  if ( -1 == flag )
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
    
    if (size(&soln) > 0)
    {
      cnt = 0;
      cptr = soln.llist;
      while ( cptr != NULL )
      {
        value = mxCreateDoubleScalar( cptr->point.val );
        mxSetFieldByNumber( plhs[0] , cnt , field_val    , value );
        value = mxCreateDoubleScalar( cptr->point.fval );
        mxSetFieldByNumber( plhs[0] , cnt , field_fval   , value );
        value = mxCreateDoubleScalar( cptr->err_x );
        mxSetFieldByNumber( plhs[0] , cnt , field_err_x  , value );
        value = mxCreateDoubleScalar( cptr->err_f );
        mxSetFieldByNumber( plhs[0] , cnt , field_err_f  , value );
        
        cptr = cptr->next;
        cnt++;
      }
    }
  }
  
  // the second output (if required)
  if ( nlhs >= 2 )
  {
    plhs[1] = mxCreateDoubleScalar( (double) flag );
  }
  
  // destroy soln
  destroy(&soln);
  
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
  BisectionOptions  opt_log , opt_exp;
  SolnIterates      soln;
  SolnLList        *cptr;
  
  int flag;
  unsigned int cnt;
  
  opt_log.fptr = func_bias_diode;
  opt_log.left  = 0.65;
  opt_log.right = 0.9;
  opt_log.abstol = 1.0e-30;
  opt_log.reltol = 1.0e-3;
  opt_log.ftol   = 1.0e-5;
  opt_log.maxIter = 50;
  
  opt_exp = opt_log;
  opt_exp.fptr = func_bias_diode_with_exp;
  
  // initialize soln
  inialize(&soln);
  
  // run
  flag = bisection_method( &opt_log , &soln );
  printf("\nNo of iterations (length of soln array) : %d\n",size(&soln));
  
  if ( (flag == 0) || (flag == -2) )
  {
    if (size(&soln) > 0)
    {
      printf("\nValues and Function Values\n\n");
      cnt = 0;
      cptr = soln.llist;
      while ( cptr != NULL )
      {
        cnt++;
        printf
        ( "Iter %d : %.16e %.16e\n" , cnt , 
          cptr->point.val , cptr->point.fval
        );
        cptr = cptr->next;
      }
      
      printf("\nErrors in Values and Function Values\n\n");
      cnt = 0;
      cptr = soln.llist;
      while ( cptr != NULL )
      {
        cnt++;
        printf
        ( "Iter %d : %.16e %.16e\n" , cnt , 
          cptr->err_x , cptr->err_f
        );
        cptr = cptr->next;
      }
    }
  }
  
  // destroy soln
  destroy(&soln);
  
  return 0;
}
#endif