//
// File: 10_WinnerTree.cpp
// Shining Yang <y.s.n@live.com>, 2014-12-23
//
#include <iostream>
#include "WinnerTree.h"

using namespace std;
using namespace DSCPP::WinnerTree;

template<typename T>
int Win(T a[], int i, int j)
{
    return (a[i] > a[j]) ? i : j;
}

int main(int argc, char* argv[])
{
    WinnerTree<int> wt;
    int a[] = { 1, 4, 5, 6, 9, 2, 3, 7, 8 };
    wt.Initialize(a - 1, sizeof(a) / sizeof(a[0]) + 1, Win);

    cout << "The winner is: " << a[wt.Winner()] << endl;
    return 0;
}