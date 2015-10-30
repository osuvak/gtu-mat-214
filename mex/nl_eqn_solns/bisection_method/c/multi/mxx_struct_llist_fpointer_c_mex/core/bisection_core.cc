#include "bisection_core.hh" 

// 
// bisection_method
// 
// returns:
//  0 : normal return (no warnings)
// -1 : initial interval not valid
// -2 : maximum no of iterations reached (not converged)
// 
int
bisection_method
(
  const BisectionOptions * ptr_opt ,
        SolnIterates     * soln
)
{
  int flag = -99; // invalid value
  BisectionOptions opt = *ptr_opt;
  IntervalInfo interval;
  
  double fval_ref , fval_ref_l , fval_ref_r;
  double x_lhs , x_rhs , f_lhs , f_rhs;
  int    logicVal1 , logicVal2;
  
  const SolnLList *last;
  
  // initialize interval and check validity of end-points
  interval.left.val   = opt.left;
  interval.left.fval  = opt.fptr(interval.left.val);
  interval.left.sign  = signum(interval.left.fval);
  
  interval.right.val  = opt.right;
  interval.right.fval = opt.fptr(interval.right.val);
  interval.right.sign = signum(interval.right.fval);
  
  if ( -1 != interval.left.sign * interval.right.sign )
  {
    printf("The initial interval is not valid. Cannot continue...\n");
    flag = -1;
    return flag;
  }
  
  // compute fval_ref (this is cumbersome in C)
  fval_ref_l = fabs( interval.left.fval );
  fval_ref_r = fabs( interval.right.fval );
  
  fval_ref = (fval_ref_l>fval_ref_r) ? fval_ref_r : fval_ref_l;
  
  // now iterate
  while ( size(soln) < opt.maxIter )
  {
    printf( "Iteration %d\n" , size(soln)+1 );
    printf("  The soln is between:\n    %.6e and %.6e\n",interval.left.val,interval.right.val);
    
    interval.mid.val  = 1.0 / 2.0 * ( interval.left.val + interval.right.val );
    interval.mid.fval = opt.fptr( interval.mid.val );
    interval.mid.sign = signum( interval.mid.fval );
    
    if ( size(soln) <= 0 )
    {
      // there is no data yet, initialize the linked list with the first arriving data
      append( soln , interval.mid , 0.0 , 0.0 );
    }
    else
    {
//       printf("before getLast\n");
      last = getLast(soln);
//       printf("after getLast\n");
      
//       if ( last == NULL )
//         printf("last is NULL.\n");
//       else
//         printf("last is not NULL.\n");
      
      // check tolerances and quit the iterations if cond are satisfied
      // check - relative error in iterate
      x_lhs = fabs( last->point.val - interval.mid.val ) - opt.abstol;
      x_rhs = 0.5 * ( fabs(last->point.val) + fabs(interval.mid.val) );
      logicVal1 = ( x_lhs < opt.reltol * x_rhs );
      // check - relative error in function value at the iterate
      f_lhs = fabs( interval.mid.fval );
      f_rhs = fval_ref;
      logicVal2 = ( f_lhs < opt.ftol * f_rhs );
      
      printf("  logicVal1 : %d\n  logicVal2 : %d\n",logicVal1,logicVal2);
      
//       printf("before append\n");
      // append to soln linked list
      append( soln , interval.mid , x_lhs / x_rhs , f_lhs / f_rhs );
//       printf("after append\n");
      
      // actually check errors and break if necessary
      if ( logicVal1 && logicVal2 )
//       if ( (x_lhs < opt.reltol * x_rhs) && (f_lhs < opt.ftol * f_rhs) )
      {
        printf("Soln found in %d iterations.\n",size(soln));
        flag = 0;
        break;
      }
    }
    
    // error check failed - prepare intervals for the next iteration
    if ( -1 == interval.left.sign * interval.mid.sign )
      interval.right = interval.mid;
    else
      interval.left  = interval.mid;
  }
  
  // check if soln found and issue warning
  if ( flag != 0 )
  {
    printf("A satisfactory soln could not be computed. Maximum number of iterations reached...\n");
    flag = -2;
  }
  
  return flag;
}