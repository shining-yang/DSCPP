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
    BinaryTree<char> bt;
    BinaryTree<char> x, a, b, c, d, e, f, g, h, i, j, T;
    a.MakeTree('A', x, x);
    b.MakeTree('B', x, x);
    c.MakeTree('C', a, x);
    d.MakeTree('D', b, x);
    e.MakeTree('E', c, d);
    f.MakeTree('F', x, x);
    g.MakeTree('G', x, x);
    h.MakeTree('H', f, g);
    i.MakeTree('I', x, h);
    j.MakeTree('J', i, x);
    T.MakeTree('X', e, j);

    T.InOrder(PrintNode); cout << endl;
    T.PreOrder(PrintNode); cout << endl;
    T.PostOrder(PrintNode); cout << endl;
    T.LevelOrder(PrintNode); cout << endl;

    cout << "Elements count: " << T.GetCount() << endl;
    cout << "Height: " << T.GetHeight() << endl;

    cout << "Print horizontally:" << endl;
    T.PrintHorizontally(4);

    cout << "Print vertically:" << endl;
    T.PrintVertically(80);

    BinaryTree<char> X;
    T.Clone(X);
    cout << "Print vertically (clone):" << endl;
    X.PrintVertically(64);
    return 0;
}