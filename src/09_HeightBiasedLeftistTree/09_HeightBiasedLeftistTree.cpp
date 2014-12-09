//
// File: 09_HeightBiasedLeftistTree.cpp
// Shining Yang <y.s.n@live.com>, 2014-12-09
//
#include <iostream>
#include "HeightBiasedLeftistTree.h"
using namespace std;
using namespace DSCPP::PriorityQueue;

int main(int argc, char* argv[])
{
    int dummy;
    MaxHBLT<int> mh, mh2;

    mh.Insert(2).Insert(9).Insert(3).Insert(6).Insert(1);
    mh.DeleteMax(dummy);
    cout << "Print vertically: " << endl;
    mh.PrintTreeVertically(cout, 64);

    mh.Clone(mh2);
    
    mh2.Insert(8).Insert(4);
    cout << "Print vertically: " << endl;
    mh2.PrintTreeVertically(cout, 64);

    int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    mh2.Initialize(a, sizeof(a) / sizeof(a[0]));
    cout << "Print vertically: " << endl;
    mh2.PrintTreeVertically(cout, 64);

    return 0;
}