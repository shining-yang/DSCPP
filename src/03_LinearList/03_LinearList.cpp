//
// File: 03_LinearList.cpp
//
// Linear list (array)
// Shining Yang <y.s.n@live.com>, 2014/08/29
//
#include <iostream>
using namespace std;

#include "LinearList.h"

int main(int argc, char* argv[]) {
  LinearList<int> la(16);
  for (int i = 0; i < 8; i++) {
    la.Insert(i, i * 2 + 1);
  }

  int de;
  la.Delete(3, de);
  la.Output(std::cout);
  la.Insert(12, 99);
  return 0;
}
