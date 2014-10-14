//
// File: 04_SparseMatrixStdList.cpp
//
#include "SparseMatrixStdList.h"

int main(int argc, char* argv[])
{
    CSparseMatrixStdList<int> sml;
    cin >> sml;
    cout << sml << endl;

    CSparseMatrixStdList<int> smlCopy;
    sml.Transpose(smlCopy);
    cout << smlCopy << endl;

    return 0;
}