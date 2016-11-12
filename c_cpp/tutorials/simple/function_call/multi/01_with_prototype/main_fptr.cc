#include <iostream>
#include <stdio.h>

#include "available_functions.hh"

int main(void)
{
  using namespace std;
  
  double (*fptr)(double);
  fptr = increment_by_one;
  
  double num = 4.1;
  
//   cout << "Result : " << fptr(num) << endl;
  printf( "Result : %7.3f\n" , fptr(num) );
  
  return 0;
} 
