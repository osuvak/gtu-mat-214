#ifndef BINOM2POIS_RESULTS_CONTAINER_H_C_
#define BINOM2POIS_RESULTS_CONTAINER_H_C_

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef
struct Binom2PoisResultsContainer_
{
  unsigned int n;
  double p;
  
  unsigned int size;
  
  bool flag_set_myRange;
  bool flag_set_pmfPoisson;
  bool flag_set_pmfBinomial;
  
  unsigned int *myRange;
  double *pmfPoisson;
  double *pmfBinomial;
}
Binom2PoisResultsContainer;

Binom2PoisResultsContainer *
os_sstests_Binom2PoisResultsContainer_new
();

void
os_sstests_Binom2PoisResultsContainer_initialize
(
  Binom2PoisResultsContainer *container
);

void
os_sstests_Binom2PoisResultsContainer_set_myRange
(
        Binom2PoisResultsContainer * container ,
  const unsigned int               * arrayPtr ,
  const unsigned int                 size
);

void
os_sstests_Binom2PoisResultsContainer_set_pmfPoisson
(
        Binom2PoisResultsContainer * container ,
  const double                     * arrayPtr ,
  const unsigned int                 size
);

void
os_sstests_Binom2PoisResultsContainer_set_pmfBinomial
(
        Binom2PoisResultsContainer * container ,
  const double                     * arrayPtr ,
  const unsigned int                 size
);

void
os_sstests_Binom2PoisResultsContainer_destroyArray
(
        Binom2PoisResultsContainer * arrayPtr ,
  const unsigned int                 size
);

#ifdef __cplusplus
}
#endif

#endif
