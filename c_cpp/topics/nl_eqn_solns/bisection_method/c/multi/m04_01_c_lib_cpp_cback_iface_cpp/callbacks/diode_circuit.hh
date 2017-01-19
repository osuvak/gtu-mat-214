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
  
  static
  double
  s_callback
  (
    double   input ,
    void   * userdata
  )
  {
    DiodeCircuit *cir = static_cast<DiodeCircuit *>(userdata);
  
    return cir->callback(input);
  }
  
  virtual
  double
  callback
  (
    double VD
  ) = 0;
};
  
} // userdefn

#endif
