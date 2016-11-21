/*
 * Example adapted from:
 * http://www.cplusplus.com/doc/tutorial/inheritance/
 * */

// friend functions
#include <iostream>
#include <typeinfo>
#include <string>
#include <memory>

class Rectangle 
{
  private:
    std::string name_;
    int width_, height_;
    
  private:
    
    void report(std::string keyword)
    {
      std::cout 
        <<  keyword << " instance of class :" << std::endl
        << "  " << typeid(*this).name() << std::endl
        << "    Name   : " << name_   << std::endl
        << "    Width  : " << width_  << std::endl
        << "    Height : " << height_ << std::endl;
    }
    
    void report_construction(void)
    {
      report("Created");
    }
    
    void report_destruction(void)
    {
      report("Destroyed");
    }
    
  public:
  
    Rectangle () 
    : 
    name_("") , width_(0), height_(0) 
    { report_construction(); }
    
    Rectangle (std::string name, int x, int y) 
    : 
    name_(name) , width_(x) , height_(y) 
    { report_construction(); }
    
    ~Rectangle()
    { report_destruction(); }
    
    int area() {return width_ * height_;}
    
    friend 
    Rectangle 
    duplicate 
    (const Rectangle&);
    
    friend 
    std::shared_ptr<Rectangle> 
    duplicate_return_shared_ptr 
    (const Rectangle&);
};

Rectangle 
duplicate 
(const Rectangle& param)
{
  Rectangle res;
  res.name_   = param.name_ + " copy";
  res.width_  = param.width_  * 2;
  res.height_ = param.height_ * 2;
  return res;
}

// cannot overload with respect to output type
// should rename this function
std::shared_ptr<Rectangle> 
duplicate_return_shared_ptr
(const Rectangle& param)
{
  std::shared_ptr<Rectangle> res( new Rectangle );
  
  (*res).name_   = param.name_ + " copy";
  (*res).width_  = param.width_  * 2;
  (*res).height_ = param.height_ * 2;
  
  return res;
}

int main () 
{
  using namespace std;
  
  Rectangle foo;
  Rectangle bar ( "bar" , 2 , 3 );
  
  foo = duplicate (bar);
  cout << "Area of copied rectangle : " << foo.area()  << endl;
  
  std::shared_ptr<Rectangle> zeta = duplicate_return_shared_ptr(foo);
  cout << "Area of copied rectangle : " << (*zeta).area() << endl;
  
  return 0;
}