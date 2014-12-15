//
// File: BinarySearchTree.h
// Binary search tree. (NO duplicate element.)
// Shining Yang <y.s.n@live.com>, 2014-12-15
//
#pragma once

#include "../Utility/Exception.h"
#include "../08_BinaryTree/BinaryTree.h"

using namespace DSCPP::Utils;
using namespace DSCPP::BinaryTree;

namespace DSCPP { namespace SearchTree {

template<typename E, typename K>
class BSTree : public DSCPP::BinaryTree::BinaryTree<E> {
public:
    BSTree() {}
    ~BSTree() {}

public:
    bool Search(const K& k, E& e) const;
    BSTree<E, K>& Insert(const E& e);
    BSTree<E, K>& Delete(const K& k, E& e);

private:
};

template<typename E, typename K>
bool BSTree<E, K>::Search(const K& k, E& e) const
{
    const BinaryTreeNode<E>* r = Root();
    while (!r) {
        if (k < r->data) {
            r = r->lchild;
        } else if (k > r->data) {
            r = r->rchild;
        } else {
            e = r->data;
            return true;
        }
    }

    return false;
}

template<typename E, typename K>
BSTree<E, K>& BSTree<E, K>::Insert(const E& e)
{
    return *this;
}

template<typename E, typename K>
BSTree<E, K>& BSTree<E, K>::Delete(const K& k, E& e)
{
    return *this;
}

}}