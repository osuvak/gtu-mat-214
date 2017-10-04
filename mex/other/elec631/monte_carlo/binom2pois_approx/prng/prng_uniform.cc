#include "prng_uniform.hh"

namespace os_prng_tests
{
namespace in_progress
{
  
unsigned PRNG_Uniform::seed = 
  std::chrono::high_resolution_clock::now().time_since_epoch().count();
  
std::default_random_engine PRNG_Uniform::generator( seed );

#ifdef USE_SHARED_PTR_FOR_DISTRIBUTION

std::shared_ptr< std::uniform_real_distribution<double> > 
PRNG_Uniform::distribution =
  std::make_shared< std::uniform_real_distribution<double> > ( 0.0 , 1.0 );

#else
  
std::uniform_real_distribution<double>
  PRNG_Uniform::distribution( 0.0 , 1.0 );
  
#endif

} // namespace in_progress
} // namespace os_prng_tests
