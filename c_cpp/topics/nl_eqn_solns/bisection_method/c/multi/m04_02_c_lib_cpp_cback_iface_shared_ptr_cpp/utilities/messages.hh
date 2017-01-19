#ifndef MESSAGES_HH_
#define MESSAGES_HH_

#include <iostream>
#include <string>

namespace my_cpp_utilities
{
  
class MessageFormulator
{
private:
  
  MessageFormulator () {}
  ~MessageFormulator() {}
  
public:
  
  static
  void
  message_constructor
  (
    std::string classname
  )
  {
    using namespace std;
    
    cout << "Constructor called for " << classname << endl;
  }
  
  static
  void
  message_destructor
  (
    std::string classname
  )
  {
    using namespace std;
    
    cout << "Destructor called for " << classname << endl;
  }
};

class TalkToggler
{
private:
  
  TalkToggler  () {}
  ~TalkToggler () {}
  
private:
  
  static bool flag_talks_;
  
public:
  
  static
  void
  set_flag
  ()
  {
    flag_talks_ = true;
  }
  
  static
  void
  unset_flag
  ()
  {
    flag_talks_ = false;
  }
  
  static
  bool
  get_flag
  ()
  {
    return flag_talks_;
  }
};

} // namespace my_cpp_utilities

#endif