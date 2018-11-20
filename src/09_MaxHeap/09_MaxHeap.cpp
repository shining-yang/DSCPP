//
// File: 09_MaxHeap.cpp
// Shining Yang <y.s.n@live.com>, 2014-12-08
//
#include "MaxHeap.h"
using namespace DSCPP::PriorityQueue;

int main(int arg, char* argv[]) {
  int dummy;
  MaxHeap<int> mh;

  mh.Insert(9).Insert(3).Insert(8).Insert(2).Insert(7).Insert(6).Insert(4).Insert(5).Insert(1);
  cout << "MaxHeap elements by level: " << mh << endl;
  mh.PrintTreeVertically(cout, 60);

  mh.DeleteMax(dummy);
  cout << "MaxHeap elements by level: " << mh << endl;
  mh.PrintTreeVertically(cout, 60);

  mh.DeleteMax(dummy);
  cout << "MaxHeap elements by level: " << mh << endl;
  mh.PrintTreeVertically(cout, 40);

  mh.DeleteMax(dummy);
  cout << "MaxHeap elements by level: " << mh << endl;
  mh.PrintTreeVertically(cout, 40);

  // Sorting
  int a[] = { 0, 1, 4, 8, 9, 2, 1, 4, 3, 5, 7, 6, 3 };
#define ELEM_COUNT(a)   (sizeof(a) / sizeof(a[0]))

  MaxHeap<int>::Sort(a, ELEM_COUNT(a));
  cout << "Sorting with MaxHeap:" << endl;
  for (int i = 0; i < ELEM_COUNT(a); i++) {
    cout << a[i] << ", ";
  }
  cout << endl;

  return 0;
}