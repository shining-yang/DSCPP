//
// File: 11_BinarySearchTree.cpp
// Shining Yang <y.s.n@live.com>, 2014-12-15
//
#include "BinarySearchTree.h"

using namespace DSCPP::SearchTree;

int main(int argc, char* argv[])
{
    int dummy;
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

    // DupBSTree
    DupBSTree<int, int> TT;
    TT.Insert(5).Insert(4).Insert(9).Insert(2).Insert(8).Insert(2).Insert(5);
    TT.PrintVerticallyWithLine(64);
    TT.OutputAscending();
    cout << endl;

    TT.Delete(2, dummy).Delete(8, dummy).Insert(7).Delete(5, dummy).Insert(7);
    TT.PrintVerticallyWithLine(64);
    TT.OutputAscending();
    cout << endl;

    cout << "Remove max elements:" << endl;
    TT.DeleteMax(dummy);
    cout << dummy << endl;
    TT.DeleteMax(dummy);
    cout << dummy << endl;
    TT.DeleteMax(dummy);
    cout << dummy << endl;
    TT.OutputAscending();
    cout << endl;

    cout << "Remove min elements:" << endl;
    TT.DeleteMin(dummy);
    cout << dummy << endl;
    TT.DeleteMin(dummy);
    cout << dummy << endl;
    TT.OutputAscending();
    cout << endl;

    return 0;
}