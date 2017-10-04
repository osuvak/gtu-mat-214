#ifndef POIS_PMF_HH_
#define POIS_PMF_HH_

#include "test_actual/results_container.hh"

void
plugInPoissonPMFValues
(
  const double lam ,
        std::vector<Binom2PoisResultsContainer> 
          & res
);

#endif
