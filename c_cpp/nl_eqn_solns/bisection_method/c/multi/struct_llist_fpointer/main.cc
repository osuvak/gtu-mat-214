#include<stdio.h> 

#include "functions_objective.hh"
#include "bisection_options.hh"

int
main
(void)
{
  BisectionOptions opt_log , opt_exp;
  
  opt_log.fptr = func_bias_diode;
  opt_log.left  = 0.65;
  opt_log.right = 0.9;
  opt_log.abstol = 1e-30;
  opt_log.reltol = 1e-6;
  opt_log.ftol   = 1e-8;
  opt_log.maxIter = 50;
  
  opt_exp = opt_log;
  opt_exp.fptr = func_bias_diode_with_exp;
  
  return 0;
}
