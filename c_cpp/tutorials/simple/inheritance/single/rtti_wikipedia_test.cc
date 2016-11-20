/*
 * Example with additional comments and/or modifications taken from :
 * https://en.wikipedia.org/wiki/Run-time_type_information
 * */

#include <iostream>    // cout
#include <typeinfo>    // for 'typeid'

class Person {
public:
  virtual ~Person() {}
};

class Employee : public Person {
};

int main() 
{
  Person person;
  Employee employee;
  
  Person* ptr = &employee;
  Person& ref = employee;
  
  // The string returned by typeid::name is implementation-defined (name-mangling)
  
  std::cout << typeid(person).name() << std::endl;   // Person (statically known at compile-time)
  std::cout << typeid(employee).name() << std::endl; // Employee (statically known at compile-time)
  std::cout << typeid(ptr).name() << std::endl;      // Person* (statically known at compile-time)
  std::cout << typeid(*ptr).name() << std::endl;     // Employee (looked up dynamically at run-time
                                                     //           because it is the dereference of a
                                                     //           pointer to a polymorphic class)
  std::cout << typeid(ref).name() << std::endl;      // Employee (references can also be polymorphic)

  Person* p = nullptr;
  try 
  {
    typeid(*p); // not undefined behavior; throws std::bad_typeid
  }
  catch ( std::exception &E )
  {
    std::cout << "An exception is caught and it is saying :" << std::endl
      << "  " << E.what() << std::endl;
  }
  catch (...) 
  {}

  Person& pRef = *p; // Undefined behavior: dereferencing null
  typeid(pRef);      // does not meet requirements to throw std::bad_typeid (issued warning)
                     // because the expression for typeid is not the result
                     // of applying the unary * operator
}
 
