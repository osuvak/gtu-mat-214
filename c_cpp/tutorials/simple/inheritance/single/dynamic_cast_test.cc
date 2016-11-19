#include <iostream>
#include <cstdio>

#include <stdexcept>

/*
 * Activate this define and observe the warnings in compilation
 * and also the destruction process reports written to stdout.
*/ 
// #define MAKE_DESTRUCTORS_NONVIRTUAL

/*
 * Activate this define to make the Base class abstract 
 * (by virtue of the purely virtual method to be implemented in Derived).
*/
#define MAKE_BASE_ABSTRACT

class Base 
{ 
private:
public:
  Base () { std::cout << "Called constructor of Base." << std::endl; }

#ifndef MAKE_DESTRUCTORS_NONVIRTUAL
  virtual
#endif
  ~Base() { std::cout << "Called destructor of Base." << std::endl; }
  
#ifdef MAKE_BASE_ABSTRACT
  virtual void method_purely_virtual () = 0;
#endif
  
  virtual void method_virtual () 
  { std::cout << "Called \"method_virtual\" of Base." << std::endl; }
  
  void method_nonvirtual () 
  { std::cout << "Called \"method_nonvirtual\" of Base." << std::endl; }
};

class Derived: public Base 
{ 
private:
  int number_;
public:
  Derived  (int number = 0) : number_(number) 
  { std::cout << "Called constructor of Derived." << std::endl; }
  
#ifndef MAKE_DESTRUCTORS_NONVIRTUAL
  virtual
#endif
  ~Derived () { std::cout << "Called destructor of Derived." << std::endl; }
  
#ifdef MAKE_BASE_ABSTRACT
  virtual void method_purely_virtual ()
  { std::cout << "Called \"method_purely_virtual\" (now implemented) of Derived." << std::endl; }
#endif

  virtual void method_virtual () 
  { std::cout << "Called \"method_virtual\" of Derived." << std::endl; }
  
  void method_nonvirtual () 
  { std::cout << "Called \"method_nonvirtual\" of Derived." << std::endl; }
};


int main (void)
{
  using namespace std;

  cout << endl;
  
#ifndef MAKE_BASE_ABSTRACT
  /* NOT ALLOWED (when Base is abstract) - Abstract class cannot be instantiated. */
  cout << "Creating the non-polymorphic pointer to Base instance." << endl;
  Base    *ppb = new Base;
#endif

  cout << "Creating the polymorphic pointer to Derived instance." << endl;
  Base    *ppd = new Derived;
  cout << "Creating the non-polymorphic pointer to Derived instance." << endl;
  Derived *ptr_derived = new Derived;
  
#ifndef MAKE_BASE_ABSTRACT
  cout << endl;
  cout << "Using the non-polymorphic pointer to Base instance." << endl;
  cout << endl;
  
  ppb->method_virtual();
  ppb->method_nonvirtual();
#endif
  
  cout << endl;
  cout << "Using the polymorphic pointer to Derived instance." << endl;
  cout << endl;

#ifdef MAKE_BASE_ABSTRACT
  ppd->method_purely_virtual();
#endif
  ppd->method_virtual();
  ppd->method_nonvirtual();
  
  cout << endl;
  cout << "Moving down the inheritance chain." << endl;
  cout << "Dynamic casting to Derived pointer the polymorphic pointer to Derived instance." << endl;
  cout << endl;
  
  try
  {
    Derived *ptr_p_derived_dc_derived = dynamic_cast<Derived*>(ppd);
    if ( !ptr_p_derived_dc_derived ) { cout << "NULL pointer obtained." << endl; }
    cout << "Now try to use the pointer." << endl;
    if ( ptr_p_derived_dc_derived )
    {
#ifdef MAKE_BASE_ABSTRACT
      ptr_p_derived_dc_derived->method_purely_virtual();
#endif
      ptr_p_derived_dc_derived->method_virtual();
      ptr_p_derived_dc_derived->method_nonvirtual();
    }
    else
    {
      throw runtime_error("NULL pointer cannot be dereferenced.");
    }
  }
  catch(exception& e)
  {
    cout << "Exception caught and it is saying:" << endl << e.what() << endl;
  }
  
  cout << endl;
  cout << "Using the non-polymorphic pointer to Derived instance." << endl;
  cout << endl;
  
#ifdef MAKE_BASE_ABSTRACT
  ptr_derived->method_purely_virtual();
#endif
  ptr_derived->method_virtual();
  ptr_derived->method_nonvirtual();
  
  cout << endl;
  cout << "Moving up the inheritance chain." << endl;
  cout << "Dynamic casting to Base pointer the non-polymorphic pointer to Derived instance." << endl;
  cout << endl;
  
  try
  {
    Base *ptr_np_derived_dc_base = dynamic_cast<Base*>(ptr_derived);
    if ( !ptr_np_derived_dc_base ) { cout << "NULL pointer obtained." << endl; }
    cout << "Now try to use the pointer." << endl;
    if ( ptr_np_derived_dc_base )
    {
#ifdef MAKE_BASE_ABSTRACT
      ptr_np_derived_dc_base->method_purely_virtual();
#endif
      ptr_np_derived_dc_base->method_virtual();
      ptr_np_derived_dc_base->method_nonvirtual();
    }
    else
    {
      throw runtime_error("NULL pointer cannot be dereferenced.");
    }
  }
  catch(exception& e)
  {
    cout << "Exception caught and it is saying:" << endl << e.what() << endl;
  }

#ifndef MAKE_BASE_ABSTRACT  
  cout << endl;
  cout << "Dynamic casting to Derived pointer the non-polymorphic pointer to Base instance." << endl;
  cout << endl;
  
  try
  {
    Derived *ptr_np_base_dc_derived = dynamic_cast<Derived*>(ppb);
    if ( !ptr_np_base_dc_derived ) { cout << "NULL pointer obtained." << endl; }
    cout << "Now try to use the NULL pointer." << endl;
    if ( ptr_np_base_dc_derived )
    {
      ptr_np_base_dc_derived->method_virtual();
      ptr_np_base_dc_derived->method_nonvirtual();
    }
    else
    {
      throw runtime_error("NULL pointer cannot be dereferenced.");
    }
  }
  catch(exception& e)
  {
    cout << "Exception caught and it is saying:" << endl << e.what() << endl;
  }
  
#endif

  cout << endl;

#ifndef MAKE_BASE_ABSTRACT
  cout << "Deleting the non-polymorphic pointer to Base instance." << endl;
  delete ppb;
#endif
  cout << "Deleting the polymorphic pointer to Derived instance." << endl;
  delete ppd;
  cout << "Deleting the non-polymorphic pointer to Derived instance." << endl;
  delete ptr_derived;
  
  return 0;
}