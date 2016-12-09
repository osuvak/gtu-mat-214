#include <iostream>
#include <array>

// #define USE_PRAGMA_ONCE
#include "my_class.hh"

int main ()
{
//   MyClass::flag_talks = false;
//   MyClass::set_flag_talks(false);
  
  std::array<MyClass,10> myarray;

  // assign some values:
  for (int i=0; i<10; i++) myarray.at(i).set_number( i+1 );

  // print content:
  std::cout << "myarray contains:";
  for (int i=0; i<10; i++)
    std::cout << ' ' << myarray.at(i).get_number();
  std::cout << '\n';

//   MyClass::flag_talks = false;
  MyClass::set_flag_talks(false);
  
  return 0;
} 
