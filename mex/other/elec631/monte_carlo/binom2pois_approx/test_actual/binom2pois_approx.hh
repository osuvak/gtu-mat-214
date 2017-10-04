#ifndef BINOM2POIS_APPROX_HH_
#define BINOM2POIS_APPROX_HH_

#include <vector>

#include "results_container.hh"

void
binom2pois_approx
(
  const double                       lam ,
  const std::vector<unsigned int>  & n ,
  const unsigned int                 noMCTests ,
        std::vector<Binom2PoisResultsContainer> 
          & res
);

#endif
