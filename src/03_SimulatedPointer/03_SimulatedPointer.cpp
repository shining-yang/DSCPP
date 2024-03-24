// 03_SimulatedPointer.cpp : Defines the entry point for the console
// application.
//
// 2014/9/5, Shining Yang <y.s.n@live.com>
//
#include <iostream>

#include "SimulatedPointer.h"

using namespace std;

int main(int argc, char *argv[]) {
  int x;
  SimChain<int> c;
  cout << "Chain length is: " << c.Length() << endl;
  c.Insert(0, 2).Insert(1, 6);
  cout << "Chain length is: " << c.Length() << endl;
  c.Find(1, x);
  cout << "[1] element is: " << x << endl;
  c.Delete(1, x);
  cout << "Deleted: " << x << endl;
  cout << "New length is: " << c.Length() << endl;
  cout << "Position of 2 is: " << c.Search(2) << endl;
  cout << "Position of 6 is: " << c.Search(6) << endl;
  c.Insert(0, 9).Insert(1, 8).Insert(2, 7).Insert(3, 6).Insert(4, 5);
  cout << "Current chain is: " << c << endl;
  c.Delete(3, x).Delete(2, x).Delete(3, x);
  cout << "Current chain is: " << c << endl;
  cout << "Its length is: " << c.Length() << endl;

  return 0;
}
