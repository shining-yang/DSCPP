//
// File: matrix.h
//
// Simple operations on matrix. Indices on rows or columns are 0 based.
// Shining Yang <y.s.n@live.com>, 2014-09-30
//
#pragma once

#include <ostream>
using namespace std;

template<class T>
class Matrix
{
public:
    Matrix(int r = 0, int c = 0);
    Matrix(const Matrix<T>& obj);
    ~Matrix();

public:
    int Rows() const { return row; }
    int Columns() const { return column; }
    const T& operator()(int i, int j) const;
    T& operator()(int i, int j);

    void Output(ostream& os) const;

private:
    int row;
    int column;
    T* elements;
};

template<class T>
void Matrix<T>::Output(ostream& os) const
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            os << elements[i * column + j] << " ";
        }
        os << std::endl;
    }
}

template<class T>
Matrix<T>::Matrix(int r /*= 0*/, int c /*= 0*/)
{
    row = r;
    column = c;
    elements = new T[row * column];
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& obj)
{
    row = obj.row;
    column = obj.column;
    elements = new T[row * column];

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            elements[i][j] = obj(i, j);
        }
    }
}

template<class T>
Matrix<T>::~Matrix()
{
    delete[] elements;
}

template<class T>
const T& Matrix<T>::operator()(int i, int j) const
{
    return elements[i * column + j];
}

template<class T>
T& Matrix<T>::operator()(int i, int j)
{
    return const_cast<T&>(static_cast<const Matrix<T>&>(*this)(i, j));
}