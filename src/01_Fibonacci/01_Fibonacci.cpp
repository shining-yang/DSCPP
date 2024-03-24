// 01_Fibonacci.cpp : Defines the entry point for the console application.
//
// 2014/8/23, Shining Yang <y.s.n@live.com>
//
// Fibonacci
//
// F(1) = 1, F(2) = 1, F3 = 2, F4 = 3, ...., F(n) = F(n-1) + F(n-2)
//

#include <stdio.h>

#include "../PerformanceStatistics/HighResTimeCounter.h"
#include "../PerformanceStatistics/TickCounter.h"

#pragma comment(lib, "PerformanceStatistics")

int Fibonacci(int n) {
  if (n < 1)
    return 0;

  if (n == 1 || n == 2)
    return 1;

  int tmp = 0;
  int f1 = 1;
  int f2 = 1;
  for (int i = 2; i < n; i++) {
    tmp = f1 + f2;
    f1 = f2;
    f2 = tmp;
  }

  return tmp;
}

int FibonacciRecursive(int n) {
  if (n < 1)
    return 0;

  if (n == 1 || n == 2)
    return 1;

  return FibonacciRecursive(n - 1) + FibonacciRecursive(n - 2);
}

int main(int argc, char *argv[]) {
  int n1 = 0;
  int n2 = 0;
  CHighResTimeCounter tc1;
  CHighResTimeCounter tc2;

  for (int i = 0; i < 40; i++) {
    tc1.Begin();
    n1 = Fibonacci(i);
    tc1.End();

    tc2.Begin();
    n2 = FibonacciRecursive(i);
    tc2.End();

    printf("Fibonacci(%d) : %4d [%4d], %4d [%4d]\n", i, n1,
           tc1.GetElapsedTimeInMS(), n2, tc2.GetElapsedTimeInMS());
  }

  return 0;
}
