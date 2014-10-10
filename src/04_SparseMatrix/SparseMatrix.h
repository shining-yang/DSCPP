//
// File: SparseMatrix.h
//
// Some operations on sparse matrix.
// NOTE: The row and column number of a matrix are counted from 1.
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
    friend istream& operator>>(istream& is, SparseMatrix<T>& m);
    friend ostream& operator<<(ostream& os, const SparseMatrix<T>& m);
    void Output(ostream& os) const;

protected:
    T _GetMatrixElements(int i, int j) const; // i, j are 1-based

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
    cout << "Provide info about rows, columns, none-zero elements:" << endl;

    int r, c, n;
    is >> r >> c >> n;
    if (n > m.capacity) {
        throw new OutOfRange();
    }

    m.rows = r;
    m.columns = c;
    m.size = n;

    cout << "Your inputs are accepted.\n"
        << "\trows: " << r
        << "\tcolumns: " << c
        << "\tnone-zero elements: " << n
        << endl;
        
    cout << "Enter the none-zero elements (row column value):" << endl;

    for (int i = 0; i < m.size; i++) {
        is >> r >> c >> n;
        if ((r > m.rows) || (c > m.columns)) {
            throw new OutOfBounds();
        }

        m.elements[i].r = r;
        m.elements[i].c = c;
        m.elements[i].v = n;
    }

    return is;
}

template<class T>
ostream& operator<<(ostream& os, const SparseMatrix<T>& m)
{
    cout << "Info about the sparse matrix:" << endl;
    cout << "Dimension: " << m.rows << " x " << m.columns << endl;
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
T SparseMatrix<T>::_GetMatrixElements(int i, int j) const // i, j are 1-based
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
            os << _GetMatrixElements(i, j) << " ";
        }
        os << endl;
    }
}

template<class T>
void SparseMatrix<T>::Transpose(SparseMatrix<T>& dm) const
{// 把*this 的转置结果送入b
    if (capacity < dm.capacity) {
        throw new OutOfMemory();
    }

    // 设置转置特征
    dm.columns = rows;
    dm.rows = columns;
    dm.size = size;

    // 初始化
    int *ColSize = new int[columns + 1];
    int *RowNext = new int[rows + 1];

    // 计算* this每一列的非0元素数
    for (int i = 1; i <= columns; i++)
        ColSize[i] = 0;
    for (int = 0; i < terms; i++)
        ColSize[a[i].c]++;

    // 给出b中每一行的起始点
    RowNext[1] = 0;
    for (int i = 2; i <= columns; i++)
        RowNext[i] = RowNext[i - 1] + ColSize[i - 1];

    // 执行转置操作
    for (int i = 0; i < terms; i++) {
        int j = RowNext[a[i].col]++; // 在b中的位置
        b.a[j].r = a[i].c;
        b.a[j].c = a[i].r;
        b.a[j].v = a[i].v;
    }

    delete[] ColSize;
    delete[] RowNext;
}

template<class T>
void SparseMatrix<T>::Add(const SparseMatrix<T>& sm, SparseMatrix<T>& dm) const
{

}
