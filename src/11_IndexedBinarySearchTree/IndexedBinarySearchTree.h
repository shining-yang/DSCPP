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

template<typename E, typename K>
class IndexedBSTreeNodeInfo {
public:
    IndexedBSTreeNodeInfo() {}
    IndexedBSTreeNodeInfo(const E& data, int sz) : d(data), s(sz) {}

    operator K() const {
        return operator K(E);
    }

    bool operator==(const IndexedBSTreeNodeInfo<E, K>& obj) const {
        return d == obj.d;
    }

    bool operator!=(const IndexedBSTreeNodeInfo<E, K>& obj) const {
        return !operator==(obj);
    }

    bool operator<(const IndexedBSTreeNodeInfo<E, K>& obj) const {
        return d < obj.d;
    }

    bool operator>(const IndexedBSTreeNodeInfo<E, K>& obj) const {
        return d > obj.d;
    }

    bool operator<=(const IndexedBSTreeNodeInfo<E, K>& obj) const {
        return !operator>(obj);
    }

    bool operator>=(const IndexedBSTreeNodeInfo<E, K>& obj) const {
        return !operator<(obj);
    }

    template<typename Et, typename Kt>
    friend class IndexedBSTree;

    template<typename Et, typename Kt>
    friend ostream& operator<<(ostream& os, const IndexedBSTreeNodeInfo<Et, Kt>& obj);

private:
    E d;    // actual data member
    int s;  // left size (number of left tree nodes + 1)
};

template<typename E, typename K>
ostream& operator<<(ostream& os, const IndexedBSTreeNodeInfo<E, K>& obj)
{
    os << obj.s << ":" << obj.d;
    return os;
}

template<typename E, typename K>
class IndexedBSTree :
    public DSCPP::BinaryTree::BinaryTree<IndexedBSTreeNodeInfo<E, K> > {

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
    const BinaryTreeNode<IndexedBSTreeNodeInfo<E, K> >* p = Root();
    while (p) {
        if (k < p->data.d) {
            p = p->lchild;
        } else if (k > p->data.d) {
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