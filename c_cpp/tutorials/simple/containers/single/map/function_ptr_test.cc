#include <iostream>
#include <map>
#include <string>
#include <cmath>

double square(double number);
double squareroot(double number);

int main ()
{
  using namespace std;
  
  map< string , double (*)( double ) > mymap;
  
  mymap["squarer"]      = square;
  mymap["squarerooter"] = squareroot;
  
  double number = 5.0;
  
  for (auto it=mymap.begin(); it!=mymap.end(); ++it)
  {
    cout << "Calling function \"" << it->first << "\" => " << endl;
    cout << "  " << it->second(number) << endl;
  }
  
  return 0;
}

double square(double number)
{
  return number * number;
}

double squareroot(double number)
{
  return sqrt( number );
}
