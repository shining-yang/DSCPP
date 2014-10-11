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
friend istream& SparseMatrixLinked::operator>>(istream& is, SparseMatrixLinked<T>& o)
{
    cout << "First, provide info about rows, columns, none-zero elements:" << endl;
    
    int r, c, n;
    is >> r >> c >> n;

    if (r < 1 || c < 1 || n < 1) {
        throw new InvalideArgument();
    }

    this->rows = r;
    this->columns = c;

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
        if (r < 1 || c < 1 || r > this->rows || c > this->columns || v == 0) {
            throw new InvalideArgument();
        }

        ColumnNode<T> cnode;
        cnode.col = c;
        cnode.val = v;

        RowNode<T> rnode;
        rnode.row = r;

        nCurRow = r;
        if (nCurRow != nPreRow) { // new row occurred
            int k = this->chain_row.Length();
            this->chain_row.Insert(k, rnode);

            RowNode<T> rx;
            this->chain_row.Find(k, rx);
            int l = rx.chain_col.Length();
            rx.chain_col.Insert(l, cnode);

            nPreRow = nCurRow;
        }
    }
}

template<class T>
friend ostream& SparseMatrixLinked::operator<<(ostream& os, const SparseMatrixLinked<T>& o)
{

}

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
