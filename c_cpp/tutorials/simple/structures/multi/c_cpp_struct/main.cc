#include <iostream> 
#include <cstdio>

/*
 * ACTIVATE EXACTLY ONE OF THE BELOW DEFINES 
 * TO ENCOUNTER A PARTICULAR COMPILATION ERROR.
*/

// #define CAUSE_COMPILATION_ERROR_C_STRUCT_TYPE_NOT_YET_DEFINED
// #define CAUSE_COMPILATION_ERROR_C_STRUCT_INF_LOOP
// #define CAUSE_COMPILATION_ERROR_C_STRUCT_IS_UNTYPEDEFD

/*
 * DO NOT MODIFY ANY OF THE BELOW UNTIL main
*/

#ifdef CAUSE_COMPILATION_ERROR_C_STRUCT_IS_UNTYPEDEFD
#define DO_NOT_TYPEDEF_C_STRUCT
#endif

#include "my_struct_c.h"
#include "my_struct_cpp.hh" 

int main (void)
{
  using namespace std;
  
/* 
 * Will cause compilation error if defined CAUSE_COMPILATION_ERROR_C_STRUCT_IS_UNTYPEDEFD
 * */  
  MyCType_DefnNoEncaps A;
  
/*
 * Always OK
 * */  
  struct MyCType_DefnNoEncaps_ B;
  
/*
 * A CPP struct is almost like a CPP class.
 * */
  MyCPPType C(5);
  cout << "Number : " << C.get_number() << endl;
  C.set_number(12);
  cout << "Number : " << C.get_number() << endl;
  
  return 0;
}
