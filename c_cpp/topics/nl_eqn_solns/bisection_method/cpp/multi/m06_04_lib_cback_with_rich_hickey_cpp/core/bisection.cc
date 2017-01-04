#include "bisection.hh" 

namespace nummethods
{
  
void
BisectionMethod::compute
()
{
  
  this->flag_ = -99; // invalid value
  IntervalInfo interval;
  
  double fval_ref , fval_ref_l , fval_ref_r;
  double x_lhs , x_rhs , f_lhs , f_rhs;
  int    logicVal1 , logicVal2;
  
  // initialize interval and check validity of end-points
  interval.left.val   = limLeft_;
//   interval.left.fval  = this->callback_(interval.left.val,userdata_);
  interval.left.fval  = this->callback_(interval.left.val);
  interval.left.sign  = signum(interval.left.fval);
  
  interval.right.val  = limRight_;
//   interval.right.fval = this->callback_(interval.right.val,userdata_);
  interval.right.fval = this->callback_(interval.right.val);
  interval.right.sign = signum(interval.right.fval);

  if ( -1 != interval.left.sign * interval.right.sign )
  {
    std::cout << "The initial interval is not valid. Cannot continue..." << std::endl;
    this->flag_ = -1;
    return;
  }
  
  // compute fval_ref (this is cumbersome in C)
  fval_ref_l = fabs( interval.left.fval );
  fval_ref_r = fabs( interval.right.fval );
  
  fval_ref = (fval_ref_l>fval_ref_r) ? fval_ref_r : fval_ref_l;
  
  // now iterate
  llist_.clear();
  while ( llist_.size() < maxIter_ )
  {
    std::cout << "Iteration " << llist_.size()+1 << std::endl;
    printf("  The soln is between:\n    %.6e and %.6e\n",interval.left.val,interval.right.val);
    
    interval.mid.val  = 1.0 / 2.0 * ( interval.left.val + interval.right.val );
//     interval.mid.fval = this->callback_( interval.mid.val , userdata_ );
    interval.mid.fval = this->callback_( interval.mid.val );
    interval.mid.sign = signum( interval.mid.fval );
    
    if ( llist_.size() <= 0 )
    {
      // there is no data yet, initialize the linked list with the first arriving data
      llist_.emplace_back( interval.mid , 0.0 , 0.0 );
    }
    else
    {
      const SolnItem &last = llist_.back();
      
      // check tolerances and quit the iterations if cond are satisfied
      // check - relative error in iterate
      x_lhs = fabs( last.point.val - interval.mid.val );
      x_rhs = 0.5 * ( fabs(last.point.val) + fabs(interval.mid.val) );
      logicVal1 = ( x_lhs < reltol_ * x_rhs + abstol_ );
      // check - relative error in function value at the iterate
      f_lhs = fabs( interval.mid.fval );
      f_rhs = fval_ref;
      logicVal2 = ( f_lhs < ftol_ * f_rhs );
      
      printf("  logicVal1 : %d\n  logicVal2 : %d\n",logicVal1,logicVal2);
      
      // append to soln linked list
      llist_.emplace_back( interval.mid , x_lhs / x_rhs , f_lhs / f_rhs );
      
      // actually check errors and break if necessary
      if ( logicVal1 && logicVal2 )
      {
        std::cout << "Soln found in " << llist_.size() << " iterations." << std::endl;
        this->flag_ = 0;
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
  if ( this->flag_ != 0 )
  {
    printf("A satisfactory soln could not be computed. Maximum number of iterations reached...\n");
    this->flag_ = -2;
  }
  
  return;
}
  
} // nummethods
