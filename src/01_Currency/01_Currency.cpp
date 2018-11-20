// 01_Currency.cpp : Defines the entry point for the console application.
//
// US currency, $
//
// Default parameters for constructor, operator overloading, friend functions
//
// 2014/8/26, Shining Yang <y.s.n@live.com>
//

#include <iostream>
#include "Currency.h"
using namespace std;

int main(int argc, char* argv[]) {
  CCurrency a(3599, 99);
  CCurrency b(11088, 1, MINUS);
  CCurrency c, d, e;

  c.Set(-100.0);
  d = c % 50.0;
  e = c + d;

  d -= 10.0f; // auto-conversion: float -> CCurrency
  d += 20.0f; // auto-conversion: float -> CCurrency

  CCurrency f;
  cin >> f;

  cout << a << endl;
  cout << b << endl;
  cout << c << endl;
  cout << d << endl;
  cout << e << endl;
  cout << f << endl;

  return 0;
}

