#include <iostream>
#include <cassert>
#include <cstdio>
#include <vector>

void
addVectors
(
        std::vector<double> &result ,
  const double               alpha ,
  const std::vector<double> &va ,
  const double               beta ,
  const std::vector<double> &vb 
);

void
printVector
(
  std::vector<double> &v
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
  
  assert( size_a == size_b );
  
  std::vector<double> veca , vecb , result;
  
  for ( unsigned int i=0 ; i<size_a ; i++ )
  {
    veca.push_back( va[i] );
    vecb.push_back( vb[i] );
  }
  
  addVectors( result , alpha , veca , beta , vecb );
  printVector(result);
  
  return 0;
}

void
addVectors
(
        std::vector<double> &result ,
  const double               alpha ,
  const std::vector<double> &va ,
  const double               beta ,
  const std::vector<double> &vb 
)
{
  double temp;
  
  result.clear();
  for ( unsigned int i=0 ; i<va.size() ; i++ )
  {
    temp = alpha * va[i] + beta * vb[i];
    result.push_back(temp);
  }
}

void
printVector
(
  std::vector<double> &v
)
{
  unsigned int i;
  
  printf("\nPrinting vector:\n");
  
  for ( i=0 ; i<v.size() ; i++ )
    printf( "  %.6e\n" , v[i] );
  
  printf("\n");
}