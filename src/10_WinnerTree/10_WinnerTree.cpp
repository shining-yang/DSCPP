//
// File: 10_WinnerTree.cpp
// Shining Yang <y.s.n@live.com>, 2014-12-23
//
#include <iostream>

#include "WinnerTree.h"

using namespace std;
using namespace DSCPP::WinnerTree;

template <typename T>
int Win(T a[], int i, int j) {
  return (a[i] > a[j]) ? i : j;
}

int main(int argc, char *argv[]) {
  WinnerTree<int> wt;
  int a[] = {1, 4, 7, 8, 5, 6, 2, 9, 3};
  wt.Initialize(a, sizeof(a) / sizeof(a[0]), Win);

  for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
    cout << a[wt.Winner()] << endl;
    a[wt.Winner()] = INT32_MIN;
    wt.Replay(wt.Winner(), Win);
  }

  return 0;
}
