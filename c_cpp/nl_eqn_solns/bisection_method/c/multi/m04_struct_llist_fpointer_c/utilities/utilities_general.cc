#include "utilities_general.hh" 

int
signum
(
  double x
)
{
  return (x > 0.0) ? 1 : ((x < 0.0) ? -1 : 0);
}