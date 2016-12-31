#ifndef BISECTION_HH_
#define BISECTION_HH_

#include<list>
#include<iostream>
#include<cstdio>
#include<cassert>
#include<cmath>
#include<memory>

#include "internals/bisection_internals.hh"
#include "utilities/utilities_general.hh"

#include "common/defines.hh"

namespace nummethods
{
  
class CallbacksFather
{
public:
  CallbacksFather  () {}
  virtual ~CallbacksFather () {}
  
  virtual double callback(double number) = 0;
};
  
class BisectionMethod
{
  
private:

#ifdef USE_SHARED_PTR_INSIDE_LIB
  std::shared_ptr<CallbacksFather> callback_class_ptr_;
#else  
  CallbacksFather *callback_class_ptr_;
#endif
  
  double   limLeft_;
  double   limRight_;
  double   abstol_;
  double   reltol_;
  double   ftol_;
  double   maxIter_;
  
private:
  
  int                 flag_;
  std::list<SolnItem> llist_;
  
public:
  
  BisectionMethod
  (
#ifdef USE_SHARED_PTR_INSIDE_LIB
    std::shared_ptr<CallbacksFather> ptr ,
#else
    CallbacksFather *ptr ,
#endif
    double   limLeft ,
    double   limRight ,
    double   abstol   = 1.0e-30 ,
    double   reltol   = 1.0e-3 ,
    double   ftol     = 1.0e-4 ,
    double   maxIter  = 50
  )
  :
  callback_class_ptr_(ptr) ,
  limLeft_  (limLeft) ,
  limRight_ (limRight) ,
  abstol_   (abstol) ,
  reltol_   (reltol) ,
  ftol_     (ftol) ,
  maxIter_  (maxIter)
  {
    llist_.clear();
#ifdef USE_SHARED_PTR_INSIDE_LIB    
    assert( callback_class_ptr_.get() != NULL );
#else 
    assert( callback_class_ptr_ != NULL );
#endif
  }
  
  ~BisectionMethod
  ()
  {
    llist_.clear();
  }

#ifdef USE_SHARED_PTR_INSIDE_LIB    
  const std::shared_ptr<CallbacksFather> &
  getPointer
  ()
  const
  {
    return callback_class_ptr_;
  }
#else 
  CallbacksFather *
  getPointer
  ()
  const
  {
    return callback_class_ptr_;
  }
#endif
  
  double call (double number) const { return callback_class_ptr_->callback(number); }
  
  void
  compute
  ();
  
  int
  getFlag
  ()
  const
  {
    return flag_;
  }
  
  const std::list<SolnItem> &
  getList
  ()
  const
  {
    return llist_;
  }
};
  
} // nummethods

#endif
