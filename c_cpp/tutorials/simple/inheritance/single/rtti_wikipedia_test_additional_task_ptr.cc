/*
 * Check if a pointer can be dynamically cast to derived pointer type.
 * If possible invoke the specified method of the derived type instance,
 * or else process the thrown exception to report a mother exception.
 * bad_cast catcher can never intervene, since the type of thrown exception
 * cannot be cast to bad_cast.
 * 
 * A switch enables the use of shared pointers in main for garbage collection.
 * 
 * Example adapted with comments and/or modifications from :
 * https://en.wikipedia.org/wiki/Run-time_type_information
 * */

#include <typeinfo> // For std::bad_cast
#include <memory>
#include <stdexcept>
#include <iostream> // For std::cout, std::err, std::endl etc.
#include <vector>

/*
 * Activate the following define to use shared pointers for the management
 * of the raw pointers to A. Deleting therefore is not necessary and
 * garbage collection is automatic. A better implementation would refrain from
 * exposing raw pointers altogether.
 * */

#define USE_SHARED_PTR

/*
 * Activate the following define to put another catcher that will process
 * the bad_cast exception before the intended catcher. Activation of this
 * define generates several nested warnings.
 * 
 * EDIT : In this implementation bad_cast can never intervene.
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
  A () { std::cout << "Called constructor for A." << std::endl; }
  
  // Since RTTI is included in the virtual method table there should be at least one virtual function.
  virtual ~A() { std::cout << "Called destructor for A." << std::endl; };
  
  void methodSpecificToA() { std::cout << "Method specific for A was invoked" << std::endl; };
};
 
class B : public A 
{
public:
  B () { std::cout << "Called constructor for B." << std::endl; }
  virtual ~B() { std::cout << "Called destructor for B." << std::endl; };
  
  void methodSpecificToB() { std::cout << "Method specific for B was invoked" << std::endl; };
};

void report_exception_not_of_type_B(const std::exception &E);
 
void my_function(A* ptr_a)
{
  try 
  {
    B* ptr_b = dynamic_cast<B*>(ptr_a); // cast will be successful only for B type objects.
    if ( ptr_b )
      ptr_b->methodSpecificToB();
    else
      throw std::runtime_error("\"Encountered a NULL pointer, manually throwing exception.\"");
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

#ifndef USE_SHARED_PTR

int main (void)
{
  using namespace std;
  
  vector<A *> vec;
  
  vec.push_back( new B() );
  vec.push_back( new B() );
  vec.push_back( new A() );
  
  for (unsigned int ii = 0 ; ii < vec.size() ; ii++ ) 
  {
    my_function( vec[ii] );
  }
  
  for (unsigned int ii = 0 ; ii < vec.size() ; ii++ ) 
  {
    delete vec[ii];
  }
  
  return 0;
} 

#else

int main (void)
{
  using namespace std;

  cout << endl << "Using shared pointers for the management of raw pointers." << endl << endl;
  
  vector< shared_ptr<A> > vec;
  
  vec.push_back( shared_ptr<A>( new B() ) );
  vec.push_back( shared_ptr<A>( new B() ) );
  vec.push_back( shared_ptr<A>( new A() ) );
  
  for (unsigned int ii = 0 ; ii < vec.size() ; ii++ ) 
  {
    my_function( vec[ii].get() ); // sending raw pointer as argument
  }

//   Should not be deleting when using shared pointers.
/*  
  for (unsigned int ii = 0 ; ii < vec.size() ; ii++ ) 
  {
    delete vec[ii];
  }
*/

  return 0;
}

#endif

void report_exception_not_of_type_B(const std::exception &E) // E is read-only
{
  std::cerr << "  Exception " << E.what() << " thrown." << std::endl;
  std::cerr << "  Object is not of type B" << std::endl;
}
