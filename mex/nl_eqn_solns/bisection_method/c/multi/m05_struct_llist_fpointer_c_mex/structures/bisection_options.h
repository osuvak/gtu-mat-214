#ifndef BISECTION_OPTIONS_H_
#define BISECTION_OPTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BisectionOptions_
{
  double (*fptr)(double);
  
  double left;
  double right;
  
  double abstol,reltol,ftol;
  
  unsigned 
  int maxIter;
}BisectionOptions;

#ifdef __cplusplus
}
#endif

#endif
