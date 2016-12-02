#include <itpp/itbase.h>
#include <iomanip>

using namespace itpp;
using namespace std;

template <typename T>
void modify_vector(const Vec<T> & , Vec<T>  );

template <typename T>
void modify_vector(const Vec<T> & , Vec<T> & , T );

int main(void)
{
  vec dv1 = randu(10);
  vec dv2 = randu(10);
  
  cout << dv1 << endl;
  dv1(0) = 1.0;
  cout << dv1 << endl;
  
  vec temp = randu(1);
  dv1(0) = temp(0);
  cout << dv1 << endl;
  
//   dv1(0) = reinterpret_cast<double>( randu(1) );
//   cout << dv1 << endl;
  
  dv1(0) = randu();
  cout << dv1 << endl;
  
  cout << endl << "Vector dv1 before modification:" << endl << dv1 << endl;
  cout << endl << "Vector dv2 before modification:" << endl << dv2 << endl;
  modify_vector( dv1 , dv2 );
  cout << endl << "Vector dv1 after modification:" << endl << dv1 << endl;
  cout << endl << "Vector dv2 after modification:" << endl << dv2 << endl;
  
  return 0;
}

template <typename T>
void modify_vector(const Vec<T> &a , Vec<T> c)
{
//   c = a;
  c(0) = a(0);
}

template <typename T>
void modify_vector(const Vec<T> &a , Vec<T> &c , T num = 0.0)
{
//   c = a;
  c(0) = a(0);
}