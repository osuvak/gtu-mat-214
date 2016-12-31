#ifndef BISECTION_HH_
#define BISECTION_HH_

#include<list>
#include<iostream>
#include<cstdio>
#include<cmath>

#include "internals/bisection_internals.hh"
#include "utilities/utilities_general.hh"

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
  
  CallbacksFather *callback_class_ptr_;
  
//   double (*callback_)(double,void*);
//   void    *userdata_;
  
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
    CallbacksFather *ptr ,
//     double (*callback)(double,void*) ,
//     void    *userdata ,
    double   limLeft ,
    double   limRight ,
    double   abstol   = 1.0e-30 ,
    double   reltol   = 1.0e-3 ,
    double   ftol     = 1.0e-4 ,
    double   maxIter  = 50
  )
  :
  callback_class_ptr_(ptr) ,
//   callback_ (callback) ,
//   userdata_ (userdata) ,
  limLeft_  (limLeft) ,
  limRight_ (limRight) ,
  abstol_   (abstol) ,
  reltol_   (reltol) ,
  ftol_     (ftol) ,
  maxIter_  (maxIter)
  {
    llist_.clear();
  }
  
  ~BisectionMethod
  ()
  {
    llist_.clear();
  }
  
  double call (double number) const { return this->callback_class_ptr_->callback(number); }
  
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
