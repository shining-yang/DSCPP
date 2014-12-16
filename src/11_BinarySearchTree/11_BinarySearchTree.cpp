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
    BSTree<int, int> T;
    T.Insert(4).Insert(9).Insert(2).Insert(7).Insert(8).Insert(1)
        .Insert(3).Insert(6).Insert(0);

    cout << "Found: " << (T.Search(4, dummy) ? "Yes" : "No") << endl;
    cout << "Found: " << (T.Search(5, dummy) ? "Yes" : "No") << endl;
    cout << "Print out the tree:" << endl;
    T.PrintVerticallyWithLine(76);

    BSTree<char, int> T2;
    cout << "Another binary search tree:" << endl;
    T2.Insert('A').Insert('B').Insert('C').Insert('D').Insert('E');
    T2.PrintVerticallyWithLine(76);
    T2.OutputAscending();
    cout << endl;

    char ch;
    T2.Delete('A', ch).Delete('D', ch);
    T2.PrintVerticallyWithLine(76);
    T2.OutputAscending();
    cout << endl;

    T2.Insert('D').Insert('A').Insert('X').Insert('Y').Insert('P').Insert('Q');
    T2.PrintVerticallyWithLine(76);
    T2.OutputAscending();
    cout << endl;
    return 0;
}