#ifndef POIS_PMF_H_C_
#define POIS_PMF_H_C_

#include "test_actual/results_container.h"

#ifdef __cplusplus
extern "C" {
#endif

void
plugInPoissonPMFValues
(
  const double        lam ,
  const unsigned int  nSize ,
        Binom2PoisResultsContainer
          ** resPtr
);

#ifdef __cplusplus
}
#endif

#endif
