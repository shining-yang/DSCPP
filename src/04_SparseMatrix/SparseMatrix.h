//
// File: SparseMatrix.h
//
// Some operations on sparse matrix
//
// Shining Yang <y.s.n@live.com>, 2014-10-09
//
#pragma once

namespace DSCPP { namespace SparseMatrix {

template<class T>
class Term {
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
    void Transpose(SparseMatrix<T>& dm) const;
    void Add(const SparseMatrix<T>& sm, SparseMatrix<T>& dm) const;

private:
    int capacity;
    int size;
    int rows;
    int columns;
    Term<T>* elements;
};

template<class T>
SparseMatrix<T>::SparseMatrix(int c /*= 16*/)
{
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
void SparseMatrix<T>::Transpose(SparseMatrix<T>& dm) const
{

}

template<class T>
void SparseMatrix<T>::Add(const SparseMatrix<T>& sm, SparseMatrix<T>& dm) const
{

}

}}