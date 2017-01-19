#ifndef DIODE_CIRCUIT_HH_
#define DIODE_CIRCUIT_HH_

#include<cmath>
#include<memory>

#include "utilities/messages.hh"

namespace userdefn
{
  
class DiodeCircuit
{
protected:
  double R_;
  double IS_;
  double VIN_;
  double VT_;
  
public:
  
  DiodeCircuit
  (
    double R ,
    double IS ,
    double VIN ,
    double VT
  )
  :
  R_  (R) ,
  IS_ (IS) ,
  VIN_(VIN) ,
  VT_ (VT)
  {
    using namespace my_cpp_utilities;
    
    if ( TalkToggler::get_flag() )
      MessageFormulator::message_constructor( "DiodeCircuit" );
  }
  
  virtual
  ~DiodeCircuit() 
  {
    using namespace my_cpp_utilities;
    
    if ( TalkToggler::get_flag() )
      MessageFormulator::message_destructor( "DiodeCircuit" );
  }
  
  static
  double
  s_callback
  (
    double   input ,
    void   * userdata
  )
  {
//     DiodeCircuit *cir = static_cast<DiodeCircuit *>(userdata);
//     return cir->callback(input);
    
    using namespace std;
    
    shared_ptr<DiodeCircuit> *cir = static_cast< shared_ptr<DiodeCircuit> * >(userdata);
    return (*cir)->callback(input);
  }
  
  virtual
  double
  callback
  (
    double VD
  ) const = 0;
};
  
} // userdefn

#endif
