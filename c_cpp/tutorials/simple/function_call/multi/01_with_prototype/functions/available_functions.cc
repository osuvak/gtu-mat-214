#include "available_functions.hh"

double squarer(double number)
{
//   return number * number;
  return pow( number , 2 );
}

// #define BY_INC_OPERATOR

double increment_by_one(double number)
{
#ifndef BY_INC_OPERATOR

  double num = number + 1.0;
  return num;

//   return number + 1.0;

#else  
  return ++number;
//   return number++;
#endif
}

#ifdef BY_INC_OPERATOR
#undef BY_INC_OPERATOR
#endif