//
// File: 04_matrix.cpp
//
// Shining Yang <y.s.n@live.com>, 2014-09-30
//

#include <iostream>
#include "matrix.h"
using namespace std;

template<typename T>
void OutputMatrixElement(const Matrix<T>& m, int i, int j)
{
    // i, j are 0-based, different from Matrix
    if ((i >= m.Rows()) || (j >= m.Columns())) {
        return;
    }

    cout << m(i + 1, j + 1) << " ";
}

template<typename T>
void OutputAtSubscriptSum(const Matrix<T>& m, int n, bool ascending)
{
    for (int i = 0; i <= n; i++) {
        if (ascending) {
            OutputMatrixElement(m, i, n - i);
        } else {
            OutputMatrixElement(m, n - i, i);
        }
    }
}

template<typename T>
void ZigzagOutput(const Matrix<T>& m)
{
    int total = m.Rows() - 1 + m.Columns() - 1;
    bool ascending = false;
    for (int i = 0; i <= total; i++) {
        OutputAtSubscriptSum(m, i, ascending);
        ascending = !ascending;
    }
}

int main(int argc, char* argv[])
{
    Matrix<int> m1(2, 3);
    m1(1, 1) = 1;
    m1(1, 2) = 2;
    m1(1, 3) = 3;
    m1(2, 1) = 2;
    m1(2, 2) = 1;
    m1(2, 3) = 4;

    const Matrix<int> cm1 = m1;
    cm1.Output(cout);

    Matrix<int> m2(3, 1);
    m2(1, 1) = 0;
    m2(2, 1) = 1;
    m2(3, 1) = 2;

    Matrix<int> m3 = m1 * m2;

    cout << "m1:" << endl << m1 << endl;
    cout << "m2:" << endl << m2 << endl;
    cout << "m3:" << endl << m3 << endl;

    Matrix<int> tm1 = m1.Transpose();
    cout << "tm1:" << endl << tm1 << endl;

    //---- Zigzag output
    char k = 'A';
    Matrix<char> mc(5, 5);
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            mc(i, j) = k++;
        }
    }
    cout << mc << endl;

    cout << "Zigzag output: ";
    ZigzagOutput(mc);
    cout << endl;
    return 0;
}