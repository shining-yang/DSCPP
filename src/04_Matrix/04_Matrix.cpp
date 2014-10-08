//
// File: 04_matrix.cpp
//
// Shining Yang <y.s.n@live.com>, 2014-09-30
//

#include <iostream>
#include "matrix.h"
using namespace std;

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

    return 0;
}