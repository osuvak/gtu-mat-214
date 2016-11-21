/*
 * Example adapted from :
 * http://www.cplusplus.com/reference/memory/shared_ptr/swap-free/
 * */

// shared_ptr swap specialization
#include <iostream>
#include <memory>

int main () 
{
  using namespace std;
  
  std::shared_ptr<int> foo (new int(10));
  std::shared_ptr<int> bar (new int(20));

  cout << "foo: " << *foo << "    " << "bar: " << *bar << endl;
  swap(foo,bar);
  cout << "Swapped." << endl;
  cout << "foo: " << *foo << "    " << "bar: " << *bar << endl;
  swap(foo,bar);
  cout << "Swapped." << endl;
  cout << "foo: " << *foo << "    " << "bar: " << *(bar.get()) << endl;
  
  return 0;
}