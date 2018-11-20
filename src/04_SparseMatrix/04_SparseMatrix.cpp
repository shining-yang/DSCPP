//
// File: SparseMatrix.cpp
//
// Test case for SparseMatrix<T>
// Shining Yang <y.s.n@live.com>, 2014-10-11
//
#include "SparseMatrix.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
  cout << "> Creating sm <" << endl;
  SparseMatrix<int> sm;
  cin >> sm;
  cout << sm << endl;
  sm.Output(cout);

  SparseMatrix<int> tsm;
  sm.Transpose(tsm);
  cout << tsm << endl;
  tsm.Output(cout);

  //-------------------------------------------------------
  cout << "> Creating sm2 <" << endl;
  SparseMatrix<int> sm2;
  cin >> sm2;
  cout << sm2 << endl;
  sm2.Output(cout);

  SparseMatrix<int> sm3;
  sm.Add(sm2, sm3);
  cout << sm3 << endl;
  sm3.Output(cout);

  return 0;
}