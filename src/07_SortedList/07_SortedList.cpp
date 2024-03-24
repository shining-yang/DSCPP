//
// File: 07_SoredList.cpp
// Shining Yang <y.s.n@live.com>, 2014-11-18
//
#include "../PerformanceStatistics/HighResTimeCounter.h"
#include "SortedList.h"
#include <iostream>
#pragma comment(lib, "PerformanceStatistics")

int main(int argc, char *argv[]) {
  int dummy;
  DSCPP::SortedLinearList::SortedList<int, int> sl;
  sl.Insert(1)
      .Insert(5)
      .Insert(20)
      .Insert(8)
      .Insert(16)
      .Insert(15)
      .Insert(10)
      .Insert(12);
  std::cout << sl << std::endl;
  sl.Delete(8, dummy).Insert(9).Delete(12, dummy).Insert(18).Insert(25);
  std::cout << sl << std::endl;

#define PRINT_SEARCH_RESULT(n)                                                 \
  std::cout << "Contains " << n << " ? "                                       \
            << ((sl.Search(n, dummy)) ? "YES" : "NO") << std::endl;
  PRINT_SEARCH_RESULT(1);
  PRINT_SEARCH_RESULT(2);
  PRINT_SEARCH_RESULT(3);
  PRINT_SEARCH_RESULT(4);
  PRINT_SEARCH_RESULT(5);
  PRINT_SEARCH_RESULT(10);
  PRINT_SEARCH_RESULT(16);
  PRINT_SEARCH_RESULT(18);
  PRINT_SEARCH_RESULT(19);
  PRINT_SEARCH_RESULT(25);
  PRINT_SEARCH_RESULT(35);

  sl.Clear();

  CHighResTimeCounter c1;
  c1.Begin();
  for (int i = 0; i < 1024 * 10; i++) {
    sl.Insert(i);
  }
  c1.End();
  std::cout << "Time costs: " << c1.GetElapsedTimeInMS() << endl;

  CHighResTimeCounter c2;
  c2.Begin();
  for (int i = 0; i < 1024 * 10; i++) {
    sl.Delete(i, dummy);
  }
  c2.End();
  std::cout << "Time costs: " << c2.GetElapsedTimeInMS() << endl;

  CHighResTimeCounter c3;
  c3.Begin();
  for (int i = 1024 * 10; i > 0; i--) {
    sl.Insert(i);
  }
  c3.End();
  std::cout << "Time costs: " << c3.GetElapsedTimeInMS() << endl;

  return 0;
}
