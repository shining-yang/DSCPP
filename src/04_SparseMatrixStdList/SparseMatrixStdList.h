//
// File: SparseMatrixStdList.h
//
// Sparse matrix implemented with std::list.
//
// 2014-10-13, Shining Yang <y.s.n@live.com>
//
#pragma once

#include <iostream>
#include <list>
using namespace std;

#include "../Utility/Exception.h"
using namespace DSCPP::Utils;

template<typename T> class CColumnNode;
template<typename T> class CRowNode;
template<typename T> class CSparseMatrixStdList;

template<typename T>
class CColumnNode {
private:
    int column;
    T   data;

    template<typename T>
    friend ostream& operator<<(ostream& os, const CColumnNode<T>& o);

    template<typename T>
    friend istream& operator>>(istream& is, CSparseMatrixStdList<T>& o);
};

template<typename T>
ostream& operator<<(ostream& os, const CColumnNode<T>& o)
{
    os << "Column: " << o.column << " Data: " << o.data;
    return os;
}

template<typename T>
class CRowNode {
private:
    int row;
    std::list<CColumnNode<T> > cl; // list of column node

    template<typename T>
    friend ostream& operator<<(ostream& os, const CRowNode<T>& o);

    template<typename T>
    friend istream& operator>>(istream& is, CSparseMatrixStdList<T>& o);
};

template<typename T>
ostream& operator<<(ostream& os, const CRowNode<T>& o)
{
    os << "Row " << o.row << ": ";
    for (std::list<CColumnNode<T> >::const_iterator it = o.cl.cbegin();
        it != o.cl.cend();
        ++it) {
        if (it != o.cl.cbegin()) {
            os << ", ";
        }
        os << *it;
    }
    return os;
}

template<typename T>
class CSparseMatrixStdList {
private:
    int rows;       // rows of sparse matrix
    int columns;    // columns of sparse matrix
    std::list<CRowNode<T> > rl; // list of row node

    template<typename T>
    friend ostream& operator<<(ostream& os, const CSparseMatrixStdList<T>& o);

    template<typename T>
    friend istream& operator>>(istream& is, CSparseMatrixStdList<T>& o);
};

template<typename T>
ostream& operator<<(ostream& os, const CSparseMatrixStdList<T>& o)
{
    os << "Dimension of matrix: " << o.rows << " x " << o.columns << endl;
    for (std::list<CRowNode<T> >::const_iterator it = o.rl.cbegin();
        it != o.rl.cend();
        ++it) {
        if (it != o.rl.cbegin()) {
            os << endl;
        }
        os << *it;
    }

    return os;
}

template<typename T>
istream& operator>>(istream& is, CSparseMatrixStdList<T>& o)
{
    cout << "Enter rows, columns, none-zero counts: ";
    int r, c, n;
    is >> r >> c >> n;
    if (r < 1 || c < 1 || n < 1) {
        throw new OutOfRange();
    }

    o.rows = r;
    o.columns = c;

    cout << "Now, please enter the elements (row column data) " << endl;

    for (int i = 0; i < n; i++) {
        cout << "No. " << (i + 1) << ": ";

        T v;
        is >> r >> c >> v;
        if (r < 1 || c < 1 || r > o.rows || c > o.columns || n < 1) {
            throw new OutOfRange();
        }

        bool inserted = false;
        CColumnNode<T> cnode;
        cnode.column = c;
        cnode.data = v;

        for (std::list<CRowNode<T> >::iterator it = o.rl.begin();
            it != o.rl.end();
            ++it) {
            if (it->row == r) {
                it->cl.push_back(cnode);
                inserted = true;
                break;
            }
        }

        if (!inserted) {
            CRowNode<T> rnode;
            rnode.row = r;
            o.rl.push_back(rnode);
            o.rl.back().cl.push_back(cnode);
        }
    }

    return is;
}
