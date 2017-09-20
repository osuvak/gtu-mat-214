#include "defn_struct.hh"

void Container::printContainer()
{
  std::cout 
    << "  String : " << this->str << std::endl
    << "  Number : " << this->num 
    << std::endl;
}