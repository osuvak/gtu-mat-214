#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define USE_CALLOC_FOR_NAMES

typedef struct MyContainer_
{
#ifdef USE_CALLOC_FOR_NAMES
  char *name;
#else
  char name[64];
#endif
  int   index;
}MyContainer;

int main(void)
{
  const unsigned int size_of_list = 4;
  unsigned int ii;
  
  MyContainer *list;
  list = (MyContainer *) malloc( size_of_list * sizeof(MyContainer) );
  
  for ( ii = 0 ; ii < size_of_list ; ii++ )
  {
    list[ii].index = ii + 1;
    switch (ii+1)
    {
      case 1 :
#ifdef USE_CALLOC_FOR_NAMES
          list[ii].name = (char *) calloc( 1 + strlen("Sukran Gunduz") , sizeof(char) );
#endif
          strcpy( list[ii].name , "Sukran Gunduz" );
          break;
      case 2 :
#ifdef USE_CALLOC_FOR_NAMES
          list[ii].name = (char *) calloc( 1 + strlen("Nur Kucuk") , sizeof(char) );
#endif
          strcpy( list[ii].name , "Nur Kucuk" );
          break;
      case 3 :
#ifdef USE_CALLOC_FOR_NAMES
          list[ii].name = (char *) calloc( 1 + strlen("Hande Uygurlu") , sizeof(char) );
#endif
          strcpy( list[ii].name , "Hande Uygurlu" );
          break;
      case 4 :
#ifdef USE_CALLOC_FOR_NAMES
          list[ii].name = (char *) calloc( 1 + strlen("Onder Suvak") , sizeof(char) );
#endif
          strcpy( list[ii].name , "Onder Suvak" );
          break;
      default :
          break;
    }
  }
  
  printf( "\nReport : \n\n" );
  for ( ii = 0 ; ii < size_of_list ; ii++ )
  {
    printf( "  Index : %d  Name : %s\n" , list[ii].index , list[ii].name );
  }
  printf( "\n" );
  
#ifdef USE_CALLOC_FOR_NAMES
  for ( ii = 0 ; ii < size_of_list ; ii++ )
  {
    free( list[ii].name );
  }
#endif
  
  free( list );
  
  return 0;
}
