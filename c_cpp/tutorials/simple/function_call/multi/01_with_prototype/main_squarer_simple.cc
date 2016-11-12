#include <iostream>
#include <stdio.h>

#include "available_functions.hh"

int main(void)
{
  using namespace std;
  
  double num = 4.1;
  
//   cout << "Square of number : " << squarer(num) << endl;
//   printf( "Square of number : %.1f\n" , squarer(num) );
//   printf( "Square of number :%6.3f\n" , squarer(num) );
  printf( "Square of number :%7.3f\n" , squarer(num) );
  
  return 0;
} 
