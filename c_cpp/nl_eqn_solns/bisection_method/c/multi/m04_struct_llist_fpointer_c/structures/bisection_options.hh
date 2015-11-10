#ifndef BISECTION_OPTIONS_HH_
#define BISECTION_OPTIONS_HH_

typedef struct BisectionOptions_
{
  double (*fptr)(double);
  
  double left;
  double right;
  
  double abstol,reltol,ftol;
  
  unsigned 
  int maxIter;
}BisectionOptions;

#endif
