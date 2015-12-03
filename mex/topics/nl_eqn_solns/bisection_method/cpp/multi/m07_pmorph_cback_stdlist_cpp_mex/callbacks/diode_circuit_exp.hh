#ifndef DIODE_CIRCUIT_EXP_HH_
#define DIODE_CIRCUIT_EXP_HH_

#include "callbacks/diode_circuit.hh"

namespace userdefn
{
  
class DiodeCircuitWithExp
:
public DiodeCircuit
{
public:
  
  DiodeCircuitWithExp
  (
    double R ,
    double IS ,
    double VIN ,
    double VT
  )
  :
  DiodeCircuit(R,IS,VIN,VT)
  {}
  
  virtual
  ~DiodeCircuitWithExp() {}
  
  virtual
  double
  callback
  (
    double VD
  )
  {
    return VIN_ - VD - R_ * IS_ * exp( VD / VT_ );
  }
};
  
} // userdefn

#endif
