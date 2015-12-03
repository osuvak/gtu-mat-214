#ifndef FUNCTIONS_OBJECTIVE_H_
#define FUNCTIONS_OBJECTIVE_H_

#include<math.h>

#ifdef __cplusplus
extern "C" {
#endif

double
func_bias_diode
(
  double VD
);

double
func_bias_diode_with_exp
(
  double VD
);

#ifdef __cplusplus
}
#endif

#endif
