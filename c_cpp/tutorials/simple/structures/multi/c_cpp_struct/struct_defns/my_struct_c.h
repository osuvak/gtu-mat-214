#ifndef MY_STRUCT_C_H_
#define MY_STRUCT_C_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MyCType_DefnEncaps_
{
  int    no_int;
  double no_double;
  
  struct MyCType_DefnEncaps_ *ptr_another;
  
#ifdef CAUSE_COMPILATION_ERROR_C_STRUCT_TYPE_NOT_YET_DEFINED
  MyCType_DefnEncaps *ptr_yet_another;
#endif
#ifdef CAUSE_COMPILATION_ERROR_C_STRUCT_INF_LOOP
  struct MyCType_DefnEncaps_ inf_loop;
#endif
  
}MyCType_DefnEncaps;

struct MyCType_DefnNoEncaps_
{
  int    no_int;
  double no_double;
};

#ifndef DO_NOT_TYPEDEF_C_STRUCT
typedef struct MyCType_DefnNoEncaps_ MyCType_DefnNoEncaps;
#endif

#ifdef __cplusplus
}
#endif

#endif
