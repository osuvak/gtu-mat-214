/*
 * Adapted from :
 * http://www.cplusplus.com/reference/array/array/data/
 * 
 * */


// array::data
#include <iostream>
#include <cstring>
#include <string>
#include <array>

int main ()
{
//   const std::string str = "Test string";
//   str = "Tast string";
  
  const std::string &str = "Test string";
  std::cout << str << std::endl;
  const_cast<std::string &>(str) = "Tast string";
  std::cout << str << std::endl;
  
  const char* cstr = "Test string";
  
//   *cstr = 't';
//   cstr[0] = 't';
//   cstr[1] = 'a';
//   char *cstr_other = cstr;
  
//   char *cstr_other = (char *) cstr;
//   cstr_other[0] = 't';
//   cstr_other[1] = 'a';
  
//   char *cstr_other = const_cast<char*>(cstr);
//   cstr_other[1] = 'a';
  
  const unsigned int offset = 0;
  
  std::array<char,12-offset> charray;

  std::memcpy (charray.data(),cstr,12);

  std::cout << charray.data() << '\n';

  return 0;
} 
