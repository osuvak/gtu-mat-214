#include "functions_objective.h"

double
func_bias_diode
(
  double VD
)
{
  double R   = 1e3;
  double IS  = 3e-15;
  double VIN = 3.3;
  double VT  = 25e-3;
  
  double m;
  m = VT * log( ( VIN - VD ) / ( R * IS ) ) - VD;
  
  return m;
}

double
func_bias_diode_with_exp
(
  double VD
)
{
  double R   = 1e3;
  double IS  = 3e-15;
  double VIN = 3.3;
  double VT  = 25e-3;
  
  double m;
  m = VIN - VD - R * IS * exp(VD/VT);
  
  return m;
}