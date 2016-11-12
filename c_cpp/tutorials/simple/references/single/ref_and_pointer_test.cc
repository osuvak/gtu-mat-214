#include <iostream>
#include <stdio.h>

double increment_by_one_copy_by_value(double  number);
void   increment_by_one(double &number);
void   increment_by_one(double *numberptr);

int main (void)
{
  using namespace std;
  
  double number = 4.1;
  
  cout << "Number :" << endl;
  printf( "  %7.3f\n" , number );
  cout << endl;
  
  cout << "Calling copy-by-value function :" << endl;
  printf( "  %7.3f\n" , increment_by_one_copy_by_value(number) );
  cout << endl;
  
  cout << "Number :" << endl;
  printf( "  %7.3f\n" , number );
  cout << endl;
  
  cout << "Calling copy-by-reference function :" << endl;
  increment_by_one(number);
  printf( "  %7.3f\n" , number );
  cout << endl;
  
  cout << "Number :" << endl;
  printf( "  %7.3f\n" , number );
  cout << endl;
  
  cout << "Calling copy-by-pointer function :" << endl;
  increment_by_one(&number);
  printf( "  %7.3f\n" , number );
  cout << endl;
  
  cout << "Number :" << endl;
  printf( "  %7.3f\n" , number );
  cout << endl;
  
  return 0;
}

double increment_by_one_copy_by_value(double  number)
{
  return number + 1.0;
}

void   increment_by_one(double &number)
{
  number += 1.0;
}

void   increment_by_one(double *numberptr)
{
  *numberptr += 1.0;
}
