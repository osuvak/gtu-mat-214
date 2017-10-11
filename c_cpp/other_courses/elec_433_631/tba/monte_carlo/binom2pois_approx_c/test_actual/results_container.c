#include "results_container.h" 

#include <stdlib.h>
#include <string.h>

Binom2PoisResultsContainer *
os_sstests_Binom2PoisResultsContainer_new
()
{
  Binom2PoisResultsContainer *newContainer
    = 
    (Binom2PoisResultsContainer *)
    malloc( 1 * sizeof(Binom2PoisResultsContainer) );
    
  os_sstests_Binom2PoisResultsContainer_initialize
    ( newContainer );
    
  return newContainer;
}

void
os_sstests_Binom2PoisResultsContainer_initialize
(
  Binom2PoisResultsContainer *container
)
{
  container->n = 0;
  container->p = 0.0;
  
  container->size = 0;
  
  container->flag_set_myRange     = false;
  container->flag_set_pmfPoisson  = false;
  container->flag_set_pmfBinomial = false;
  
  container->myRange     = NULL;
  container->pmfPoisson  = NULL;
  container->pmfBinomial = NULL;
}

void
os_sstests_Binom2PoisResultsContainer_set_myRange
(
        Binom2PoisResultsContainer * container ,
  const unsigned int               * arrayPtr ,
  const unsigned int                 size
)
{
//   unsigned int ii;
  
  if
  (
    ( container->myRange != NULL )
    &&
    ( container->flag_set_myRange == true )
  )
  {
    free( container->myRange );
    container->flag_set_myRange = false;
  }
  
  unsigned int *tmpPtr 
    = (unsigned int *) malloc( size * sizeof(unsigned int) );

/*
  for ( ii=0 ; ii<size ; ii++ )
  {
    tmpPtr[ii] = arrayPtr[ii];
  }
*/
  memcpy( tmpPtr , arrayPtr , size * sizeof(unsigned int) );

  container->myRange = tmpPtr;
  container->flag_set_myRange = true;
}

void
os_sstests_Binom2PoisResultsContainer_set_pmfPoisson
(
        Binom2PoisResultsContainer * container ,
  const double                     * arrayPtr ,
  const unsigned int                 size
)
{
  if
  (
    ( container->pmfPoisson != NULL )
    &&
    ( container->flag_set_pmfPoisson == true )
  )
  {
    free( container->pmfPoisson );
    container->flag_set_pmfPoisson = false;
  }
  
  double *tmpPtr 
    = (double *) malloc( size * sizeof(double) );

  memcpy( tmpPtr , arrayPtr , size * sizeof(double) );

  container->pmfPoisson = tmpPtr;
  container->flag_set_pmfPoisson = true;
}

void
os_sstests_Binom2PoisResultsContainer_set_pmfBinomial
(
        Binom2PoisResultsContainer * container ,
  const double                     * arrayPtr ,
  const unsigned int                 size
)
{
  if
  (
    ( container->pmfBinomial != NULL )
    &&
    ( container->flag_set_pmfBinomial == true )
  )
  {
    free( container->pmfBinomial );
    container->flag_set_pmfBinomial = false;
  }
  
  double *tmpPtr 
    = (double *) malloc( size * sizeof(double) );

  memcpy( tmpPtr , arrayPtr , size * sizeof(double) );

  container->pmfBinomial = tmpPtr;
  container->flag_set_pmfBinomial = true;
}

void
os_sstests_Binom2PoisResultsContainer_destroyArray
(
        Binom2PoisResultsContainer * arrayPtr ,
  const unsigned int                 size
)
{
  unsigned int ii;
  
  for ( ii=0 ; ii<size ; ii++ )
  {
    Binom2PoisResultsContainer *currentPtr
      = arrayPtr + ii;
      
    Binom2PoisResultsContainer * container
      = currentPtr;
      
    if
    (
      ( container->myRange != NULL )
      &&
      ( container->flag_set_myRange == true )
    )  
    {   
      free( container->myRange );
    }
  
    if
    (
      ( container->pmfPoisson != NULL )
      &&
      ( container->flag_set_pmfPoisson == true )
    )
    {
      free( container->pmfPoisson );
    }
    
    if
    (
      ( container->pmfBinomial != NULL )
      &&
      ( container->flag_set_pmfBinomial == true )
    )
    {
      free( container->pmfBinomial );
    }
    
    os_sstests_Binom2PoisResultsContainer_initialize( currentPtr );
  }
}