#ifndef MY_PRNG_UNIFORM_HH_IN_PROGRESS_
#define MY_PRNG_UNIFORM_HH_IN_PROGRESS_

#include <chrono>
#include <random>
#include <memory>
#include <vector>
#include <iostream>

#define USE_SHARED_PTR_FOR_DISTRIBUTION

namespace os_prng_tests
{
namespace in_progress
{
  
class PRNG_Uniform
{
  
private:
  static unsigned seed;
  
  static std::default_random_engine generator;
  
#ifdef USE_SHARED_PTR_FOR_DISTRIBUTION
  static std::shared_ptr< std::uniform_real_distribution<double> > distribution;
#else
  static std::uniform_real_distribution<double> distribution;
#endif
  
private:
  PRNG_Uniform() {}
  PRNG_Uniform(const PRNG_Uniform &arg) {}
  PRNG_Uniform(PRNG_Uniform &arg) {}
  ~PRNG_Uniform() {}
  
public:
  
  static
  std::vector<double> *
  getNumbers
  (unsigned int howMany)
  {
    using namespace std;
    
    vector<double> *current = new vector<double> ();
    current->clear();
    for ( unsigned int ii = 0 ; ii < howMany ; ii++ )
    {
#ifdef USE_SHARED_PTR_FOR_DISTRIBUTION
      (*current).push_back( (*distribution)(generator) );
#else
      (*current).push_back( distribution(generator) );
#endif
    }
    
    return current;
  }
  
  static
  void
  getNumbers
  (
    std::vector<double> & current , 
    unsigned int          howMany
  )
  {
    using namespace std;
    
    current.clear();
    for ( unsigned int ii = 0 ; ii < howMany ; ii++ )
    {
#ifdef USE_SHARED_PTR_FOR_DISTRIBUTION
      current.push_back( (*distribution)(generator) );
#else
      current.push_back( distribution(generator) );
#endif
    }
  }
  
};

} // namespace in_progress
} // namespace os_prng_tests

#endif
