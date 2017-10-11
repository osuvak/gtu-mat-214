#ifndef BINOM2POIS_APPROX_H_C_
#define BINOM2POIS_APPROX_H_C_

#include "results_container.h"

#ifdef __cplusplus
extern "C" {
#endif

void
os_sstests_binom2pois_approx
(
  const double          lam ,
  const unsigned int  * n ,
  const unsigned int    nSize ,
  const unsigned int    noMCTests ,
        Binom2PoisResultsContainer
          ** res
);

#ifdef __cplusplus
}
#endif

#endif
