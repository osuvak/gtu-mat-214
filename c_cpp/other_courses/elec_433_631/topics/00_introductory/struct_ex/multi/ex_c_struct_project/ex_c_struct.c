#define USE_SEPARATE_DEFN
#include "defn_struct.h"

int main (void)
{
  Container myContainer1;
  
//   Container *ptrMyContainer2 = (Container *) malloc( sizeof( Container ) );
  Container *ptrMyContainer2 = (Container *) calloc( 1 , sizeof( Container ) );
  
  myContainer1.num = 5;
  myContainer1.str = (char *) calloc( SIZE_STRING , sizeof(char) );
  
  strcpy( myContainer1.str , "Onder" );
  printContainer( &myContainer1 );
  
  strcat( myContainer1.str , "Onder" );
  printContainer( &myContainer1 );
  
  ptrMyContainer2->num = 10;
  ptrMyContainer2->str = (char *) calloc( SIZE_STRING , sizeof(char) );
  
  strcpy( ptrMyContainer2->str , "Emre" );
//   printContainer( ptrMyContainer2 );
  printContainer( &(*ptrMyContainer2) );
  
  free( myContainer1.str );
  free( ptrMyContainer2->str );
  
  free( ptrMyContainer2 );
  
  return 0;
}