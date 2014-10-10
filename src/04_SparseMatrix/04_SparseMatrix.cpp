//
// File: SparseMatrix.cpp
//
// 
#include "SparseMatrix.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    SparseMatrix<int> sm;

    cin >> sm;
    cout << sm << endl;
    sm.Output(cout);

    SparseMatrix<int> tsm;
    sm.Transpose(tsm);
    cout << tsm << endl;
    tsm.Output(cout);
    return 0;
}