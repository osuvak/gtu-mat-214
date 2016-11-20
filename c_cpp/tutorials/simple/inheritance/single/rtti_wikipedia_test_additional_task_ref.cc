/*
 * Check if a reference can be dynamically cast to derived type.
 * If possible invoke the specified method of the derived type instance,
 * or else process the thrown exception to report a bad_cast.
 * 
 * Example adapted with comments and/or modifications from :
 * https://en.wikipedia.org/wiki/Run-time_type_information
 * */

#include <typeinfo> // For std::bad_cast
#include <iostream> // For std::cout, std::err, std::endl etc.

/*
 * Activate the following define to put another catcher that will process
 * the bad_cast exception before the intended catcher. Activation of this
 * define generates several nested warnings.
 * */

// #define PUT_CATCHER_FOR_EXCEPTION_BEFORE_BAD_CAST_CATCHER

/*
 * DO NOT MODIFY UNTIL main.
 * */

#define TEXT_CATCHER_FOR_EXCEPTION() \
  catch (const std::exception& e) \
  { \
    std::cout << "  This is the catcher for mother exceptions." << std::endl; \
    report_exception_not_of_type_B( e ); \
  }

class A 
{
public:
  // Since RTTI is included in the virtual method table there should be at least one virtual function.
  virtual ~A() { };
  
  void methodSpecificToA() { std::cout << "Method specific for A was invoked" << std::endl; };
};
 
class B : public A 
{
public:
  virtual ~B() { };
  void methodSpecificToB() { std::cout << "Method specific for B was invoked" << std::endl; };
};

void report_exception_not_of_type_B(const std::exception &E);
 
void my_function(A& my_a)
{
  try 
  {
    B& my_b = dynamic_cast<B&>(my_a); // cast will be successful only for B type objects.
    my_b.methodSpecificToB();
  }
#ifdef PUT_CATCHER_FOR_EXCEPTION_BEFORE_BAD_CAST_CATCHER
  TEXT_CATCHER_FOR_EXCEPTION()
#endif
  catch (const std::bad_cast& e) // e is read-only
  {
    std::cout << "  This is the catcher for \"bad_cast\" exceptions." << std::endl;
    report_exception_not_of_type_B( e );
  }
#ifndef PUT_CATCHER_FOR_EXCEPTION_BEFORE_BAD_CAST_CATCHER
  TEXT_CATCHER_FOR_EXCEPTION()
#endif
}

int main()
{
  A *arrayOfA[3];          // Array of pointers to base class (A)

  arrayOfA[0] = new B();   // Pointer to B object
  arrayOfA[1] = new B();   // Pointer to B object
  arrayOfA[2] = new A();   // Pointer to A object
  
  for (int i = 0; i < 3; i++) 
  {
    my_function(*arrayOfA[i]);
    delete arrayOfA[i];  // delete object to prevent memory leak
  }
  
  return 0;
} 

void report_exception_not_of_type_B(const std::exception &E) // E is read-only
{
  std::cerr << "  Exception " << E.what() << " thrown." << std::endl;
  std::cerr << "  Object is not of type B" << std::endl;
}
