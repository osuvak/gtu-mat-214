#include "callbacks/callback_diode.hh" 

namespace userdefn
{
  
double
callback_diode
(
  double   input ,
  void   * userdata
)
{
  DiodeCircuit *cir = static_cast<DiodeCircuit *>(userdata);
  
  return cir->callback(input);
}
  
} // userdefn
