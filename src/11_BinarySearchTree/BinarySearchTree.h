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
    virtual BSTree<E, K>& Insert(const E& e);
    BSTree<E, K>& Delete(const K& k, E& e);
    
    BSTree<E, K>& DeleteMax(E& e);
    BSTree<E, K>& DeleteMin(E& e);

    void OutputAscending() const {
        InOrder(_PrintNode);
    }

protected:
    static void _PrintNode(const BinaryTreeNode<E>* p) {
        cout << p->data << ", ";
    }
};

template<typename E, typename K>
bool BSTree<E, K>::Search(const K& k, E& e) const
{
    const BinaryTreeNode<E>* r = Root();
    while (r) {
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
    K k = e; // auto conversion from E to K
    BinaryTreeNode<E>* p = Root();
    BinaryTreeNode<E>* pp = NULL; // parent
    while (p) {
        pp = p;
        if (k < p->data) {
            p = p->lchild;
        } else if (k > p->data) {
            p = p->rchild;
        } else {
            throw new ItemAlreadyExisted();
        }
    }
    
    BinaryTreeNode<E>* q = new BinaryTreeNode<E>(e);
    if (!pp) {
        Root() = q;
    } else {
        if (k < pp->data) {
            pp->lchild = q;
        } else {
            pp->rchild = q;
        }
    }

    return *this;
}

template<typename E, typename K>
BSTree<E, K>& BSTree<E, K>::Delete(const K& k, E& e)
{
    BinaryTreeNode<E>* p = Root();
    BinaryTreeNode<E>* pp = NULL; // parent

    while (p && (k != p->data)) {
        pp = p;
        if (k < p->data) {
            p = p->lchild;
        } else {
            p = p->rchild;
        }
    }

    if (!p) {
        throw new ItemNotExisted();
    }

    e = p->data;

    if (p->lchild && p->rchild) { // p has both left and right child
        BinaryTreeNode<E>* lp = p->lchild; // left child
        BinaryTreeNode<E>* lpp = p; // left child's parent
        while (lp->rchild) { // try to get the max node in the left child
            lpp = lp;
            lp = lp->rchild;
        }

        p->data = lp->data;
        p = lp;
        pp = lpp;
    }

    // Now, p has 1 child at most
    BinaryTreeNode<E>* c = p->lchild;
    if (!c) {
        c = p->rchild;
    }

    if (!pp) { // it's root
        Root() = c;
    } else if (pp->lchild == p) {
        pp->lchild = c;
    } else {
        pp->rchild = c;
    }

    delete p;
    return *this;
}

template<typename E, typename K>
BSTree<E, K>& BSTree<E, K>::DeleteMax(E& e)
{
    BinaryTreeNode<E>* p = Root();
    BinaryTreeNode<E>* pp = NULL;

    if (!p) {
        throw new ItemUnderFlow();
    }

    while (p->rchild) {
        pp = p;
        p = p->rchild;
    }

    if (!pp) { // it's the root node
        Root() = p->lchild;
    } else {
        pp->rchild = p->lchild;
    }

    e = p->data;
    delete p;
    return *this;
}

template<typename E, typename K>
BSTree<E, K>& BSTree<E, K>::DeleteMin(E& e)
{
    BinaryTreeNode<E>* p = Root();
    BinaryTreeNode<E>* pp = NULL;

    if (!p) {
        throw new ItemUnderFlow();
    }

    while (p->lchild) {
        pp = p;
        p = p->lchild;
    }

    if (!pp) {
        Root() = p->rchild;
    } else {
        pp->lchild = p->rchild;
    }

    e = p->data;
    delete p;
    return *this;
}

//
// DupBSTree
//
// Binary search tree that allow duplicate elements.
//
template<typename E, typename K>
class DupBSTree : public BSTree<E, K> {
public:
    DupBSTree() {}
    ~DupBSTree() {}

public:
    virtual DupBSTree<E, K>& Insert(const E& e);
};

template<typename E, typename K>
DupBSTree<E, K>& DupBSTree<E, K>::Insert(const E& e)
{
    K k = e; // auto conversion from E to K
    BinaryTreeNode<E>* p = Root();
    BinaryTreeNode<E>* pp = NULL; // parent
    while (p) {
        pp = p;
        if (k <= p->data) { // allow duplicate elements
            p = p->lchild;
        } else if (k > p->data) {
            p = p->rchild;
        }
    }

    BinaryTreeNode<E>* q = new BinaryTreeNode<E>(e);
    if (!pp) {
        Root() = q;
    } else {
        if (k < pp->data) {
            pp->lchild = q;
        } else {
            pp->rchild = q;
        }
    }

    return *this;
}

}}