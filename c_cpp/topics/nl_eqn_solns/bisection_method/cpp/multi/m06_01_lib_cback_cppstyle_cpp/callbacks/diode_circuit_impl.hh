#ifndef DIODE_CIRCUIT_IMPL_HH_
#define DIODE_CIRCUIT_IMPL_HH_

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
  
class DiodeCircuitWithLog
:
public DiodeCircuit
{
public:
  
  DiodeCircuitWithLog
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
  ~DiodeCircuitWithLog() {}
  
  virtual
  double
  callback
  (
    double VD
  )
  {
    return VT_ * log( ( VIN_ - VD ) / ( R_ * IS_ ) ) - VD;
  }
};

} // userdefn

#endif
