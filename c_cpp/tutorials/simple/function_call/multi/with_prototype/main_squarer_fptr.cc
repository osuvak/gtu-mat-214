#include <iostream>
#include <stdio.h>

#include "available_functions.hh"

int main(void)
{
  using namespace std;
  
  double (*fptr)(double);
  fptr = squarer;
  
  double num = 4.1;
  
//   cout << "Square of number : " << fptr(num) << endl;
//   printf( "Square of number : %.1f\n" , fptr(num) );
//   printf( "Square of number :%6.3f\n" , fptr(num) );
  printf( "Square of number :%7.3f\n" , fptr(num) );
  
  return 0;
} 
