#include <iostream> 
#include <cstdio>
#include <vector>
#include <list>

void print_contents( const std::list<double> & dlist );

template <typename T>
unsigned int get_size(T * container)
// unsigned int get_size(const std::list<T> & container)
{
  using namespace std;
  
  static unsigned int no_calls = 0;
  
  cout << "Number of call to get_size : " << ++no_calls << endl;
  cout << "Size of container : " << sizeof(container) << endl;
  cout << "Size of T         : " << sizeof(T) << endl;
  
  return sizeof(container) / sizeof(T);
}

int main(void)
{
  using namespace std;
  
  const double dlist_raw[] = { 3.14 , 2.71 , -1.2 , 0.19  };
  
  list<double> dlist;
  for ( unsigned int ii = 0 ; ii < sizeof(dlist_raw) / sizeof(double) ; ii++ )
//   for ( unsigned int ii = 0 ; ii < get_size(dlist_raw) ; ii++ )
    dlist.push_back( dlist_raw[ii] );
  
  print_contents( dlist );
  
  { // scope begin
    auto it = dlist.begin();
    it--;
    printf( "  Number (at the position before begin) : %8.3f\n" , *it );
    *it = 0.2;
    printf( "  Number (at the position before begin) : %8.3f\n" , *it );
    print_contents( dlist );
    
    it = dlist.end();
    printf( "  Number (at the position \"end\")        : %8.3f\n" , *it );
    *it = 0.4;
    printf( "  Number (at the position \"end\")        : %8.3f\n" , *it );
    print_contents( dlist );
    
    it = dlist.begin();
    it--;
    printf( "  Number (at the position before begin) : %8.3f\n" , *it );
    print_contents( dlist );
    
    it = dlist.end();
    it--;
    printf( "  Number (at the position before end)   : %8.3f\n" , *it );
  } // scope end
  
  { // scope begin
    auto it = dlist.begin();
//     it = it + 1;
//     it += 1;
    ++it;
    printf( "  Number (at the position after begin)  : %8.3f\n" , *it );
//     it = it - 1;
//     it -= 1;
    printf( "  Number (at the position after begin)  : %8.3f\n" , *it );
  } // scope end
  
  return 0;
}

void print_contents( const std::list<double> & dlist )
{
  using namespace std;
  
  cout << "\nReport :" << endl << endl;
  
  unsigned int ii = 0;
//   for ( auto it = dlist.begin() ; it != dlist.end() ; ++it )
  for ( auto it = dlist.begin() ; it != dlist.end() ; it++ )
  {
    printf( "  Index : %6d  Number : %8.3f\n" , ii++ , *it );
  }
  
  cout << endl;
}