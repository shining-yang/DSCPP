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
using namespace DSCPP::BinaryTree;

namespace DSCPP { namespace SearchTree {

template<typename T>
class IndexedBSTreeNodeInfo {
public:
    IndexedBSTreeNodeInfo() {}
    IndexedBSTreeNodeInfo(const T& data, int sz) : d(data), s(sz) {}

    bool operator==(const IndexedBSTreeNodeInfo<T>& obj) const {
        return d == obj.d;
    }

    bool operator!=(const IndexedBSTreeNodeInfo<T>& obj) const {
        return !operator==(obj);
    }

    bool operator<(const IndexedBSTreeNodeInfo<T>& obj) const {
        return d < obj.d;
    }

    bool operator>(const IndexedBSTreeNodeInfo<T>& obj) const {
        return d > obj.d;
    }

    bool operator<=(const IndexedBSTreeNodeInfo<T>& obj) const {
        return !operator>(obj);
    }

    bool operator>=(const IndexedBSTreeNodeInfo<T>& obj) const {
        return !operator<(obj);
    }

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
class IndexedBSTree :
    public DSCPP::BinaryTree::BinaryTree<IndexedBSTreeNodeInfo<E> > {

public:
    IndexedBSTree() {}
    ~IndexedBSTree() {}

public:
    // Search for element by key. Return true on success, false otherwise
    bool Search(const K& k, E& e) const;
    IndexedBSTree<E, K>& Insert(const E& e);
    IndexedBSTree<E, K>& Delete(const K& k, E& e);
    // Search for the i-th element.
    bool IndexSearch(int i, E& e) const;
    // Delete the i-th element.
    IndexedBSTree<E, K>& IndexDelete(int i, E& e);
};

template<typename E, typename K>
bool DSCPP::SearchTree::IndexedBSTree<E, K>::Search(const K& k, E& e) const
{
    BinaryTreeNode<IndexedBSTreeNodeInfo<E> >* p = Root();
    while (p) {
        if (k < p->lchild) {
            p = p->lchild;
        } else if (k > p->data) {
            p = p->rchild;
        } else {
            e = p->data.d;
            return true;
        }
    }

    return false;
}

template<typename E, typename K>
IndexedBSTree<E, K>& DSCPP::SearchTree::IndexedBSTree<E, K>::Insert(const E& e)
{

}

template<typename E, typename K>
IndexedBSTree<E, K>& DSCPP::SearchTree::IndexedBSTree<E, K>::Delete(const K& k, E& e)
{

}

template<typename E, typename K>
bool DSCPP::SearchTree::IndexedBSTree<E, K>::IndexSearch(int i, E& e) const
{

}

template<typename E, typename K>
IndexedBSTree<E, K>& DSCPP::SearchTree::IndexedBSTree<E, K>::IndexDelete(int i, E& e)
{

}

}}