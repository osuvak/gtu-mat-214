#include <iostream>

class Options
{
private:
  static bool flag_talks_;
  
private:
  Options  () {}
  ~Options () {}
  
public:
  static 
  void set_flag_talks( bool flag = true ) 
  { flag_talks_ = flag; }
  
  static 
  bool get_flag_talks( void ) 
  { return flag_talks_; }
};

bool Options::flag_talks_ = true;

class Shape {
  public:
    Shape() {
      id_ = total_++;
      if ( Options::get_flag_talks() )
      {
        std::cout << "Constructor called for Shape with id : " << this->id_ << std::endl;
      }
    }
	
    virtual
    ~Shape() { std::cout << "Destructor  called for Shape with id : " << this->id_ << std::endl; }
	
    virtual void draw() = 0;
  protected:
    int id_;
    static int total_;
};
int Shape::total_ = 0;

class Circle : public Shape {
  public:
    Circle ()
    {
      std::cout << "Constructor called for Circle." << std::endl;
    }
    
    virtual
    ~Circle ()
    {
      std::cout << "Destructor  called for Circle." << std::endl;
    }
    
    void draw() {
      std::cout << "circle " << id_ << ": draw" << std::endl;
    }
};

class Square : public Shape {
  public:
    Square ()
    {
      std::cout << "Constructor called for Square." << std::endl;
    }
    
    virtual
    ~Square ()
    {
      std::cout << "Destructor  called for Square." << std::endl;
    }
    
    void draw() {
      std::cout << "square " << id_ << ": draw" << std::endl;
    }
};

class Ellipse : public Shape {
  public:
    Ellipse ()
    {
      std::cout << "Constructor called for Ellipse." << std::endl;
    }
    
    virtual
    ~Ellipse ()
    {
      std::cout << "Destructor  called for Ellipse." << std::endl;
    }
    
    void draw() {
      std::cout << "ellipse " << id_ << ": draw" << std::endl;
    }
};

class Rectangle : public Shape {
  public:
    Rectangle ()
    {
      std::cout << "Constructor called for Rectangle." << std::endl;
    }
    
    virtual
    ~Rectangle ()
    {
      std::cout << "Destructor  called for Rectangle." << std::endl;
    }
    
    void draw() {
      std::cout << "rectangle " << id_ << ": draw" << std::endl;
    }
};

class Factory {
  public:
    virtual Shape* createCurvedInstance() = 0;
    virtual Shape* createStraightInstance() = 0;
};

class SimpleShapeFactory : public Factory {
  public:
    Shape* createCurvedInstance() {
      return new Circle;
    }
    Shape* createStraightInstance() {
      return new Square;
    }
};
class RobustShapeFactory : public Factory {
  public:
    Shape* createCurvedInstance()   {
      return new Ellipse;
    }
    Shape* createStraightInstance() {
      return new Rectangle;
    }
};

#define SIMPLE

int main(void) {
#ifdef SIMPLE
  Factory* factory = new SimpleShapeFactory;
#else
  Factory* factory = new RobustShapeFactory;
#endif
  Shape* shapes[3];

  shapes[0] = factory->createCurvedInstance();   // shapes[0] = new Ellipse;
  shapes[1] = factory->createStraightInstance(); // shapes[1] = new Rectangle;
  shapes[2] = factory->createCurvedInstance();   // shapes[2] = new Ellipse;

  for (int i=0; i < 3; i++) {
    shapes[i]->draw();
  }
  
  for (int i=0; i < 3; i++) 
  {
    delete shapes[i];
  }
  
  return 0;
}