// #ifdef USE_PRAGMA_ONCE

#pragma once

// #else

// #ifndef MY_CLASS_HH_
// #define MY_CLASS_HH_

// #endif

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

// #ifndef USE_PRAGMA_ONCE
// #endif
// #endif
