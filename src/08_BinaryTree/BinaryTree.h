//
// File: BinaryTree.h
// Binary tree which described in linked list manner.
// Shining Yang <y.s.n@live.com>, 2014-12-03
//
#pragma once
#include <iostream>
#include "../Utility/Exception.h"
#include "../06_LinkedListQueue/LinkedListQueue.h"
#include "../04_Array/Array.h"
#include "../03_SinglyLinkedList/SinglyLinkedList.h"

using namespace std;
using namespace DSCPP::Utils;
using namespace DSCPP::Queue;

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
    template<typename X> friend class BinaryTree;
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
    enum { H_INDENT = 4 }; // indentation for printing tree horizontally

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

    // Print binary tree on console
    void PrintHorizontally(int indent) const;
    void PrintVertically(int width) const;

    void Clone(BinaryTree<T>& cp) const;
    bool Compare(const BinaryTree<T>& bt) const;

protected:
    void _InOrder(BTVisitor v, BinaryTreeNode<T>* t) const;
    void _PreOrder(BTVisitor v, BinaryTreeNode<T>* t) const;
    void _PostOrder(BTVisitor v, BinaryTreeNode<T>* t) const;
    void _LevelOrder(BTVisitor v, BinaryTreeNode<T>* t) const;
    void _Destroy();
    void _PrintHorz(BinaryTreeNode<T>* t, int pos, int indent) const;
    void _PrintVert(BinaryTreeNode<T>* t, int level, int pos) const;

    // structure used to print binary tree vertically
    struct BinaryTreeVerticalPrintInfo {
        BinaryTreeVerticalPrintInfo() {}
        BinaryTreeVerticalPrintInfo(BinaryTreeNode<T>* n, int l, int p)
            : node(n), level(l), pos(p) {}
        BinaryTreeNode<T>* node;
        int level;
        int pos;
    };

    void _PrintVertByLevel(const Chain<BinaryTreeVerticalPrintInfo> & c) const;
    BinaryTreeNode<T>* _Clone(const BinaryTreeNode<T>* t) const;
    bool _Compare(const BinaryTreeNode<T>* s, const BinaryTreeNode<T>* t) const;

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
    _Destroy(); // first to release ourselves
    this->root = new BinaryTreeNode<T>(e, l.root, r.root);
    l.root = NULL;
    r.root = NULL;
}

template<typename T>
void BinaryTree<T>::BreakTree(T& e, BinaryTree<T>& l, BinaryTree<T>& r)
{
    if (IsEmpty()) {
        throw new ItemNotExisted(); // empty tree
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
    _LevelOrder(v, this->root);
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
    if (t) {
        LinkedListQueue<BinaryTreeNode<T>*> q;
        q.EnQueue(t);

        while (!q.IsEmpty()) {
            BinaryTreeNode<T>* p;
            q.DeQueue(p);
            v(p);

            if (p->lchild) {
                q.EnQueue(p->lchild);
            }

            if (p->rchild) {
                q.EnQueue(p->rchild);
            }
        }
    }
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

template<typename T>
void BinaryTree<T>::_PrintHorz(BinaryTreeNode<T>* t, int pos, int indent) const
{
    // visit order: right, root, left
    if (t) {
        _PrintHorz(t->rchild, pos + indent, indent);

        for (int i = 0; i < pos; i++) {
            std::cout << " ";
        }
        std::cout << t->Data() << endl;
        
        _PrintHorz(t->lchild, pos + indent, indent);
    }
}

template<typename T>
void BinaryTree<T>::_PrintVert(BinaryTreeNode<T>* t, int level, int width) const
{
    if (!t) {
        return;
    }

    if (level != 0) {
        throw new InvalideArgument();
    }

    int height = _CalcHeight(t);

    // an array of chains
    Array<Chain<BinaryTreeVerticalPrintInfo> > A(height);

    LinkedListQueue<BinaryTreeVerticalPrintInfo> Q;
    Q.EnQueue(BinaryTreeVerticalPrintInfo(t, level, width / 2));

    while (!Q.IsEmpty()) {
        BinaryTreeVerticalPrintInfo p;
        Q.DeQueue(p);

        A[p.level].Insert(0, p); // save the print-info into linked-list

        if (p.node->lchild) {
            Q.EnQueue(BinaryTreeVerticalPrintInfo(
                p.node->lchild, p.level + 1, p.pos - width / (1 << (p.level + 2))));
        }

        if (p.node->rchild) {
            Q.EnQueue(BinaryTreeVerticalPrintInfo(
                p.node->rchild, p.level + 1, p.pos + width / (1 << (p.level + 2))));
        }
    }

    // ready to print
    for (int i = 0; i < height; i++) {
        _PrintVertByLevel(A[i]);
        cout << endl;
    }
}

template<typename T>
void BinaryTree<T>::_PrintVertByLevel(const Chain<BinaryTreeVerticalPrintInfo>& c) const
{
    int maxpos = 0;
    BinaryTreeVerticalPrintInfo x;

    // - get the max
    for (int i = 0; i < c.Length(); i++) {
        c.Find(i, x);
        if (maxpos < x.pos) {
            maxpos = x.pos;
        }
    }

    // - fill in valid items
    Array<BinaryTreeNode<T>*> A(maxpos + 1);
    for (int i = 0; i <= maxpos; i++) {
        A[i] = NULL;
    }

    for (int i = 0; i < c.Length(); i++) {
        c.Find(i, x);
        A[x.pos] = x.node;
    }

    // - output
    for (int i = 0; i <= maxpos; i++) {
        if (A[i]) {
            cout << A[i]->data;
        } else {
            cout << " ";
        }
    }
}

template<typename T>
void BinaryTree<T>::PrintHorizontally(int indent) const
{
    _PrintHorz(this->root, 0, indent);
}

template<typename T>
void BinaryTree<T>::PrintVertically(int width) const
{
    _PrintVert(this->root, 0, width);
}

template<typename T>
bool BinaryTree<T>::Compare(const BinaryTree<T>& bt) const
{
    return _Compare(this->root, bt.root);
}

template<typename T>
bool BinaryTree<T>::_Compare(const BinaryTreeNode<T>* s, const BinaryTreeNode<T>* t) const
{
    if (!s && !t) {
        return true;
    }

    if (s && t) {
        return
            s->data == t->data &&
            _Compare(s->lchild, t->lchild) &&
            _Compare(s->rchild, t->rchild);
    }

    return false;
}

template<typename T>
void BinaryTree<T>::Clone(BinaryTree<T>& cp) const
{
    if (this == &cp) {
        throw new InvalideArgument();
    }

    cp._Destroy();
    cp.root = _Clone(this->root);
}

template<typename T>
BinaryTreeNode<T>* BinaryTree<T>::_Clone(const BinaryTreeNode<T>* t) const
{
    if (!t) {
        return NULL;
    }

    BinaryTreeNode<T>* r = new BinaryTreeNode<T>(t->data);
    r->lchild = _Clone(t->lchild);
    r->rchild = _Clone(t->rchild);
    return r;
}

}}
