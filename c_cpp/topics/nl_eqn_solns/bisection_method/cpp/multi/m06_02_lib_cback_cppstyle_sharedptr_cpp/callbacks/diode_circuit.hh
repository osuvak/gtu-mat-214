#ifndef DIODE_CIRCUIT_HH_
#define DIODE_CIRCUIT_HH_

#include<cmath>

#include "core/bisection.hh"

namespace userdefn
{
  
class DiodeCircuit
:
public nummethods::CallbacksFather
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
  {}
  
  virtual
  ~DiodeCircuit() {}
  
};
  
} // userdefn

#endif
