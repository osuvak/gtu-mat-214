#include <iostream>
#include <list>
#include <stdio.h>

// if this define is active, then construction and destruction are reported on stdout.
#define REPORT_EXISTENCE

// Can comment out the next define to see what happens
// #define DO_NOT_DESTROY

#include "available_functions.hh"
#include "fptrholder.hh"

int main(void)
{
  using namespace std;
  
  list<FPTRHolder*> llist;
  
  llist.push_front( new FPTRHolder() );
  (*(llist.begin()))->fptr = increment_by_one;
  llist.push_front( new FPTRHolder() );
  (*(llist.begin()))->fptr = squarer;
  
  double num = 4.1;
  unsigned int ii = -1;
  
  for ( std::list<FPTRHolder*>::iterator it=llist.begin() ; it != llist.end() ; ++it )
  {
    ii++;
    cout << "Index of Current Holder : " << ii << endl;
    printf( "Result : %7.3f\n" , (*it)->fptr(num) );
    
    if ( ii < - 1 + llist.size() )
    { cout << endl; }
  }

#ifndef DO_NOT_DESTROY
  for ( std::list<FPTRHolder*>::iterator it=llist.begin() ; it != llist.end() ; ++it )
  {
    delete *it;
  }
#endif

  return 0;
} 
