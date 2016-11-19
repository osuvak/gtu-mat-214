#ifndef MY_STRUCT_CPP_HH_
#define MY_STRUCT_CPP_HH_

#include <iostream>

struct MyCPPType
{
//   Default is public
  MyCPPType(int number = 0) : number_(number)
  { std::cout << "Called constructor for MyCPPType." << std::endl; }
  
  ~MyCPPType() { std::cout << "Called destructor for MyCPPType."  << std::endl; }
  
  int 
  get_number(void) const;
  
  void 
  set_number(double number);
  
private:
  int number_;
  
};

#endif 
