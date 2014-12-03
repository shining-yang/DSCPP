//
// File: BinaryTree.h
// Binary tree which described in linked list manner.
// Shining Yang <y.s.n@live.com>, 2014-12-03
//
#pragma once
#include <iostream>
using namespace std;
#include "../Utility/Exception.h"
using namespace DSCPP::Utils;

namespace DSCPP { namespace BinaryTree {

// Binary tree node
template<typename T>
class BinaryTreeNode {
public:
    BinaryTreeNode();
    BinaryTreeNode(const T& e);
    BinaryTreeNode(const T& e, BinaryTreeNode<T>* l, BinaryTreeNode<T>* r);
    ~BinaryTreeNode();

    T& Data() {
        return data;
    }
    const T& Data() const {
        return const_cast<BinaryTreeNode<T>*>(this)->Data();
    }

private:
    T data;
    BinaryTreeNode<T>* lchild;
    BinaryTreeNode<T>* rchild;
    template<typename T> friend class BinaryTree;
};

template<typename T>
BinaryTreeNode<T>::BinaryTreeNode() : lchild(NULL), rchild(NULL)
{
}

template<typename T>
BinaryTreeNode<T>::BinaryTreeNode(const T& e) : data(e), lchild(NULL), rchild(NULL)
{
}

template<typename T>
BinaryTreeNode<T>::BinaryTreeNode(const T& e, BinaryTreeNode<T>* l, BinaryTreeNode<T>* r)
    : data(e), lchild(l), rchild(r)
{
}

template<typename T>
BinaryTreeNode<T>::~BinaryTreeNode()
{
}

// Binary tree
template<typename T>
class BinaryTree {
public:
    BinaryTree();
    virtual ~BinaryTree();

    typedef void (*BTVisitor)(const BinaryTreeNode<T>*);

public:
    bool GetRoot(T& x) const;
    bool IsEmpty() const;
    int GetHeight() const;
    int GetCount() const;

    void MakeTree(const T& e, BinaryTree<T>& l, BinaryTree<T>& r);
    void BreakTree(T& e, BinaryTree<T>& l, BinaryTree<T>& r);

    void InOrder(BTVisitor v) const;
    void PreOrder(BTVisitor v) const;
    void PostOrder(BTVisitor v) const;
    void LevelOrder(BTVisitor v) const;

protected:
    void _InOrder(BTVisitor v, BinaryTreeNode<T>* t) const;
    void _PreOrder(BTVisitor v, BinaryTreeNode<T>* t) const;
    void _PostOrder(BTVisitor v, BinaryTreeNode<T>* t) const;
    void _LevelOrder(BTVisitor v, BinaryTreeNode<T>* t) const;
    void _Destroy();

private:
    static void _DestroyVisitor(const BinaryTreeNode<T>* t);
    int _CalcCount(const BinaryTreeNode<T>* t) const;
    int _CalcHeight(const BinaryTreeNode<T>* t) const;

private:
    BinaryTreeNode<T>* root;
};


template<typename T>
BinaryTree<T>::BinaryTree() : root(NULL)
{
}

template<typename T>
BinaryTree<T>::~BinaryTree()
{
    _Destroy();
}

template<typename T>
bool BinaryTree<T>::GetRoot(T& x) const
{
    if (!this->root) {
        return false;
    }

    x = this->root->data;
    return true;
}

template<typename T>
bool BinaryTree<T>::IsEmpty() const
{
    return (this->root == NULL);
}

template<typename T>
int BinaryTree<T>::GetHeight() const
{
    return _CalcHeight(this->root);
}

template<typename T>
int BinaryTree<T>::GetCount() const
{
    return _CalcCount(this->root);
}

template<typename T>
void BinaryTree<T>::MakeTree(const T& e, BinaryTree<T>& l, BinaryTree<T>& r)
{
    this->root = new BinaryTreeNode<T>(e, l.root, r.root);
    l.root = NULL;
    r.root = NULL;
}

template<typename T>
void BinaryTree<T>::BreakTree(T& e, BinaryTree<T>& l, BinaryTree<T>& r)
{
    if (IsEmpty()) {
        thro new ItemNotExisted(); // empty tree
    }

    e = this->root->data;
    l.root = this->root->lchild;
    r.root = this->root->rchild;
    delete this->root;
    this->root = NULL;
}

template<typename T>
void BinaryTree<T>::InOrder(BTVisitor v) const
{
    _InOrder(v, this->root);
}

template<typename T>
void BinaryTree<T>::PreOrder(BTVisitor v) const
{
    _PreOrder(v, this->root);
}

template<typename T>
void BinaryTree<T>::PostOrder(BTVisitor v) const
{
    _PostOrder(v, this->root);
}

template<typename T>
void BinaryTree<T>::LevelOrder(BTVisitor v) const
{

}

template<typename T>
void BinaryTree<T>::_InOrder(BTVisitor v, BinaryTreeNode<T>* t) const
{
    if (t) {
        _InOrder(v, t->lchild);
        v(t);
        _InOrder(v, t->rchild);
    }
}

template<typename T>
void BinaryTree<T>::_PreOrder(BTVisitor v, BinaryTreeNode<T>* t) const
{
    if (t) {
        v(t);
        _PreOrder(v, t->lchild);
        _PreOrder(v, t->rchild);
    }
}

template<typename T>
void BinaryTree<T>::_PostOrder(BTVisitor v, BinaryTreeNode<T>* t) const
{
    if (t) {
        _PostOrder(v, t->lchild);
        _PostOrder(v, t->rchild);
        v(t);
    }
}

template<typename T>
void BinaryTree<T>::_LevelOrder(BTVisitor v, BinaryTreeNode<T>* t) const
{

}

template<typename T>
int BinaryTree<T>::_CalcHeight(const BinaryTreeNode<T>* t) const
{
    if (!t) {
        return 0;
    }

    int lh = _CalcHeight(t->lchild);
    int rh = _CalcHeight(t->rchild);
    return 1 + (lh > rh ? lh : rh);
}

template<typename T>
int BinaryTree<T>::_CalcCount(const BinaryTreeNode<T>* t) const
{
    if (!t) {
        return 0;
    }

    int lc = _CalcCount(t->lchild);
    int rc = _CalcCount(t->rchild);
    return 1 + lc + rc;
}

template<typename T>
void BinaryTree<T>::_Destroy()
{
    _PostOrder(_DestroyVisitor, this->root);
    this->root = NULL;
}

template<typename T>
void BinaryTree<T>::_DestroyVisitor(const BinaryTreeNode<T>* t)
{
    delete t;
}

}}