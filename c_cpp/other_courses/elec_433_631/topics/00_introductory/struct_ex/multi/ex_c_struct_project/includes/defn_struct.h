#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef USE_SEPARATE_DEFN

struct Container_
{
  char *str;
  int   num;
};

typedef struct Container_ Container;

#else

typedef struct Container_
{
  char *str;
  int   num;
}Container;

#endif

#define SIZE_STRING 256

void printContainer(const Container *input);

#ifdef __cplusplus
}
#endif