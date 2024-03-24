//
// File: IndexedBinarySearchTree.h
// Indexed binary search tree. No duplicate elements are allowed.
// Shining Yang <y.s.n@live.com>, 2014-12-16
//
#pragma once

#include "../08_BinaryTree/BinaryTree.h"
#include "../Utility/Exception.h"
#include <iostream>

using namespace std;
using namespace DSCPP::Utils;
using namespace DSCPP::BinaryTree;

namespace DSCPP {
namespace SearchTree {

template <typename E, typename K> class IndexedBSTreeNodeInfo {
public:
  IndexedBSTreeNodeInfo() {}
  IndexedBSTreeNodeInfo(const E &data, int sz) : d(data), s(sz) {}

  bool operator==(const IndexedBSTreeNodeInfo<E, K> &obj) const {
    return d == obj.d;
  }

  bool operator!=(const IndexedBSTreeNodeInfo<E, K> &obj) const {
    return !operator==(obj);
  }

  bool operator<(const IndexedBSTreeNodeInfo<E, K> &obj) const {
    return d < obj.d;
  }

  bool operator>(const IndexedBSTreeNodeInfo<E, K> &obj) const {
    return d > obj.d;
  }

  bool operator<=(const IndexedBSTreeNodeInfo<E, K> &obj) const {
    return !operator>(obj);
  }

  bool operator>=(const IndexedBSTreeNodeInfo<E, K> &obj) const {
    return !operator<(obj);
  }

  // use Et & Kt instead, to avoid complaints from g++
  template <typename Et, typename Kt> friend class IndexedBSTree;
  template <typename Et, typename Kt>
  friend ostream &operator<<(ostream &os,
                             const IndexedBSTreeNodeInfo<Et, Kt> &obj);

private:
  E d;   // actual data member
  int s; // left size (number of left tree nodes + 1)
};

template <typename E, typename K>
ostream &operator<<(ostream &os, const IndexedBSTreeNodeInfo<E, K> &obj) {
  os << obj.s << ":" << obj.d;
  return os;
}

template <typename E, typename K>
class IndexedBSTree
    : public DSCPP::BinaryTree::BinaryTree<IndexedBSTreeNodeInfo<E, K>> {

public:
  IndexedBSTree() {}
  ~IndexedBSTree() {}

public:
  // Search for element by key. Return true on success, false otherwise
  bool Search(const K &k, E &e) const;

  // Insert a new element. Throw exception when already existed
  IndexedBSTree<E, K> &Insert(const E &e);

  // Delete an element by specified key. Throw exception when not found
  IndexedBSTree<E, K> &Delete(const K &k, E &e);

  // Search for the i-th [1..count] element.
  bool IndexSearch(int i, E &e) const;

  // Delete the i-th [1..count] element. Throw exception when not found
  IndexedBSTree<E, K> &IndexDelete(int i, E &e);

  void OutputAscending() const {
    DSCPP::BinaryTree::BinaryTree<IndexedBSTreeNodeInfo<E, K>>::InOrder(
        _PrintNode);
  }

protected:
  static void _PrintNode(const BinaryTreeNode<IndexedBSTreeNodeInfo<E, K>> *p) {
    cout << p->data << ", ";
  }

  void _UpdateOnInsert(const K &k);
  void _UpdateOnDelete(const K &k);
  const BinaryTreeNode<IndexedBSTreeNodeInfo<E, K>> *
  _Find(const BinaryTreeNode<IndexedBSTreeNodeInfo<E, K>> *p, int i) const;
};

template <typename E, typename K>
bool IndexedBSTree<E, K>::Search(const K &k, E &e) const {
  const BinaryTreeNode<IndexedBSTreeNodeInfo<E, K>> *p =
      DSCPP::BinaryTree::BinaryTree<IndexedBSTreeNodeInfo<E, K>>::RootNodePtr();

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

template <typename E, typename K>
IndexedBSTree<E, K> &IndexedBSTree<E, K>::Insert(const E &e) {
  K k = e; // make a conversion
  BinaryTreeNode<IndexedBSTreeNodeInfo<E, K>> *p =
      DSCPP::BinaryTree::BinaryTree<IndexedBSTreeNodeInfo<E, K>>::RootNodePtr();
  BinaryTreeNode<IndexedBSTreeNodeInfo<E, K>> *pp = NULL;

  while (p) {
    pp = p;
    if (k < p->data.d) {
      p = p->lchild;
    } else if (k > p->data.d) {
      p = p->rchild;
    } else {
      throw new ItemAlreadyExisted();
    }
  }

  BinaryTreeNode<IndexedBSTreeNodeInfo<E, K>> *r =
      new BinaryTreeNode<IndexedBSTreeNodeInfo<E, K>>(
          IndexedBSTreeNodeInfo<E, K>(e, 1));
  if (!pp) { // empty tree
    DSCPP::BinaryTree::BinaryTree<IndexedBSTreeNodeInfo<E, K>>::RootNodePtr() =
        r;
  } else if (k < pp->data.d) {
    pp->lchild = r;
  } else {
    pp->rchild = r;
  }

  _UpdateOnInsert(k);
  return *this;
}

template <typename E, typename K>
IndexedBSTree<E, K> &IndexedBSTree<E, K>::Delete(const K &k, E &e) {
  bool updated = false; // flag to indicate whether updated `s' or not
  BinaryTreeNode<IndexedBSTreeNodeInfo<E, K>> *p =
      DSCPP::BinaryTree::BinaryTree<IndexedBSTreeNodeInfo<E, K>>::RootNodePtr();
  BinaryTreeNode<IndexedBSTreeNodeInfo<E, K>> *pp = NULL;

  while (p && (k != p->data.d)) {
    pp = p;
    if (k < p->data.d) {
      p = p->lchild;
    } else {
      p = p->rchild;
    }
  }

  if (!p) {
    throw new ItemNotExisted();
  }

  e = p->data.d;

  if (p->lchild && p->rchild) { // p has both left and right child
    //
    // We'd try to find the smallest element in the right child sub-tree.
    // Then assign it to the one which will be deleted. And then delete it.
    //
    BinaryTreeNode<IndexedBSTreeNodeInfo<E, K>> *rpp = p;
    BinaryTreeNode<IndexedBSTreeNodeInfo<E, K>> *rp = p->rchild;
    while (rp->lchild) {
      rpp = rp;
      rp = rp->lchild;
    }

    // Update the `left-size' field from ROOT to the node that will be deleted.
    // Do this operation before the following REPLACEMENT.
    _UpdateOnDelete(rp->data.d);
    updated = true;

    p->data.d = rp->data.d; // replace only data, leave `left-size' alone
    pp = rpp;
    p = rp;
  }

  if (!updated) {
    _UpdateOnDelete(p->data.d);
    updated = true;
  }

  // Now, `p' has 1 child at most, `pp' is the parent of `p' if not NULL
  BinaryTreeNode<IndexedBSTreeNodeInfo<E, K>> *c = p->lchild;
  if (!c) {
    c = p->rchild;
  }

  if (!pp) {
    DSCPP::BinaryTree::BinaryTree<IndexedBSTreeNodeInfo<E, K>>::RootNodePtr() =
        c;
  } else if (pp->lchild == p) {
    pp->lchild = c;
  } else {
    pp->rchild = c;
  }

  delete p;
  return *this;
}

template <typename E, typename K>
bool IndexedBSTree<E, K>::IndexSearch(int i, E &e) const {
  const BinaryTreeNode<IndexedBSTreeNodeInfo<E, K>> *p = _Find(
      DSCPP::BinaryTree::BinaryTree<IndexedBSTreeNodeInfo<E, K>>::RootNodePtr(),
      i);
  if (!p) {
    return false;
  }

  e = p->data.d;
  return true;
}

template <typename E, typename K>
IndexedBSTree<E, K> &IndexedBSTree<E, K>::IndexDelete(int i, E &e) {
  bool updated = false;
  BinaryTreeNode<IndexedBSTreeNodeInfo<E, K>> *p =
      DSCPP::BinaryTree::BinaryTree<IndexedBSTreeNodeInfo<E, K>>::RootNodePtr();
  BinaryTreeNode<IndexedBSTreeNodeInfo<E, K>> *pp = NULL;

  while (p) {
    if (i == p->data.s) {
      break;
    }

    pp = p;
    if (i < p->data.s) {
      p = p->lchild;
    } else {
      i = i - p->data.s;
      p = p->rchild;
    }
  }

  if (!p) {
    throw new ItemNotExisted();
  }

  e = p->data.d;

  if (p->lchild && p->rchild) { // p has both left child and right child
    // use the MINIMUM element in right children to replace `p'
    BinaryTreeNode<IndexedBSTreeNodeInfo<E, K>> *rpp = p;
    BinaryTreeNode<IndexedBSTreeNodeInfo<E, K>> *rp = p->rchild;
    while (rp->lchild) {
      rpp = rp;
      rp = rp->lchild;
    }

    // Update the `left-size' field from ROOT to the node that will be deleted.
    // Do this operation before the following REPLACEMENT.
    _UpdateOnDelete(rp->data.d);
    updated = true;

    p->data.d = rp->data.d; // Only replace the `d', keep `s' unchanged
    pp = rpp;
    p = rp;
  }

  if (!updated) {
    _UpdateOnDelete(p->data.d);
    updated = true;
  }

  // Now, p has 1 child at most, pp is the parent of p if not NULL
  BinaryTreeNode<IndexedBSTreeNodeInfo<E, K>> *c = p->lchild;
  if (!c) {
    c = p->rchild;
  }

  if (!pp) {
    DSCPP::BinaryTree::BinaryTree<IndexedBSTreeNodeInfo<E, K>>::RootNodePtr() =
        c;
  } else if (pp->lchild == p) {
    pp->lchild = c;
  } else {
    pp->rchild = c;
  }

  delete p;
  return *this;
}

template <typename E, typename K>
void IndexedBSTree<E, K>::_UpdateOnInsert(const K &k) {
  BinaryTreeNode<IndexedBSTreeNodeInfo<E, K>> *p =
      DSCPP::BinaryTree::BinaryTree<IndexedBSTreeNodeInfo<E, K>>::RootNodePtr();
  while (p && (k != p->data.d)) {
    if (k < p->data.d) {
      p->data.s++;
      p = p->lchild;
    } else {
      p = p->rchild;
    }
  }
}

template <typename E, typename K>
void IndexedBSTree<E, K>::_UpdateOnDelete(const K &k) {
  BinaryTreeNode<IndexedBSTreeNodeInfo<E, K>> *p =
      DSCPP::BinaryTree::BinaryTree<IndexedBSTreeNodeInfo<E, K>>::RootNodePtr();
  while (p && (k != p->data.d)) {
    if (k < p->data.d) {
      p->data.s--;
      p = p->lchild;
    } else {
      p = p->rchild;
    }
  }
}

template <typename E, typename K>
const BinaryTreeNode<IndexedBSTreeNodeInfo<E, K>> *
IndexedBSTree<E, K>::_Find(const BinaryTreeNode<IndexedBSTreeNodeInfo<E, K>> *p,
                           int i) const {
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

} // namespace SearchTree
} // namespace DSCPP