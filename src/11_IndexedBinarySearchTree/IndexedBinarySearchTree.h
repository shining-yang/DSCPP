//
// File: IndexedBinarySearchTree.h
// Indexed binary search tree. No duplicate elements are allowed.
// Shining Yang <y.s.n@live.com>, 2014-12-16
//
#pragma once

#include <iostream>
#include "../Utility/Exception.h"
#include "../08_BinaryTree/BinaryTree.h"

using namespace std;
using namespace DSCPP::Utils;

namespace DSCPP { namespace SearchTree {

template<typename T>
class IndexedBSTreeNodeInfo {
public:
    IndexedBSTreeNodeInfo() {}
    IndexedBSTreeNodeInfo(const T& data, int sz) : d(data), s(sz) {}

    template<typename E, typename K> friend class IndexedBSTree;
    friend ostream& operator<<(ostream& os, const IndexedBSTreeNodeInfo<T>& obj);

private:
    T d;    // actual data member
    int s;  // left size (number of left tree nodes + 1)
};

template<typename T>
ostream& operator<<(ostream& os, const IndexedBSTreeNodeInfo<T>& obj)
{
    os << s << ":" << d;
    return os;
}

template<typename E, typename K>
class IndexedBSTree : public DSCPP::BinaryTree::BinaryTree<E> {

};

}}