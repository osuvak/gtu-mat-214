#ifndef MY_CLASSES_HH_
#define MY_CLASSES_HH_

#include <vector>

class IntegerHolder
{
private:
  std::vector<int> vec_;
  int number_;
  
public:
  IntegerHolder( int init = 0 ) : number_(init) { vec_.push_back(number_); }
  ~IntegerHolder() {}
  
  const std::vector<int> &
  get_vector
  ()
  { return vec_; }
  
  void 
  append
  ( unsigned int no_times = 5 )
  {
    for ( unsigned int ii = 0 ; ii < no_times ; ii++ )
    {
      vec_.push_back( --number_ );
    }
  }
};

#endif
