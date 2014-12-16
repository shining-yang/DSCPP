//
// File: 11_IndexedBinarySearchTree.cpp
// Shining Yang <y.s.n@live.com>, 2014-12-16
//
#include <iostream>
#include "IndexedBinarySearchTree.h"

using namespace std;
using namespace DSCPP::SearchTree;

int main(int argc, char* argv[])
{
    int dummy;
    IndexedBSTree<int, int> ibst;
    IndexedBSTree<int, int> x, a, b, c, d;
    a.MakeTree(IndexedBSTreeNodeInfo<int, int>(1, 1), x, x);
    b.MakeTree(IndexedBSTreeNodeInfo<int, int>(4, 2), a, x);
    c.MakeTree(IndexedBSTreeNodeInfo<int, int>(8, 1), x, x);
    d.MakeTree(IndexedBSTreeNodeInfo<int, int>(6, 3), b, c);

    cout << "Found: " << (d.Search(1, dummy) ? "Yes" : "No") << endl;
    d.PrintVerticallyWithLine(64);
    return 0;
}