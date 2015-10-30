#ifndef BISECTION_INTERNALS_HH_
#define BISECTION_INTERNALS_HH_

#include<stdlib.h>

typedef struct 
PointInfo_
{
  double val , fval;
  int    sign;
}PointInfo;

typedef struct 
IntervalInfo_
{
  PointInfo left , mid , right;
}IntervalInfo;

typedef struct
SolnLList_
{
  PointInfo point;
  double    err_x , err_f;
  
  SolnLList_ *next;
  SolnLList_ *prev;
}SolnLList;

// SolnIterates structure and its "methods"
typedef struct
SolnIterates_
{
  SolnLList    *llist;
  unsigned int  size;
}SolnIterates;

void
inialize
(
  SolnIterates *item
);

void
destroy
(
  SolnIterates *item
);

unsigned int
size
(
  const SolnIterates *item
);

void
append
(
  SolnIterates *item ,
  PointInfo     point ,
  double        err_x ,
  double        err_f
);

const SolnLList *
getLast
(
  SolnIterates *item
);

#endif
