//
// File: 04_Array.cpp
//
// Shining Yang <y.s.n@live.com>, 2014/09
//
#include <iostream>
#include "Array.h"

using namespace std;

int main(int argc, char* argv[]) {
  int n = 10;
  Array<int> a(n);
  for (int i = 0; i < n; i++) {
    a[i] = i * i;
  }

  cout << "Array elements: \n" << a << endl;
  return 0;
}
