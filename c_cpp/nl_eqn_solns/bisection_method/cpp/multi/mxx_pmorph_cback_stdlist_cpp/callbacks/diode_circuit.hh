#ifndef DIODE_CIRCUIT_HH_
#define DIODE_CIRCUIT_HH_

#include<cmath>

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
  {}
  
  virtual
  ~DiodeCircuit() {}
  
  virtual
  double
  callback
  (
    double VD
  ) = 0;
};
  
} // userdefn

#endif
