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
    Matrix<int> m1(3, 4);
//     m1(0, 0) = 1;
//     m1(0, 2) = 3;

    int d = m1(0, 2);
    cout << "d: " << d << endl;

    m1.Output(cout);
    return 0;
}