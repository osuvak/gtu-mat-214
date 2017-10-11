#ifndef MY_PRNG_UNIFORM_H_C_IN_PROGRESS_
#define MY_PRNG_UNIFORM_H_C_IN_PROGRESS_

#ifdef __cplusplus
extern "C" {
#endif

void
os_prng_initRNG
();

double *
os_prng_getUniformlyDistRV
(
  const unsigned int   howMany
);
  
#ifdef __cplusplus
}
#endif


#endif
