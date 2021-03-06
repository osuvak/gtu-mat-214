#include <iostream>
#include <list>
#include <stdio.h>

#define REPORT_EXISTENCE

#include "available_functions.hh"
#include "fptrholder.hh"

int main(void)
{
  using namespace std;
  
  list<FPTRHolder> llist;
  
  llist.emplace_front();
  (*(llist.begin())).fptr = increment_by_one;
  llist.emplace_front();
  (llist.begin())->fptr = squarer;
  
  double num = 4.1;
  unsigned int ii = 0;
  
  for ( std::list<FPTRHolder>::iterator it=llist.begin() ; it != llist.end() ; ++it )
  {
    cout << "Index of Current Holder : " << ii << endl;
//     printf( "Result : %7.3f\n" , it->fptr(num) );
    printf( "Result : %7.3f\n" , (*it).fptr(num) );
    
    if ( ii < - 1 + llist.size() )
    { cout << endl; }
    
    ii++;
  }

  return 0;
} 
