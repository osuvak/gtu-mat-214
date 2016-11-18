#include <iostream>
#include <vector>
#include <stdio.h>

#define REPORT_EXISTENCE

#include "available_functions.hh"
#include "fptrholder.hh"

#define USE_EMPLACE_ONLY

int main(void)
{
  using namespace std;
  
  vector<FPTRHolder> llist;

#ifdef USE_EMPLACE_ONLY
  
  llist.emplace( llist.begin() );
  llist[0].fptr = increment_by_one;
  llist.emplace( llist.begin() );
//   (llist.begin())->fptr = squarer;
  (*(llist.begin())).fptr = squarer;
  
#else
  
  llist.emplace_back();
  llist[-1+llist.size()].fptr = increment_by_one;
  llist.emplace_back();
  (&llist[-1+llist.size()])->fptr = squarer;
  
#endif
  
  double num = 4.1;
  unsigned int ii = 0;
  
  for ( std::vector<FPTRHolder>::iterator it=llist.begin() ; it != llist.end() ; ++it )
  {
    cout << "Index of Current Holder : " << ii << endl;
    printf( "Result : %7.3f\n" , it->fptr(num) );
    
    if ( ii < - 1 + llist.size() )
    { cout << endl; }
    
    ii++;
  }

  return 0;
} 
