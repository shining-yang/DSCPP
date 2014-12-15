//
// File: 11_BinarySearchTree.cpp
// Shining Yang <y.s.n@live.com>, 2014-12-15
//
#include "BinarySearchTree.h"
using namespace DSCPP::SearchTree;
int main(int argc, char* argv[])
{
    int dummy;
    BSTree<int, int> x;
    BSTree<int, int> T, A, B, C, D, E, F, G;
    A.MakeTree(5, x, x);
    B.MakeTree(6, x, x);
    C.MakeTree(7, x, x);
    D.MakeTree(8, A, x);
    E.MakeTree(9, B, C);
    F.MakeTree(1, D, E);
    G.MakeTree(2, x, x);

    T.MakeTree(0, F, G);
    T.PrintVerticallyWithLine(64);

    bool found = T.Search(4, dummy);
    cout << "Found: " << (found ? "Yes" : "No") << endl;
    return 0;
}