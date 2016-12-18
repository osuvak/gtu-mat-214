/*
 * An exercise on list iterator arithmetics.
 * Pre/Post increment/decrement are not distinct.
 * Storing apparently non-existent dereferenced container content,
 * but keeping list content intact, no errors/asserts/exceptions.
 * 
 * Also C-style array initialization example included.
 * "get_size" function template now working.
 * 
 * See the following entry on this last aspect:
 * http://stackoverflow.com/questions/9626722/c-string-array-initialization
 * 
 * */

#include <iostream> 
#include <cstdio>
#include <vector>
#include <list>

void print_contents( const std::list<double> & dlist );

template <typename T , unsigned N>
unsigned int get_size( T const (&container)[N] );

int main(void)
{
  using namespace std;
  
  const double dlist_raw[] = { 3.14 , 2.71 , -1.2 , 0.19  };
  
  list<double> dlist;
  
  unsigned int size = get_size(dlist_raw);
  for ( unsigned int ii = 0 ; ii < size ; ii++ )
//   for ( unsigned int ii = 0 ; ii < sizeof(dlist_raw) / sizeof(double) ; ii++ )
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

template <typename T , unsigned N>
unsigned int get_size( T const (&container)[N] )
// BOTH OF THE FOLLOWING ARE JUNK.
// unsigned int get_size(T * container)
// unsigned int get_size(const std::list<T> & container)
{
  using namespace std;
  
  static unsigned int no_calls = 0;
  
  cout << "Number of call to get_size : " << ++no_calls << endl;
  cout << "Size of container : " << sizeof(container) << endl;
  cout << "Size of T         : " << sizeof(T) << endl;
  
  return sizeof(container) / sizeof(T);
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