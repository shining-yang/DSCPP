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
    cout << sm;
    sm.Output(cout);

    return 0;
}