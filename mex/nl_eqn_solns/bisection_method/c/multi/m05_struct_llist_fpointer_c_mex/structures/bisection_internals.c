#include "bisection_internals.h" 

void
inialize
(
  SolnIterates *item
)
{
  (*item).llist = NULL;
  (*item).size  = 0;
}

void
destroy
(
  SolnIterates *item
)
{
  SolnLList *cptr , *tmp;
  
  if ( item->size <= 0 )
    return;
  
  cptr = item->llist;
  while (cptr != NULL)
  {
    // set prev. ptr to NULL
    cptr->prev = NULL;
    // will jump to the next at the end of iter.
    tmp = cptr->next;
    // destroy current
    free(cptr);
    
    // now jump
    cptr = tmp;
    
    // adjust item
    item->llist = cptr;
    (item->size)--;
  }
}

unsigned int
size
(
  const SolnIterates *item
)
{
  return item->size;
}

void
append
(
  SolnIterates *item ,
  PointInfo     point ,
  double        err_x ,
  double        err_f
)
{
  SolnLList *tmp , *end;
  
  // allocate space for new
  tmp = (SolnLList *) malloc(sizeof(SolnLList));
  // set data
  tmp->point = point;
  tmp->err_x = err_x;
  tmp->err_f = err_f;
  // set next (NULL)
  tmp->next = NULL;
  
  // traverse to the end of the list
  end = item->llist;
  if ( end != NULL )
  {
    while (end->next != NULL)
      end = end->next;
  }
  
  // connect tmp
  if ( end != NULL )
    end->next = tmp;
  tmp->prev = end;
  
  // update llist and size
  if ( item->size <= 0 ) // if the list has just been initialized
    item->llist = tmp;
  (item->size)++;
}

const SolnLList *
getLast
(
  SolnIterates *item
)
{
  SolnLList *end;
  
  // traverse to the end of the list
  end = item->llist;
  if ( end != NULL )
  {
    while (end->next != NULL)
      end = end->next;
  }
  
  return end;
}