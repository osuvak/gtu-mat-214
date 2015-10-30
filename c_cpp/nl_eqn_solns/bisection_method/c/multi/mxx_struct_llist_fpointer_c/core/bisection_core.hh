#ifndef BISECTION_CORE_HH_
#define BISECTION_CORE_HH_

#include "structures/bisection_options.hh"
#include "structures/bisection_internals.hh"
#include "utilities/utilities_general.hh"

#include<math.h>
#include<stdio.h>

int
bisection_method
(
  const BisectionOptions * ptr_opt ,
        SolnIterates     * soln
);

#endif
