#include<stdio.h> 

#include "functions_objective.hh"
#include "bisection_options.hh"
#include "bisection_internals.hh"
#include "bisection_core.hh"

int
main
(void)
{
  BisectionOptions  opt_log , opt_exp;
  SolnIterates      soln;
  SolnLList        *cptr;
  
  int flag;
  unsigned int cnt;
  
  opt_log.fptr = func_bias_diode;
  opt_log.left  = 0.65;
  opt_log.right = 0.9;
  opt_log.abstol = 1.0e-30;
  opt_log.reltol = 1.0e-3;
  opt_log.ftol   = 1.0e-5;
  opt_log.maxIter = 50;
  
  opt_exp = opt_log;
  opt_exp.fptr = func_bias_diode_with_exp;
  
  // initialize soln
  inialize(&soln);
  
  // run
  flag = bisection_method( &opt_log , &soln );
  printf("\nNo of iterations (length of soln array) : %d\n",size(&soln));
  
  if ( (flag == 0) || (flag == -2) )
  {
    if (size(&soln) > 0)
    {
      printf("\nValues and Function Values\n\n");
      cnt = 0;
      cptr = soln.llist;
      while ( cptr != NULL )
      {
        cnt++;
        printf
        ( "Iter %d : %.16e %.16e\n" , cnt , 
          cptr->point.val , cptr->point.fval
        );
        cptr = cptr->next;
      }
      
      printf("\nErrors in Values and Function Values\n\n");
      cnt = 0;
      cptr = soln.llist;
      while ( cptr != NULL )
      {
        cnt++;
        printf
        ( "Iter %d : %.16e %.16e\n" , cnt , 
          cptr->err_x , cptr->err_f
        );
        cptr = cptr->next;
      }
    }
  }
  
  // destroy soln
  destroy(&soln);
  
  return 0;
}
