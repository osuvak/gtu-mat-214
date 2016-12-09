/*
 * Adapted from:
 * http://www.cplusplus.com/reference/array/array/at/
 * 
 * */

// array::at
#include <iostream>
#include <array>

class MyClass
{
private:
  int num_;
  
private:
  static bool flag_talks_;
  
public:
//   MyClass(int num = 0) : num_(num) {}
  
  MyClass(int num) : num_(num) 
  { 
    if ( flag_talks_ )
      std::cout << "Constructor with int arg called." << std::endl; 
  }
  MyClass()        : num_(0)   
  { 
    if ( flag_talks_ )
      std::cout << "Constructor with no  arg called." << std::endl; 
  }
  ~MyClass() 
  { 
    if ( flag_talks_ )
      std::cout << "Destructor called." << std::endl; 
  }
  
  int  get_number (void) const { return num_; }
  void set_number (int number) { this->num_ = number; }
  
public:
  static void set_flag_talks(bool lval)
  { flag_talks_ = lval; }
};

bool MyClass::flag_talks_ = true;

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
