//
// File: 04_matrix.cpp
//
// Shining Yang <y.s.n@live.com>, 2014-09-30
//

#include "matrix.h"
#include <iostream>
using namespace std;

template <typename T>
void OutputMatrixElement(const Matrix<T> &m, int i, int j) {
  // i, j are 0-based, different from Matrix
  if ((i >= m.Rows()) || (j >= m.Columns())) {
    return;
  }

  cout << m(i + 1, j + 1) << " ";
}

template <typename T>
void OutputAtSubscriptSum(const Matrix<T> &m, int n, bool ascending) {
  for (int i = 0; i <= n; i++) {
    if (ascending) {
      OutputMatrixElement(m, i, n - i);
    } else {
      OutputMatrixElement(m, n - i, i);
    }
  }
}

// 锯齿形遍历矩阵
template <typename T> void ZigzagTraverse(const Matrix<T> &m) {
  int total = m.Rows() - 1 + m.Columns() - 1;
  bool ascending = false;
  for (int i = 0; i <= total; i++) {
    OutputAtSubscriptSum(m, i, ascending);
    ascending = !ascending;
  }
}

// 水平来回扫描式遍历矩阵
template <typename T> void HorizontallyTraverse(const Matrix<T> &m) {
  bool ltr = true; // left to right
  for (int i = 0; i < m.Rows(); i++) {
    if (ltr) {
      for (int j = 0; j < m.Columns(); j++) {
        OutputMatrixElement(m, i, j);
      }
    } else {
      for (int j = m.Columns() - 1; j >= 0; j--) {
        OutputMatrixElement(m, i, j);
      }
    }

    ltr = !ltr;
  }
}

// 垂直来回扫描式遍历矩阵
template <typename T> void VerticallyTraverse(const Matrix<T> &m) {
  bool utd = true; // up to down
  for (int j = 0; j < m.Columns(); j++) {
    if (utd) {
      for (int i = 0; i < m.Rows(); i++) {
        OutputMatrixElement(m, i, j);
      }
    } else {
      for (int i = m.Rows() - 1; i >= 0; i--) {
        OutputMatrixElement(m, i, j);
      }
    }

    utd = !utd;
  }
}

// 螺旋式遍历矩阵
template <typename T> void SpiralTraverse(const Matrix<T> &m) {
  int r0 = 0;
  int c0 = 0;
  int r1 = m.Rows() - 1;
  int c1 = m.Columns() - 1;
  int i, j;

  while ((r0 <= r1) && (c0 <= c1)) {
    if (r0 == r1) {
      for (j = c0; j <= c1; j++)
        OutputMatrixElement(m, r0, j);
    } else if (c0 == c1) {
      for (i = r0; i <= r1; i++)
        OutputMatrixElement(m, i, c0);
    } else {
      for (i = r0, j = c0; j <= c1; j++)
        OutputMatrixElement(m, i, j);
      for (j = c1, i = r0 + 1; i <= r1 && j > c0; i++)
        OutputMatrixElement(m, i, j);
      for (i = r1, j = c1 - 1; j >= c0 && i > r0; j--)
        OutputMatrixElement(m, i, j);
      for (j = c0, i = r1 - 1; i > r0; i--)
        OutputMatrixElement(m, i, j);
    }

    r0++;
    c0++;
    r1--;
    c1--;
  }
}

int main(int argc, char *argv[]) {
  Matrix<int> m1(2, 3);
  m1(1, 1) = 1;
  m1(1, 2) = 2;
  m1(1, 3) = 3;
  m1(2, 1) = 2;
  m1(2, 2) = 1;
  m1(2, 3) = 4;

  const Matrix<int> cm1 = m1;
  cm1.Output(cout);

  Matrix<int> m2(3, 1);
  m2(1, 1) = 0;
  m2(2, 1) = 1;
  m2(3, 1) = 2;

  Matrix<int> m3 = m1 * m2;

  cout << "m1:" << endl << m1 << endl;
  cout << "m2:" << endl << m2 << endl;
  cout << "m3:" << endl << m3 << endl;

  Matrix<int> tm1 = m1.Transpose();
  cout << "tm1:" << endl << tm1 << endl;

  //---- Zigzag output
  char k = 'A';
  int row = 4, column = 4;
  Matrix<char> mc(row, column);
  for (int i = 1; i <= row; i++) {
    for (int j = 1; j <= column; j++) {
      mc(i, j) = k++;
    }
  }
  cout << mc << endl;

  //-- zigzag
  cout << "Zigzag output: " << endl;
  ZigzagTraverse(mc);
  cout << endl;

  //-- horizontally
  cout << "Back and forth by row: " << endl;
  HorizontallyTraverse(mc);
  cout << endl;

  //-- vertically
  cout << "Back and forth by column: " << endl;
  VerticallyTraverse(mc);
  cout << endl;

  //-- spirally
  cout << "Spirally: " << endl;
  SpiralTraverse(mc);
  cout << endl;

  //-- Square matrix operations
  SquareMatrix sm(3);
  sm(1, 1) = 1;
  sm(1, 2) = 2;
  sm(1, 3) = -1;
  sm(2, 1) = 3;
  sm(2, 2) = 4;
  sm(2, 3) = -2;
  sm(3, 1) = 5;
  sm(3, 2) = -4;
  sm(3, 3) = 1;

  double det = sm.CalcDeterminant();

  cout << "Matrix:" << endl;
  cout << sm << endl;

  cout << "Adjoint matrix:" << endl;
  cout << sm.BuildAdjointMatrix() << endl;

  cout << "Inverse matrix:" << endl;
  cout << sm.BuildInverseMatrix() << endl;

  cout << "cross product matrix and its inverse matrix:" << endl;
  cout << sm * (sm.BuildInverseMatrix()) << endl;

  return 0;
}