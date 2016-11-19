#include "my_struct_cpp.hh" 

int 
MyCPPType::get_number(void) const
{
  return this->number_;
//   return number_;
}
  
void 
MyCPPType::set_number(double number)
{
  this->number_ = number;
//   number_ = number;
}