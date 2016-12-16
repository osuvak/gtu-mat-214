#include <iostream>
#include <cstdio>
#include <string>

int main(void)
{
  using namespace std;
  
  int ilist[] = { 16 , 19 , -45 , 80 };
  unsigned int size_total = sizeof(ilist) / sizeof(int);
  
  cout << "Size of ilist : " << size_total <<  endl;
  
  cout << "\n" << "Report : " << endl << endl;
  
//   for ( unsigned int ii = 0 ; ii < size_total ; ii++ )
//   {
//     printf( "  Index : %6d  Number : %6d\n" , ii , ilist[ii] );
//   }
  
//   for ( unsigned int ii = 0 ; ii < size_total ; ii++ )
//   {
//     int *iptr = ilist;
//     printf( "  Index : %6d  Number : %6d\n" , ii , *(iptr + ii) );
//   }
  
  int *iptr = ilist;
  for ( unsigned int ii = 0 ; ii < size_total ; ii++ )
  {
//     printf( "  Index : %6d  Number : %6d\n" , ii , *(iptr++) );
    printf( "  Index : %6d  Number : %6d\n" , ii , (*(iptr++))-- );
    printf( "  Index : %6d  Number : %6d\n" , ii , *(iptr - 1) );
  }
  
  cout << '\n' ;
  
  return 0;
}
