// 03_SinglyLinkedList.cpp : Defines the entry point for the console
// application.
//
// Singly linked list
// Shining Yang <y.s.n@live.com>, 2014/09/02

#include <iostream>

#include "../PerformanceStatistics/HighResTimeCounter.h"
#include "../Utility/NewHandler.h"
#include "SinglyLinkedList.h"

using namespace std;
#pragma comment(lib, "Utility")
#pragma comment(lib, "PerformanceStatistics")

int main(int argc, char *argv[]) {
  ApplyCustomNewHandler();

  Chain<int> c;
  for (int i = 0; i < 20; i++) {
    c.Insert(i, (i + 1) * (i + 1));
  }

  for (int i = 9; i >= 0; i--) {
    int x;
    c.Delete(i, x);
  }

  c.Output(std::cout);

  std::cout << std::endl << std::endl;

  Chain<int> cp = c;
  cp.Reverse();
  for (Chain<int>::Iterator it = cp.Begin(); it != cp.End();) {
    std::cout << *it++ << " ";
  }

  //--------------------------------------------------------------------------
  Chain<int> cr1 = cp;
  Chain<int> cr2;
  CHighResTimeCounter tc;

  tc.Begin();
  cr1.Reverse();
  tc.End();
  std::cout << "\nTime costed: " << tc.GetElapsedTimeInMS() << std::endl;

  tc.Begin();
  ReverseChain(cr1, cr2);
  tc.End();
  std::cout << "\nTime costed: " << tc.GetElapsedTimeInMS() << std::endl;

  //--------------------------------------------------------------------------
  Chain<int> ca = c;
  ca.Insert(0, 7);
  ca.Insert(4, 5);
  ca.Insert(7, 11);
  ca.BubbleSort();
  cout << ca << endl;

  ca.Clear();
  ca.Insert(0, 49);
  ca.Insert(0, 18);
  ca.Insert(0, 7);
  ca.Insert(0, 19);
  ca.Insert(0, 8);
  ca.Insert(0, 37);
  ca.SelectionSort();
  cout << ca << endl;
  ca.SelectionSort(false);
  cout << ca << endl;

  return 0;
}
