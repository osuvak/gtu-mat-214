#include "defn_struct.hh"

int main (void)
{
  Container myContainer1;
  Container *ptrMyContainer2 = new Container;
  
  myContainer1.num = 5;
  myContainer1.str = "Onder";
  
  myContainer1.printContainer();
  
  myContainer1.str += "Onder";
  myContainer1.printContainer();
  
  ptrMyContainer2->num = 10;
  ptrMyContainer2->str = "Emre";
  
  ptrMyContainer2->printContainer();
  
  delete ptrMyContainer2;
  
  return 0;
}