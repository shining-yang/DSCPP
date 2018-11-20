//
// File: SparseMatrix.h
//
// Some operations on sparse matrix.
// NOTE: The row and column number of a matrix are counted from 1.
//
// ATTENTION on C++ template friends, for more details on C++ syntax, see:
// http://msdn.microsoft.com/en-us/library/f1b2td24.aspx
//
// Shining Yang <y.s.n@live.com>, 2014-10-09
//
#pragma once

#include <iostream>
#include "../Utility/Exception.h"
using namespace std;
using namespace DSCPP::Utils;

template<class T> class SparseMatrix;

template<class T>
class Term {
    friend class SparseMatrix<T>;
    template<class E> friend istream& operator>>(istream&, SparseMatrix<E>&);
    template<class E> friend ostream& operator<<(ostream&, const SparseMatrix<E>&);
private:
    int r; // row No.
    int c; // column No.
    T   v; // value
};

template<class T>
class SparseMatrix {
public:
    SparseMatrix(int c = 16);
    ~SparseMatrix();

public:
    //
    // Transpose this sparse matrix to an existing one. Since copy-constructor
    // here might be less efficient.
    // If that matrix does not have enough memory to hold the transposed matrix,
    // we'll throw an exception rather than re-allocate memory for brevity.
    //
    void Transpose(SparseMatrix<T>& dm) const;

    // *this + sm --> dm
    void Add(const SparseMatrix<T>& sm, SparseMatrix<T>& dm) const;

    // I/O operators
    template<class E> friend istream& operator>>(istream&, SparseMatrix<E>&);
    template<class E> friend ostream& operator<<(ostream&, const SparseMatrix<E>&);
    void Output(ostream& os) const;

protected:
    T _GetElementContent(int i, int j) const; // i, j are 1-based
    void _Append(const Term<T>& e);

private:
    int capacity;
    int size;
    int rows;
    int columns;
    Term<T>* elements;
};

template<class T>
istream& operator>>(istream& is, SparseMatrix<T>& m)
{
    cout << "First, provide info about rows, columns, none-zero elements:" << endl;

    int r, c, n;
    is >> r >> c >> n;

    if (r < 1 || c < 1 || n < 1) {
        throw new InvalideArgument();
    }

    if (n > m.capacity) {
        throw new OutOfRange();
    }

    m.rows = r;
    m.columns = c;
    m.size = n;

    cout << "Your inputs are accepted. "
        << "rows: " << r
        << ", columns: " << c
        << ", none-zero elements: " << n
        << endl;

    cout << "Second, enter the none-zero elements INCREAMENTLY (row column value):" << endl;

    for (int i = 0; i < m.size; i++) {
        cout << "No. " << (i + 1) << ": ";

        T v;
        is >> r >> c >> v;
        if (r < 1 || c < 1 || r > m.rows || c > m.columns || v == 0) {
            throw new InvalideArgument();
        }

        m.elements[i].r = r;
        m.elements[i].c = c;
        m.elements[i].v = v;
    }

    return is;
}

template<class T>
ostream& operator<<(ostream& os, const SparseMatrix<T>& m)
{
    os << "Info about the sparse matrix:" << endl;
    os << "Dimension: " << m.rows << " x " << m.columns << endl;
    for (int i = 0; i < m.size; i++) {
        if (i > 0) {
            os << ", ";
        }
        os << "[" << m.elements[i].r << "," << m.elements[i].c << "] " << m.elements[i].v;
    }

    return os;
}

template<class T>
SparseMatrix<T>::SparseMatrix(int c /*= 16*/)
{
    if (c < 1) {
        throw new BadInitializer();
    }

    elements = new Term<T>[c];
    capacity = c;
    size = 0;
    rows = 0;
    columns = 0;
}

template<class T>
SparseMatrix<T>::~SparseMatrix()
{
    delete[] elements;
}

template<class T>
T SparseMatrix<T>::_GetElementContent(int i, int j) const // i, j are 1-based
{
    for (int n = 0; n < size; n++) {
        if (elements[n].r == i && elements[n].c == j) {
            return elements[n].v;
        }
    }

    return 0; // 0 to T auto-conversion required
}

template<class T>
void SparseMatrix<T>::Output(ostream& os) const
{
    // Simple way just for diagnostics purpose
    for (int i = 1; i <= rows; i++) { // 1-based
        for (int j = 1; j <= columns; j++) {
            os << _GetElementContent(i, j) << " ";
        }
        os << endl;
    }
}

template<class T>
void SparseMatrix<T>::Transpose(SparseMatrix<T>& dm) const
{
    if (capacity > dm.capacity) {
        throw new OutOfMemory();
    }

    dm.columns = rows;
    dm.rows = columns;
    dm.size = size;

    int* ColSize = new int[columns + 1];
    int* RowNext = new int[columns + 1];

    for (int i = 1; i <= columns; i++) {
        ColSize[i] = 0;
    }

    for (int i = 0; i < size; i++) {
        ColSize[elements[i].c]++;
    }

    RowNext[1] = 0;
    for (int i = 2; i <= columns; i++) {
        RowNext[i] = RowNext[i - 1] + ColSize[i - 1];
    }

    for (int i = 0; i < size; i++) {
        int j = RowNext[elements[i].c]++;
        dm.elements[j].r = elements[i].c;
        dm.elements[j].c = elements[i].r;
        dm.elements[j].v = elements[i].v;
    }

    delete[] ColSize;
    delete[] RowNext;
}

template<class T>
void SparseMatrix<T>::_Append(const Term<T>& e)
{
    if (size >= capacity) {
        throw new OutOfBounds();
    }

    elements[size++] = e;
}

template<class T>
void SparseMatrix<T>::Add(const SparseMatrix<T>& sm, SparseMatrix<T>& dm) const
{
    if (rows != sm.rows || columns != sm.columns) {
        throw new SizeNotMatch();
    }

    dm.rows = rows;
    dm.columns = columns;
    dm.size = 0;

    int ptr1 = 0; // pointer for *this
    int ptr2 = 0; // pointer for sm

    while (ptr1 < size && ptr2 < sm.size) {
        int pos1 = elements[ptr1].r * columns + elements[ptr1].c;
        int pos2 = sm.elements[ptr2].r * columns + sm.elements[ptr2].c;

        if (pos1 < pos2) {
            dm._Append(elements[ptr1]);
            ptr1++;
        } else if (pos1 > pos2) {
            dm._Append(sm.elements[ptr2]);
            ptr2++;
        } else {
            if (elements[ptr1].v + sm.elements[ptr2].v != 0) {
                Term<T> e;
                e.r = elements[ptr1].r;
                e.c = elements[ptr1].c;
                e.v = elements[ptr1].v + sm.elements[ptr2].v;
                dm._Append(e);
            }

            ptr1++;
            ptr2++;
        }
    }

    while (ptr1 < size) {
        dm._Append(elements[ptr1]);
        ptr1++;
    }

    while (ptr2 < sm.size) {
        dm._Append(sm.elements[ptr2]);
        ptr2++;
    }
}
