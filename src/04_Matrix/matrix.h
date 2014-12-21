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
#include "../Utility/Misc.h"
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

protected:
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
    SquareMatrix(int n = 0) : Matrix<double>(n, n), determinant(0.0) {}
    SquareMatrix(const SquareMatrix& sm) {
        determinant = sm.determinant;
    }
    SquareMatrix& operator=(const SquareMatrix& sm) {
        if (this != &sm) {
            determinant = sm.determinant;
        }
        return *this;
    }
    ~SquareMatrix() {}

public:
    // 求行列式（Determinant）的值
    double CalcDeterminant();
    // 求代数余子式
    double CalcCofactor(int i, int j);
    // 求伴随矩阵（Adjoint matrix）
    SquareMatrix BuildAdjointMatrix();
    // 生成余子式矩阵
    SquareMatrix SquareMatrix::BuildCofactorMatrix(int i, int j);
    // 求逆矩阵（Inverse matrix）
    SquareMatrix BuildInverseMatrix();

protected:
    int _CalcReverseOrderCount(int index[], int n);
    void _PermuteVisit(int index[], int n, int k, void (*v)(SquareMatrix&, int*, int));
    static void _PermuteVisitor(SquareMatrix& m, int index[], int n);

protected:
    double determinant;
};

SquareMatrix SquareMatrix::BuildInverseMatrix()
{
    SquareMatrix sm;

    return sm;
}

SquareMatrix SquareMatrix::BuildAdjointMatrix()
{
    int n = Rows();
    SquareMatrix sm(n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            sm(i, j) = CalcCofactor(i, j);
        }
    }
    
    return sm;
}

// 余子式（矩阵）
SquareMatrix SquareMatrix::BuildCofactorMatrix(int I, int J)
{
    int n = Rows() - 1;
    if (n <= 0) {
        throw new InvalideArgument();
    }

    int k = 0;
    SquareMatrix sm(n);
    for (int i = 1; i <= Rows(); i++) {
        if (i == I) { continue; }
        for (int j = 1; j <= Columns(); j++) {
            if (j == J) { continue; }
            elements[k++] = sm(i, j);
        }
    }

    return sm;
}

// 代数余子式（行列式值）
double SquareMatrix::CalcCofactor(int i, int j)
{
    SquareMatrix cm = BuildCofactorMatrix(i, j);
    if ((i + j) % 2 == 0) {
        return cm.CalcDeterminant();
    } else {
        return -cm.CalcDeterminant();
    }
}

double SquareMatrix::CalcDeterminant()
{
    int n = Rows();
    int* index = new int[n];
    for (int i = 0; i < n; i++) {
        index[i] = i + 1; // matrix's indices start from 1
    }

    determinant = 0.0; // reset before calculate
    _PermuteVisit(index, n, 0, _PermuteVisitor); // calculate in permute recursion
    return determinant;
}

void SquareMatrix::_PermuteVisit(int index[], int n, int k, void (*v)(SquareMatrix&, int*, int))
{
    if (k == n - 1) {
        v(*this, index, n);
    } else {
        for (int i = k; i < n; i++) {
            Swap(index[k], index[i]);
            _PermuteVisit(index, n, k + 1, v);
            Swap(index[k], index[i]);
        }
    }
}

void SquareMatrix::_PermuteVisitor(SquareMatrix& m, int index[], int n)
{
    double result = 1.0;
    for (int i = 0; i < n; i++) {
        result *= m(i + 1, index[i]); // matrix's indices start from 1
    }

    if (m._CalcReverseOrderCount(index, n) % 2 == 0) {
        m.determinant += result;
    } else {
        m.determinant -= result;
    }
}

int SquareMatrix::_CalcReverseOrderCount(int index[], int n)
{
    int count = 0; // reversed indices order counter
    for (int i = n - 1; i > 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            if (index[j] > index[i]) {
                count++;
            }
        }
    }

//     for (int i = 0; i < n; i++) {
//         cout << index[i] << " ";
//     }
//     cout << ": " << count << endl;

    return count;
}
