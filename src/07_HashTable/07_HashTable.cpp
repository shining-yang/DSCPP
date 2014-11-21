//
// File: 07_HashTable.cpp
// Shining Yang <y.s.n@live.com>, 2014-11-21
//
#include "HashTable.h"

int main(int argc, char* argv[])
{
    int num = 16;
    DSCPP::Hash::HashTable<int, int> ht(16);
    for (int i = 0; i < num; i++) {
        ht.Insert(i);
    }

    cout << "Hash: " << ht << endl;
    return 0;
}