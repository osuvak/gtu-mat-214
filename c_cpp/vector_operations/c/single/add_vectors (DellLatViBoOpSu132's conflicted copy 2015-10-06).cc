#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int
addVectors
(
  const unsigned int     size ,
                 double *result ,
  const          double  alpha ,
  const          double *veca ,
  const          double  beta ,
  const          double *vecb
);

void
printVector
(
  unsigned int     size ,
           double *v
);

int
main
(void)
{
  double alpha=1.0 , beta=1.0;
  
  double va[] = { 0.5 , 1.0 , 1.5 };
  double vb[] = { 0.7 , 1.7 , 2.7 };
  
  unsigned int size_a = sizeof(va) / sizeof(double);
  unsigned int size_b = sizeof(vb) / sizeof(double);
  
  printf( "Size of va: %d\n" , size_a );
  printf( "Size of vb: %d\n" , size_b );
  
  assert( size_a == size_b );
  
  double *result = (double *) calloc( size_a , sizeof(double) );
  
  addVectors( size_a , result , alpha , va , beta , vb );
  printVector( size_a , result );
  
  free(result);
  
  return 0;
}

int
addVectors
(
  const unsigned int     size ,
                 double *result ,
  const          double  alpha ,
  const          double *veca ,
  const          double  beta ,
  const          double *vecb
)
{
  unsigned int i;
  
  for ( i=0 ; i<size ; i++ )
  {
    result[i] = alpha * veca[i] + beta * vecb[i];
  }
  
  return 0;
}

void
printVector
(
  unsigned int     size ,
           double *v
)
{
  unsigned int i;
  
  printf("\nPrinting vector:\n");
  
  for ( i=0 ; i<size ; i++ )
    printf( "  %.6e\n" , v[i] );
  
  printf("\n");
}