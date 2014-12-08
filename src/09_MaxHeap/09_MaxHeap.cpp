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

    mh.Insert(10).Insert(3).Insert(12).Insert(15).Insert(2).Insert(8).Insert(20);
    cout << mh << endl;

    mh.Delete(dummy);
    cout << mh << endl;

    mh.Delete(dummy);
    cout << mh << endl;

    mh.Delete(dummy);
    cout << mh << endl;

    return 0;
}