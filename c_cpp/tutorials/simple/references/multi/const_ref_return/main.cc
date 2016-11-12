#include <iostream> 
#include <stdio.h>

#include "myclasses.hh"

// #define USE_CONST_ITERATORS

int main (void)
{
  using namespace std;
  
  IntegerHolder A(5);
  A.append(6);
  
  const vector<int> &vec = A.get_vector();
  
#ifdef USE_CONST_ITERATORS
  
  unsigned int ii = -1;
  for ( auto it = vec.cbegin() ; it != vec.cend() ; ++it )
  {
    ii++;
    cout << "Index of Current Entry : " << ii << endl;
    printf( "  %6d\n" , *it );
    
    if ( ii < - 1 + vec.size() )
    { cout << endl; }
  }
  
#else

  for ( unsigned int ii = 0 ; ii < vec.size() ; ii++ )
  {
    cout << "Index of Current Entry : " << ii << endl;
    printf( "  %6d\n" , vec[ii] );
    
    if ( ii < - 1 + vec.size() )
    { cout << endl; }
  }

#endif
  
  return 0;
}