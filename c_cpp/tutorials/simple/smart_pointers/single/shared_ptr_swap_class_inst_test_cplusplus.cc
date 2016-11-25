/*
 * shared_ptr swap with class instances
 * << overloading for reports - ostream usage
 *
 * Example adapted from :
 * http://www.cplusplus.com/reference/memory/shared_ptr/swap-free/
 * */

 
/*
 * Activate the following define to generate a compilation error.
 * Should make reporters const (unable to modify class instance members)
 * when called upon a const ref of instance.
 * */ 
// #define MAKE_REPORTERS_NON_CONST
 
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
    
    void report_construction(void)
#ifndef MAKE_REPORTERS_NON_CONST
    const
#endif
    {
      report( std::cout , "Created" );
    }
    
    void report_destruction(void)
#ifndef MAKE_REPORTERS_NON_CONST
    const
#endif
    {
      report( std::cout , "Destroyed" );
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
    
    int area() const {return width_ * height_;}
    
    void report( std::ostream& stream , std::string keyword )
#ifndef MAKE_REPORTERS_NON_CONST    
    const
#endif
    {
      stream 
        << std::endl
        <<  keyword << " instance of class :" << std::endl
        << "  " << typeid(*this).name() << std::endl
        << "    Name   : " << name_   << std::endl
        << "    Width  : " << width_  << std::endl
        << "    Height : " << height_ << std::endl
        << std::endl;
    }
    
};

std::ostream& operator<< (std::ostream& stream, const Rectangle& current)
{
  current.report( stream , "Examining" );
  return stream;
}

int main(void) 
{
  using namespace std;
  
  std::shared_ptr<Rectangle> foo ( new Rectangle ( "foo" , 1 , 2 ) );
  std::shared_ptr<Rectangle> bar ( new Rectangle ( "bar" , 4 , 5 ) );

  cout << "foo: " << *foo << endl << "bar: " << *bar << endl;
  swap(foo,bar);
  cout << "Swapped." << endl << endl;
  cout << "foo: " << *foo << endl << "bar: " << *bar << endl;
  swap(foo,bar);
  cout << "Swapped." << endl << endl;
  cout << "foo: " << *foo << endl << "bar: " << *(bar.get()) << endl;
  
  return 0;
}