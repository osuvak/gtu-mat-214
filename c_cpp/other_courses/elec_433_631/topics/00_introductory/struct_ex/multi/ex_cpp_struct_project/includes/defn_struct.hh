#pragma once

#include<iostream>
#include<memory>
#include<string>

struct Container
{
  Container() {}
  Container
  (
    std::string str_in ,
    int         num_in
  )
  :
  str (str_in) ,
  num (num_in)
  {}
  
  std::string str;
  int         num;
  
  void printContainer();
};

// #define SIZE_STRING 256

