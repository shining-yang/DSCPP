//
// File: SparseMatrixLinked.h
//
// Sparse matrix implemented by linked list.
//
#pragma once

#include <iostream>
using namespace std;

#include "../03_SinglyLinkedList/SinglyLinkedList.h"
#include "../Utility/Exception.h"
using namespace DSCPP::Utils;

// class declarations
template<class T> class ColumnNode;
template<class T> class RowNode;
template<class T> class SparseMatrixLinked;

//
//------------------------------------------------------------------------------
//
template<class T>
class ColumnNode {
public:
    bool operator==(const ColumnNode<T>& o) const {
        return col == o.col;
    }

    bool operator!=(const ColumnNode<T>& o) const {
        return !operator==(o);
    }

    void Output(ostream& os) const {
        os << "column: " << col << "value: " << val;
    }

private:
    int col;
    T   val;

    friend class RowNode < T > ;
    friend class SparseMatrixLinked < T > ;
};

template<class T>
ostream& operator<<(ostream& os, const ColumnNode<T>& o)
{
    o.Output(os);
    return os;
}

//
//------------------------------------------------------------------------------
//
template<class T>
class RowNode {
public:
    bool oprator==(const RowNode<T>& o) const {
        return row == o.row;
    }

    bool operator!=(const RowNode<T>& o) const {
        return !operator==(o);
    }

    void Output(ostream& os) const {
        os << "Row: " << endl;
        os << chain_col;
    }

private:
    int row;
    Chain<ColumnNode<T> > chain_col;

    friend class SparseMatrixLinked < T > ;
};

template<class T>
ostream& operator<<(ostream& os, const RowNode<T>& o)
{
    o.Output(os);
    return os;
}

//
//------------------------------------------------------------------------------
//
template<class T>
class SparseMatrixLinked {
public:
    SparseMatrixLinked(int r, int c);

public:
    template<class T>
    friend istream& operator>>(istream& is, SparseMatrixLinked<T>& o);

    template<class T>
    friend ostream& operator<<(ostream& os, const SparseMatrixLinked<T>& o);

    void Output(ostream& os) const {
        os << "Sparse matrix: " << rows << " x " << columns << endl;
        os << chain_row;
    }

private:
    int rows;
    int columns;
    Chain<RowNode<T> > chain_row;
};

template<class T>
friend istream& operator>>(istream& is, SparseMatrixLinked<T>& o)
{
    cout << "First, provide info about rows, columns, none-zero elements:" << endl;

    int r, c, n;
    is >> r >> c >> n;

    if (r < 1 || c < 1 || n < 1) {
        throw new InvalideArgument();
    }

    o.rows = r;
    o.columns = c;

    cout << "Your inputs are accepted. "
        << "rows: " << r
        << "columns: " << c
        << "none-zero elements: " << n
        << endl;

    cout << "Second, enter the none-zero elements INCREAMENTLY (row column value):" << endl;

    int nCurRow = -1;
    int nPreRow = -1;

    for (int i = 0; i < n; i++) {
        cout << "No. " << (i + 1) << ": ";

        T v;
        is >> r >> c >> n;
        if (r < 1 || c < 1 || r > o.rows || c > o.columns || v == 0) {
            throw new InvalideArgument();
        }

        ColumnNode<T> cnode;
        cnode.col = c;
        cnode.val = v;

        RowNode<T> rnode;
        rnode.row = r;

        int k = o.chain_row.Length();

        if (nPreRow != r) { // new row occurred
            o.chain_row.Insert(k, rnode);
            nPreRow = r;
        }

        RowNode<T> rx;
        o.chain_row.Find(k, rx);
        int l = rx.chain_col.Length();
        rx.chain_col.Insert(l, cnode);
    }
}

#if 0
template<class T>
ostream& SparseMatrixLinked::operator<<(ostream& os, const SparseMatrixLinked<T>& o)
{
    os << "Info about the sparse matrix (linked):" << endl;
    os << "Dimension: " << o.rows << " x " << o.columns << endl;
    for (Chain<RowNode<T> >::Iterator it = o.chain_row.Begin();
        it != o.chain_row.End();
        ++it) {
        os << "Row " << (*it).row << ": " << endl;

        for (Chain<ColumnNode<T> >::Iterator itcol = (*it).chain_col.Begin();
            itcol != (*it).chain_col.End();
            ++itcol) {
            os << (*itcol).col << " [" << (*itcol).val << "], ";
        }

        os << endl;
    }

    return os;
}
#endif

template<class T>
ostream& operator<<(ostream& os, const SparseMatrixLinked<T>& o)
{
    o.Output(os);
    return os;
}

template<class T>
SparseMatrixLinked<T>::SparseMatrixLinked(int r, int c)
{
    if (r < 1 || c < 1) {
        throw new BadInitializer();
    }

    rows = r;
    columns = c;
}
