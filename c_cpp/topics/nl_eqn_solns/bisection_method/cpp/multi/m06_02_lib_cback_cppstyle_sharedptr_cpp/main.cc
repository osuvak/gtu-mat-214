#include<iostream>
#include<cstdio>
#include<cassert>
#include<vector>
#include<memory>

#include "diode_circuit_impl.hh"

#include "bisection_internals.hh"
#include "bisection.hh"

#include "defines.hh"

int
main
(void)
{
  using namespace std;
  
  using namespace userdefn;
  using namespace nummethods;
  
  // variables for the diode circuit
  double R   = 1e3;
  double IS  = 3e-15;
  double VIN = 3.3;
  double VT  = 25e-3;
  
// #ifdef USE_SHARED_PTR_INSIDE_LIB
  vector< shared_ptr<CallbacksFather> > vec_cback;
// #else
//   vector<CallbacksFather *> vec_cback;
// #endif
  
  // polymorphic pointers declared and initialized
  vec_cback.push_back( shared_ptr<CallbacksFather>( new DiodeCircuitWithExp( R , IS , VIN , VT ) ) );
  vec_cback.push_back( shared_ptr<CallbacksFather>( new DiodeCircuitWithLog( R , IS , VIN , VT ) ) );
  
  // choose 0 or 1
  unsigned int index = 1;
#ifdef USE_SHARED_PTR_INSIDE_LIB
  shared_ptr<CallbacksFather> current = vec_cback[index];
  assert( current.get() == vec_cback[index].get() );
#else
  CallbacksFather *current = vec_cback[index].get();
#endif
  
  // initialize solver
  BisectionMethod B
    ( 
      current ,
      0.68 , 1.0 , 1e-30 , 1e-3 , 1e-5 
    );
    
#ifdef USE_SHARED_PTR_INSIDE_LIB
  assert( current.get() == ( B.getPointer() ).get() );
#else
  assert( current == B.getPointer() );
#endif
    
  // compute
  B.compute();
  
  cout << endl << "Flag Value : " << B.getFlag() << endl;
  
  // report
  if ( -1 != B.getFlag() )
  {
    const std::list<SolnItem> &llist = B.getList();
    int cnt;
    
    printf("\nValues and Function Values\n\n");
    cnt = 0;
    for 
      (
        std::list<SolnItem>::const_iterator 
          it = llist.begin() ; 
        it != llist.end() ; 
        ++it
      )
    {
      cnt++;
      printf
        ( "Iter %d : %.16e %.16e\n" , cnt , 
          (*it).point.val , (*it).point.fval
        );
    }
    
    printf("\nErrors in Values and Function Values\n\n");
    cnt = 0;
    for 
      (
        std::list<SolnItem>::const_iterator 
          it = llist.begin() ; 
        it != llist.end() ; 
        ++it
      )
    {
      cnt++;
      printf
        ( "Iter %d : %.16e %.16e\n" , cnt , 
          (*it).err_x , (*it).err_f
        );
    }
  }
    
  // destroy allocated space
//   for ( unsigned ii=0 ; ii < vec_cback.size() ; ii++ )
//   {
//     delete vec_cback[ii];
//   }
  
  return 0;
}