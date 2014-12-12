//
// File: 09_Heap.cpp
// Shining Yang <y.s.n@live.com>, 2014-12-12
//
#include <iostream>
#include "Heap.h"

using namespace std;
using namespace DSCPP::Heap;

int main(int argc, char* argv[])
{
    int dummy;
    Heap<int> hp;

    hp.Insert(10).Insert(20).Insert(30).Insert(25).Insert(3).Insert(6).Insert(8);
    cout << "Heap: " << hp << endl;
    hp.PrintTreeVertically(cout, 64);

    return 0;
}