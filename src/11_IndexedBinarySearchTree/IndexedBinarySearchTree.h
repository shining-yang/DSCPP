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

    // Make a conversion so that we can compare K and
    // IndexedBSTreeNodeInfo<E,K> directly
    operator K() const {
        return K(d);
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

    // use Et & Kt instead, to avoid complaints from g++
    template<typename Et, typename Kt> friend class IndexedBSTree;
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

    // Insert a new element. Throw exception when already existed
    IndexedBSTree<E, K>& Insert(const E& e);

    // Delete an element by specified key. Throw exception when not found
    IndexedBSTree<E, K>& Delete(const K& k, E& e);

    // Search for the i-th element.
    bool IndexSearch(int i, E& e) const;

    // Delete the i-th element. Throw exception when not found
    IndexedBSTree<E, K>& IndexDelete(int i, E& e);

    void OutputAscending() const {
        InOrder(_PrintNode);
    }

protected:
    static void _PrintNode(const BinaryTreeNode<IndexedBSTreeNodeInfo<E, K> >* p) {
        cout << p->data << ", ";
    }

    void _UpdateOnInsert(const K& k);
    void _UpdateOnDelete(const K& k);
    const BinaryTreeNode<IndexedBSTreeNodeInfo<E, K> >* _Find(
        const BinaryTreeNode<IndexedBSTreeNodeInfo<E, K> >* p, int i) const;
};

template<typename E, typename K>
const BinaryTreeNode<IndexedBSTreeNodeInfo<E, K> >* IndexedBSTree<E, K>::_Find(
    const BinaryTreeNode<IndexedBSTreeNodeInfo<E, K> >* p, int i) const
{
    if (!p) {
        return NULL;
    }
    
    if (i == p->data.s) {
        return p;
    } else if (i < p->data.s) {
        return _Find(p->lchild, i);
    } else {
        return _Find(p->rchild, i - p->data.s);
    }
}

template<typename E, typename K>
bool IndexedBSTree<E, K>::Search(const K& k, E& e) const
{
    const BinaryTreeNode<IndexedBSTreeNodeInfo<E, K> >* p = Root();
    while (p) {
        if (k < p->data) {
            p = p->lchild;
        } else if (k > p->data) {
            p = p->rchild;
        } else {
            e = p->data;
            return true;
        }
    }

    return false;
}

template<typename E, typename K>
IndexedBSTree<E, K>& IndexedBSTree<E, K>::Insert(const E& e)
{
    K k = e; // make a conversion
    BinaryTreeNode<IndexedBSTreeNodeInfo<E, K> >* p = Root();
    BinaryTreeNode<IndexedBSTreeNodeInfo<E, K> >* pp = NULL;

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

    BinaryTreeNode<IndexedBSTreeNodeInfo<E, K> >* r =
        new BinaryTreeNode<IndexedBSTreeNodeInfo<E, K> >(IndexedBSTreeNodeInfo<E, K>(e, 1));
    if (!pp) { // empty tree
        Root() = r;
    } else if (k < pp->data) {
        pp->lchild = r;
    } else {
        pp->rchild = r;
    }

    _UpdateOnInsert(k);
    return *this;
}

template<typename E, typename K>
IndexedBSTree<E, K>& IndexedBSTree<E, K>::Delete(const K& k, E& e)
{

}

template<typename E, typename K>
bool IndexedBSTree<E, K>::IndexSearch(int i, E& e) const
{
    const BinaryTreeNode<IndexedBSTreeNodeInfo<E, K> >* p = _Find(Root(), i);
    if (!p) {
        //throw new ItemNotExisted();
        return false;
    }

    e = p->data.d;
    return true;
}

template<typename E, typename K>
IndexedBSTree<E, K>& IndexedBSTree<E, K>::IndexDelete(int i, E& e)
{

}

template<typename E, typename K>
void IndexedBSTree<E, K>::_UpdateOnInsert(const K& k)
{
    BinaryTreeNode<IndexedBSTreeNodeInfo<E, K> >* p = Root();
    while (p && (k != p->data)) {
        if (k < p->data) {
            p->data.s++;
            p = p->lchild;
        } else {
            p = p->rchild;
        }
    }
}

template<typename E, typename K>
void IndexedBSTree<E, K>::_UpdateOnDelete(const K& k)
{

}

}}