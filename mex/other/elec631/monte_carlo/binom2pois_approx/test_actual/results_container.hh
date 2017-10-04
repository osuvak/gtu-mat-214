#ifndef BINOM2POIS_RESULTS_CONTAINER_HH_
#define BINOM2POIS_RESULTS_CONTAINER_HH_

#include <vector>

struct Binom2PoisResultsContainer
{
  Binom2PoisResultsContainer() {}
  ~Binom2PoisResultsContainer() {}
  
  double n;
  double p;
  
  std::vector<unsigned int> myRange;
  std::vector<double> pmfPoisson;
  std::vector<double> pmfBinomial;
};

#endif
