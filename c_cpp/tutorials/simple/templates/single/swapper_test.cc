#include <iostream>
#include <cstdio>

// #define TRY_SWAPPING_INCOMPATIBLE_TYPES

template <class T>
void swapper (T &a , T &b) 
{
  T temp;
  temp = a;
  a = b;
  b= temp;
}

int main (void)
{
  using namespace std;
  
  double a = 1.0 , b = 2.1;
  int c = 3;
  
//   cout << "a = " << a << "   " << "b = " << b << endl;
  printf( "a = %4.1f   b = %4.1f\n" , a , b );
  swapper(a,b);
//   cout << "a = " << a << "   " << "b = " << b << endl;
  printf( "a = %4.1f   b = %4.1f\n" , a , b );
  swapper<double>(a,b);
//   cout << "a = " << a << "   " << "b = " << b << endl;
  printf( "a = %4.1f   b = %4.1f\n" , a , b );

#ifdef TRY_SWAPPING_INCOMPATIBLE_TYPES
//   swapper(a,c);
//   swapper<double>(a,c);
  swapper<int>(a,c);
  cout << "a = " << a << "   " << "c = " << c << endl;
#endif
  
  return 0;
}