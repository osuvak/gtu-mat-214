#include <iostream>
#include <vector>
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
  
  vector<FPTRHolder*> llist;
  
  llist.push_back( new FPTRHolder() );
//   (*(llist.end()))->fptr = increment_by_one;
  llist[-1+llist.size()]->fptr = increment_by_one;
  llist.push_back( new FPTRHolder() );
//   (*(llist.end()))->fptr = squarer;
  llist[-1+llist.size()]->fptr = squarer;
  
  double num = 4.1;
  unsigned int ii = -1;
  
  for ( std::vector<FPTRHolder*>::iterator it=llist.begin() ; it != llist.end() ; ++it )
  {
    ii++;
    cout << "Index of Current Holder : " << ii << endl;
    printf( "Result : %7.3f\n" , (*it)->fptr(num) );
    
    if ( ii < - 1 + llist.size() )
    { cout << endl; }
  }

#ifndef DO_NOT_DESTROY
  for ( std::vector<FPTRHolder*>::iterator it=llist.begin() ; it != llist.end() ; ++it )
  {
    delete *it;
  }
#endif

  return 0;
} 
