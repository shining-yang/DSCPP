//
// File: 09_MaxHeap.cpp
// Shining Yang <y.s.n@live.com>, 2014-12-08
//
#include "MaxHeap.h"
using namespace DSCPP::PriorityQueue;

int main(int arg, char* argv[])
{
    int dummy;
    MaxHeap<int> mh;

    mh.Insert(9).Insert(3).Insert(8).Insert(2).Insert(7).Insert(6).Insert(4).Insert(5).Insert(1);
    cout << mh << endl;
    mh.PrintTreeVertically(cout, 60);

    mh.DeleteMax(dummy);
    cout << mh << endl;
    mh.PrintTreeVertically(cout, 60);

    mh.DeleteMax(dummy);
    cout << mh << endl;
    mh.PrintTreeVertically(cout, 40);

    mh.DeleteMax(dummy);
    cout << mh << endl;
    mh.PrintTreeVertically(cout, 40);

    return 0;
}