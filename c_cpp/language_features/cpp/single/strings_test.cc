#include<iostream>
#include<cstdio>
#include<string>

int
main
(void)
{
  using namespace std;
  
  string A("MAT 214 Class");
  
  cout << "Printing std::string    : " << A << endl;
  printf( "Printing C-style string : %s\n" , A.c_str() );
  
  return 0;
}
