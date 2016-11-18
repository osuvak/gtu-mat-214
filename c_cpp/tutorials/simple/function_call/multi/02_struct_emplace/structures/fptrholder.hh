#ifndef FPTR_HOLDER_HH_
#define FPTR_HOLDER_HH_

#include <iostream>

struct FPTRHolder
{
  double (*fptr)(double);
  
  FPTRHolder ()
  {
#ifdef REPORT_EXISTENCE
    std::cout << "Creating type : \"FPTRHolder\"" << std::endl;
#endif
  }
  
  ~FPTRHolder ()
  {
#ifdef REPORT_EXISTENCE
    using namespace std;
    cout << "Destroying type : \"FPTRHolder\"" << endl;
#endif
  }
  
};

#endif
