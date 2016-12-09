/*
 * Adapted from :
 * http://www.cplusplus.com/reference/array/array/fill/
 * 
 * */

// array::fill example
#include <iostream>
#include <array>

class MyClass
{
private:
  int num_;
  
public:
//   MyClass(int num = 0) : num_(num) {}
  
  MyClass(int num) : num_(num) { std::cout << "Constructor with int arg called." << std::endl; }
  MyClass()        : num_(0)   { std::cout << "Constructor with no  arg called." << std::endl; }
  ~MyClass() { std::cout << "Destructor called." << std::endl; }
  
  int get_number (void) const { return num_; }
};

int main () {
  MyClass A(5);
  std::array<MyClass,6> myarray;

  myarray.fill(A);

  std::cout << "myarray contains:";
  for ( MyClass& x : myarray) { std::cout << ' ' << x.get_number(); }

  std::cout << '\n';

  return 0;
} 
