//
// File: 08_BinaryTree.cpp
// Shining Yang <y.s.n@live.com>, 2014-12-03
//
#include <iostream>
#include "BinaryTree.h"

using namespace std;
using namespace DSCPP::BinaryTree;

template<typename T>
void PrintNode(const BinaryTreeNode<T>* n)
{
    cout << n->Data() << " ";
}

int main(int argc, char* argv[])
{
    BinaryTree<int> bt;
    BinaryTree<int> x, a, b, c, d, e;
    a.MakeTree(10, x, x);
    b.MakeTree(20, x, x);
    c.MakeTree(30, a, x);
    d.MakeTree(40, b, x);
    e.MakeTree(50, c, d);

    e.InOrder(PrintNode); cout << endl;
    e.PreOrder(PrintNode); cout << endl;
    e.PostOrder(PrintNode); cout << endl;

    cout << "Elements count: " << e.GetCount() << endl;
    cout << "Height: " << e.GetHeight() << endl;

    return 0;
}