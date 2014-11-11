//
// File: 07_SkipList.cpp
// Simple test case for skip list data structure
// 2014-11-11, Shining Yang <y.s.n@live.com>
//
#include "SkipList.h"
#include <iostream>

int main(int argc, char* argv[])
{
    DSCPP::SkipList::SkipList<int, int> sl(10000);
    sl.Insert(10).Insert(20).Insert(30).Insert(40).Insert(50);
    sl.Insert(5);
    sl.Insert(15);
    sl.Insert(25);
    sl.Insert(35);
    sl.Insert(45);

    std::cout << sl << std::endl;
    return 0;
}