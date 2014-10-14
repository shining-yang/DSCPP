//
// File: SparseMatrixStdList.h
//
// Sparse matrix implemented with std::list.
// Assumption: row/column indices is ascending ordered.
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
public:
    CColumnNode(int c, const T& d) : column(c), data(d) {}

private:
    int column;
    T   data;

    friend class CRowNode < T >;
    friend class CSparseMatrixStdList < T > ;

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
public:
    CRowNode(int r) : row(r) {}

public:
    void AddElementNode(int c, const T& d);

private:
    int row;
    std::list<CColumnNode<T> > cl; // list of column node

    friend class CSparseMatrixStdList < T > ;

    template<typename T>
    friend ostream& operator<<(ostream& os, const CRowNode<T>& o);

    template<typename T>
    friend istream& operator>>(istream& is, CSparseMatrixStdList<T>& o);
};

template<typename T>
void CRowNode<T>::AddElementNode(int c, const T& d)
{
    std::list<CColumnNode<T> >::iterator pre = cl.begin();
    std::list<CColumnNode<T> >::iterator itcol = cl.begin();

    for ( ; itcol != cl.end(); ++itcol) {
        if (c == itcol->column) { // update if already exists
            itcol->data = d;
            return;
        }

        if (c > pre->column && c < itcol->column) {
            break;
        }

        pre = itcol;
    }
    
    cl.insert(itcol, CColumnNode<T>(c, d));
}

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
public:
    CSparseMatrixStdList() : rows(0), columns(0) {}

public:
    void Clear(void);

    // make a transposed copy to `obj`
    void Transpose(CSparseMatrixStdList<T>& o) const;

protected:
    void _AddElement(int r, int c, const T& d);

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
void CSparseMatrixStdList<T>::_AddElement(int r, int c, const T& d)
{
    std::list<CRowNode<T> >::iterator pre = rl.begin();
    std::list<CRowNode<T> >::iterator itrow = rl.begin();

    for ( ; itrow != rl.end(); ++itrow) {
        if (r == itrow->row) { // Row already exists
            itrow->AddElementNode(c, d);
            return;
        }

        if (r > pre->row && r < itrow->row) {
            break;
        }

        pre = itrow;
    }

    std::list<CRowNode<T> >::iterator newitrow = rl.insert(itrow, CRowNode<T>(r));
    newitrow->AddElementNode(c, d);
}

template<typename T>
void CSparseMatrixStdList<T>::Clear(void)
{
    rows = 0;
    columns = 0;
    rl.clear();
}

template<typename T>
void CSparseMatrixStdList<T>::Transpose(CSparseMatrixStdList<T>& o) const
{
    o.Clear();
    o.rows = columns;
    o.columns = rows;

    for (std::list<CRowNode<T> >::const_iterator itrow = rl.begin();
        itrow != rl.end();
        ++itrow) {
        for (std::list<CColumnNode<T> >::const_iterator itcol = itrow->cl.begin();
            itcol != itrow->cl.end();
            ++itcol) {
            o._AddElement(itcol->column, itrow->row, itcol->data);
        }
    }
}

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

    cout << "Now, please enter the elements INCREAMENTLY (row column data) " << endl;

    for (int i = 0; i < n; i++) {
        cout << "No. " << (i + 1) << ": ";

        T v;
        is >> r >> c >> v;
        if (r < 1 || c < 1 || r > o.rows || c > o.columns || n < 1) {
            throw new OutOfRange();
        }

        bool inserted = false;
        CColumnNode<T> cnode(c, v);

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
            CRowNode<T> rnode(r);
            o.rl.push_back(rnode);
            o.rl.back().cl.push_back(cnode);
        }
    }

    return is;
}
