#ifndef BISECTION_CORE_H_
#define BISECTION_CORE_H_

#include "structures/bisection_options.h"
#include "structures/bisection_internals.h"
#include "utilities/utilities_general.h"

#include<math.h>
#include<stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

int
bisection_method
(
  const BisectionOptions * ptr_opt ,
        SolnIterates     * soln
);

#ifdef __cplusplus
}
#endif

#endif
