//
// File: SparseMatrixLinked.h
//
// Sparse matrix implemented by linked list.
//
// 2014-10-13, Shining Yang <y.s.n@live.com>
//
#pragma once

#include <iostream>
using namespace std;

#include "../03_SinglyLinkedList/SinglyLinkedList.h"
#include "../Utility/Exception.h"
using namespace DSCPP::Utils;

// class declarations
template <class T> class ColumnNode;
template <class T> class RowNode;
template <class T> class SparseMatrixLinked;

//
//------------------------------------------------------------------------------
//
template <class T> class ColumnNode {
public:
  void Output(ostream &os) const {
    os << "Column: " << col << " Value: " << val;
  }

private:
  int col;
  T val;

  template <class E>
  friend istream &operator>>(istream &is, SparseMatrixLinked<E> &o);
};

template <class T> ostream &operator<<(ostream &os, const ColumnNode<T> &o) {
  o.Output(os);
  return os;
}

//
//------------------------------------------------------------------------------
//
template <class T> class RowNode {
public:
  void Output(ostream &os) const { os << "Row " << row << ": " << chainCol; }

private:
  int row;
  Chain<ColumnNode<T>> chainCol;

  template <class E>
  friend istream &operator>>(istream &is, SparseMatrixLinked<E> &o);
};

template <class T> ostream &operator<<(ostream &os, const RowNode<T> &o) {
  o.Output(os);
  return os;
}

//
//------------------------------------------------------------------------------
//
template <class T> class SparseMatrixLinked {
public:
  void Output(ostream &os) const {
    os << "Sparse matrix: " << rows << " x " << columns << endl;
    os << chainRow;
  }

private:
  int rows;
  int columns;
  Chain<RowNode<T>> chainRow;

  template <class E>
  friend istream &operator>>(istream &is, SparseMatrixLinked<E> &o);
};

template <class T> istream &operator>>(istream &is, SparseMatrixLinked<T> &o) {
  cout << "First, provide info about rows, columns, none-zero elements: ";

  int r, c, n;
  is >> r >> c >> n;

  if (r < 1 || c < 1 || n < 1) {
    throw new InvalideArgument();
  }

  o.rows = r;
  o.columns = c;

  cout << "Your inputs are accepted. " << "rows: " << r << ", columns: " << c
       << ", none-zero elements: " << n << endl;

  cout
      << "Second, enter the none-zero elements INCREAMENTLY (row column value):"
      << endl;

  for (int i = 0; i < n; i++) {
    cout << "No. " << (i + 1) << ": ";

    T v;
    is >> r >> c >> v;
    if (r < 1 || c < 1 || r > o.rows || c > o.columns || v == 0) {
      throw new InvalideArgument();
    }

    RowNode<T> rnode;
    rnode.row = r;

    // {{ BAD practices. Since there are not proper methods available yet.
    bool inserted = false;
  _TryInsertColumnData:
    for (auto rit = o.chainRow.Begin(); rit != o.chainRow.End(); ++rit) {
      if ((*rit).row == r) { // find the existing one
        ColumnNode<T> cnode;
        cnode.col = c;
        cnode.val = v;

        (*rit).chainCol.Insert((*rit).chainCol.Length(), cnode);
        inserted = true;
        break;
      }
    }

    if (!inserted) {
      o.chainRow.Insert(o.chainRow.Length(), rnode);
      goto _TryInsertColumnData;
    }
    // }}
  }

  return is;
}

template <class T>
ostream &operator<<(ostream &os, const SparseMatrixLinked<T> &o) {
  o.Output(os);
  return os;
}
