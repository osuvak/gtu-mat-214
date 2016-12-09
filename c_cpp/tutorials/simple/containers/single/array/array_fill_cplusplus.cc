/*
 * Adapted from :
 * http://www.cplusplus.com/reference/array/array/fill/
 * 
 * */

// array::fill example
#include <iostream>
#include <array>

int main () {
  std::array<int,6> myarray;

  myarray.fill(5);

  std::cout << "myarray contains:";
  for ( int& x : myarray) { std::cout << ' ' << x; }

  std::cout << '\n';

  return 0;
} 
