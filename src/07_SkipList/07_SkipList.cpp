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
    std::cout << "NO.1 :" << std::endl << sl << std::endl;

    int dummy = 0;
    sl.Insert(18).Insert(17).Delete(18, dummy).Delete(15, dummy);
    sl.Delete(45, dummy).Insert(44).Insert(28).Delete(35, dummy).Insert(32);
    std::cout << "NO.2 :" << std::endl << sl << std::endl;
    return 0;
}
