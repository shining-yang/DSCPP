//
// File: matrix.h
//
// Simple operations on matrix. Indices on rows or columns are started from 1.
// Shining Yang <y.s.n@live.com>, 2014-09-30
//
#pragma once

#include <ostream>
using namespace std;
#include "../Utility/Exception.h"
using namespace DSCPP::Utils;

template<class T>
class Matrix
{
public:
    Matrix(int r = 0, int c = 0);
    Matrix(const Matrix<T>& m);
    ~Matrix();

public:
    int Rows() const { return row; }
    int Columns() const { return column; }
    const T& operator()(int i, int j) const;
    T& operator()(int i, int j);
    void Output(ostream& os) const;
    Matrix<T> Transpose() const;

    Matrix<T>& operator=(const Matrix<T>& m);
    Matrix<T>& operator+=(const Matrix<T>& m);
    Matrix<T> operator+() const;
    Matrix<T> operator-() const;
    Matrix<T> operator+(const Matrix<T>& m) const;
    Matrix<T> operator-(const Matrix<T>& m) const;
    Matrix<T> operator*(const Matrix<T>& m) const;

private:
    int row;
    int column;
    T* elements;
};

template<class T>
Matrix<T> Matrix<T>::Transpose() const
{
    int k = 0;
    Matrix<T> w(column, row);
    for (int j = 0; j < column; j++) {
        for (int i = 0; i < row; i++) {
            w.elements[k++] = elements[i * column + j];
        }
    }
    return w;
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m)
{
    if (this == &m) {
        return *this;
    }

    if (row * column != m.row * m.column) {
        delete[] elements;
        elements = new T[m.row * m.column];
    }

    row = m.row;
    column = m.column;
    for (int i = 0; i < row * column; i++) {
        elements[i] = m.elements[i];
    }

    return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& m)
{
    if (row != m.row || column != m.column) {
        throw new SizeNotMatch();
    }

    for (int i = 0; i < row * column; i++) {
        elements[i] += m.elements[i];
    }

    return *this;
}

template<class T>
Matrix<T> Matrix<T>::operator+() const
{
    Matrix<T> w(row, column);
    for (int i = 0; i < row * column; i++) {
        w.elements[i] = +elements[i];
    }
    return w;
}

template<class T>
Matrix<T> Matrix<T>::operator-() const
{
    Matrix<T> w(row, column);
    for (int i = 0; i < row * column; i++) {
        w.elements[i] = -elements[i];
    }
    return w;
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& m) const
{
    if (row != m.row || column != m.column) {
        throw new SizeNotMatch();
    }

    Matrix<T> w(row, column);
    for (int i = 0; i < row * column; i++) {
        w.elements[i] = elements[i] + m.elements[i];
    }

    return w;
}

template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& m) const
{
    if (row != m.row || column != m.column) {
        throw new SizeNotMatch();
    }

    Matrix<T> w(row, column);
    for (int i = 0; i < row * column; i++) {
        w.elements[i] = elements[i] - m.elements[i];
    }

    return w;
}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& m) const
{
    if (column != m.row) {
        throw new SizeNotMatch();
    }

    Matrix<T> w(row, m.column);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < m.column; j++) {
            T t = elements[i * column + 0] * m.elements[0 * m.column + j];
            for (int k = 1; k < column; k++) {
                t += (elements[i * column + k] * m.elements[k * m.column + j]);
            }
            w.elements[i * m.column + j] = t;
        }
    }

    return w;
}

template<class T>
ostream& operator<<(ostream& os, const Matrix<T>& m)
{
    m.Output(os);
    return os;
}

template<class T>
void Matrix<T>::Output(ostream& os) const
{
    for (int i = 0; i < row * column; i++) {
        os << elements[i] << " ";
        if ((i + 1) % column == 0) {
            os << std::endl;
        }
    }
}

template<class T>
Matrix<T>::Matrix(int r /*= 0*/, int c /*= 0*/)
{
    if (r < 0 || c < 0) {
        throw new BadInitializer();
    }

    if ((!r || !c) && (r || c)) {
        throw new BadInitializer();
    }

    row = r;
    column = c;
    elements = new T[row * column];
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& m)
{
    row = m.row;
    column = m.column;
    elements = new T[row * column];

    for (int i = 0; i < row * column; i++) {
        elements[i] = m.elements[i];
    }
}

template<class T>
Matrix<T>::~Matrix()
{
    delete[] elements;
}

// indices of (i, j) are started from 1
template<class T>
const T& Matrix<T>::operator()(int i, int j) const
{
    if (i < 1 || i > row || j < 1 || j > column) {
        throw new OutOfBounds();
    }

    return elements[(i - 1) * column + (j - 1)];
}

// indices of (i, j) are started from 1
template<class T>
T& Matrix<T>::operator()(int i, int j)
{
    return const_cast<T&>(static_cast<const Matrix<T>&>(*this)(i, j));
}


//
// Class SquareMatrix
//
class SquareMatrix : public Matrix<double> {
public:
    SquareMatrix(int n = 0) : Matrix<double>(n, n) {}
    ~SquareMatrix();

public:
    // 求行列式（Determinant）的值
    double CalcDeterminant();
    // 求代数余子式
    double CalcCofactor(int i, int j);
    // 求伴随矩阵（Adjoint matrix）
    SquareMatrix<double> BuildAdjointMatrix() const;
    // 求逆矩阵（Inverse matrix）
    SquareMatrix<double> BuildInverseMatrix() const;
};