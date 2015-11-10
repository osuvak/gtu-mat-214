#ifndef UTILITIES_GENERAL_HH_
#define UTILITIES_GENERAL_HH_

namespace nummethods
{

template <typename T> 
int signum(T val) 
{
  return (T(0) < val) - (val < T(0));
}

} // nummethods

#endif
