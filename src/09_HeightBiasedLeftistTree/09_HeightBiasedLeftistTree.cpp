//
// File: 09_HeightBiasedLeftistTree.cpp
// Shining Yang <y.s.n@live.com>, 2014-12-09
//
#include <iostream>
#include "HeightBiasedLeftistTree.h"
using namespace std;
using namespace DSCPP::PriorityQueue;

int main(int argc, char* argv[]) {
  int dummy;
  MaxHBLT<int> mh, mh2;

  mh.Insert(2).Insert(9).Insert(3).Insert(6).Insert(1);
  mh.DeleteMax(dummy);
  cout << "Print vertically: " << endl;
  mh.PrintTreeVertically(cout, 64);

  mh.Clone(mh2);

  mh2.Insert(8).Insert(4);
  cout << "Print vertically: " << endl;
  mh2.PrintTreeVertically(cout, 64);

  int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  mh2.Initialize(a, sizeof(a) / sizeof(a[0]));
  cout << "Print vertically: " << endl;
  mh2.PrintTreeVertically(cout, 64);

  cout << "Dump all elements of the MinHBLT:" << endl;
  while (!mh2.IsEmpty()) {
    mh2.DeleteMax(dummy);
    cout << dummy << ", ";
  }
  cout << endl << endl;

  //
  // - MinHBLT
  //
  MinHBLT<int> minHBLT, minHBLT2;
  minHBLT.Initialize(a, sizeof(a) / sizeof(a[0]));
  cout << "Print vertically: " << endl;
  minHBLT.PrintTreeVertically(cout, 64);

  minHBLT.Clone(minHBLT2);

  minHBLT2.DeleteMin(dummy);
  minHBLT2.DeleteMin(dummy);
  cout << "Print vertically: " << endl;
  minHBLT2.PrintTreeVertically(cout, 64);

  minHBLT2.Insert(15).Insert(18);
  cout << "Print vertically: " << endl;
  minHBLT2.PrintTreeVertically(cout, 64);

  minHBLT2.Merge(minHBLT);
  cout << "Print vertically: " << endl;
  minHBLT2.PrintTreeVertically(cout, 64);

  cout << "Dump all elements of the MinHBLT:" << endl;
  while (!minHBLT2.IsEmpty()) {
    minHBLT2.DeleteMin(dummy);
    cout << dummy << ", ";
  }
  cout << endl << endl;

  return 0;
}