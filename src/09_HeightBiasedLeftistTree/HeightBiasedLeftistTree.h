//
// File: HeightBiasedLeftistTree.h
// Height biased leftist tree (HBLT).
// Also called: 左高树，左偏树，左倾树，左式树，左式堆(Leftist Heap)，左堆。
// Shining Yang <y.s.n@live.com>, 2014-12-09
//
//
// 满二叉树（Full Binary Tree）：树的每一层，都是满结点的。
//
// 离散数学中的正则二叉树或2-正则树：
// 每个结点要么为树叶（度数为0），要么有两个孩子结点（度数为2）。
// 注：有些教材也定义这个为满二叉树。
//
// 完全二叉树(Complete Binary Tree)：
// 可以这样来理解完全二叉树，即，除了最下面的一层外，其它每层都是满结点的，
// 而最下面那一层，可满也可不满，若不满，则结点连续靠左集中。
//
// 定义[最大树（最小树）]
// 每个节点的值都大于（小于）或等于其子节点（如果有的话）值的树。
//
// 定义[最大堆（最小堆）] 最大（最小）的完全二叉树。
//
// 定义[扩充二叉树(Extended Binary Tree)] 把原二叉树的结点都变为度数为2
// 的分支结点，
// 也就是说，如果原结点的度数的2，则不变；度数为1，则增加一个分支；度数为0（树叶），
// 则增加两个分支。原二叉树结点称为内部结点，新增加的结点称为外部结点。
//
// 令s(x) 为从节点x
// 到它的子树的外部节点的所有路径中最短的一条，根据s(x)的定义可知， 若x
// 是外部节点，则s 的值为0，若x 为内部节点，则它的s 值是：min{s(L), s(R)} + 1
//
// 定义[高度优先左高树] 当且仅当一棵二叉树的任何一个内部节点，其左孩子的s
// 值大于等于 右孩子的s 值时，该二叉树为高度优先左高树（height-biased leftist
// tree, HBLT）。
//
// 定义[最大HBLT] 同时又是最大树的HBLT；[最小HBLT] 同时又是最小树的HBLT。
//
// 定理 令x 为一个HBLT的内部节点，则
//  1) 以x 为根的子树的节点数目至少为2^^s(x) - 1
//  2) 若子树x 有m 个节点，s(x) 最多为log2(m + 1)
//  3) 通过最右路径（路径是从x 开始沿右孩子移动）从x
//  到达外部节点的路径长度为s(x)
//
#pragma once

#include "../03_SinglyLinkedList/SinglyLinkedList.h"
#include "../04_Array/Array.h"
#include "../06_LinearQueue/LinearQueue.h"
#include "../06_LinkedListQueue/LinkedListQueue.h"
#include "../Utility/Exception.h"
#include "../Utility/Misc.h"
#include <iostream>

using namespace std;
using namespace DSCPP::Utils;
using namespace DSCPP::Queue;

namespace DSCPP {
namespace PriorityQueue {

template <typename T> class MaxHBLT;
template <typename T> class MinHBLT;

template <typename T> class HBLTNode {
public:
  HBLTNode(const T &e, int sx = 0, HBLTNode<T> *l = NULL, HBLTNode<T> *r = NULL)
      : data(e) {
    s = sx;
    lchild = l;
    rchild = r;
  }
  ~HBLTNode() {}

private:
  T data;
  int s;
  HBLTNode<T> *lchild;
  HBLTNode<T> *rchild;

  friend class MaxHBLT<T>;
  friend class MinHBLT<T>;
};

template <typename T> class MaxHBLT {
public:
  MaxHBLT();
  ~MaxHBLT();

public:
  bool IsEmpty() const { return root == NULL; }
  T Max() const;
  MaxHBLT<T> &Insert(const T &e);
  MaxHBLT<T> &DeleteMax(T &e);
  MaxHBLT<T> &Merge(MaxHBLT<T> &obj);
  void Initialize(const T arr[], int n);
  void Clear();
  void Clone(MaxHBLT<T> &obj) const;
  void PrintTreeVertically(ostream &os, int width) const;

protected:
  void _Destroy(HBLTNode<T> *p);
  virtual void _Merge(HBLTNode<T> *&dest, HBLTNode<T> *src);
  HBLTNode<T> *_Clone(const HBLTNode<T> *p) const;

  struct VertPrintInfo {
    VertPrintInfo() {}
    VertPrintInfo(HBLTNode<T> *e, int l, int p) : node(e), level(l), pos(p) {}
    HBLTNode<T> *node;
    int level;
    int pos;
  };
  void _PrintVertByLevel(ostream &os, const Chain<VertPrintInfo> &c) const;

private:
  HBLTNode<T> *root;
};

template <typename T> MaxHBLT<T>::MaxHBLT() { root = NULL; }

template <typename T> MaxHBLT<T>::~MaxHBLT() { Clear(); }

template <typename T> void MaxHBLT<T>::Clear() {
  _Destroy(root);
  root = NULL;
}

template <typename T> void MaxHBLT<T>::_Destroy(HBLTNode<T> *p) {
  if (p) {
    _Destroy(p->lchild);
    _Destroy(p->rchild);
    delete p;
  }
}

template <typename T> T MaxHBLT<T>::Max() const {
  if (IsEmpty()) {
    throw new OutOfBounds();
  }

  return root->data;
}

template <typename T> MaxHBLT<T> &MaxHBLT<T>::Insert(const T &e) {
  HBLTNode<T> *p = new HBLTNode<T>(e, 1);
  _Merge(root, p);
  return *this;
}

template <typename T> MaxHBLT<T> &MaxHBLT<T>::DeleteMax(T &e) {
  if (IsEmpty()) {
    throw new OutOfBounds();
  }

  HBLTNode<T> *p = root;
  root = p->lchild;
  _Merge(root, p->rchild);

  e = p->data;
  delete p;
  return *this;
}

template <typename T> MaxHBLT<T> &MaxHBLT<T>::Merge(MaxHBLT<T> &obj) {
  if (this == &obj) {
    return *this;
  }

  _Merge(root, obj.root);
  obj.root = NULL; // detach it
  return *this;
}

template <typename T>
void MaxHBLT<T>::_Merge(HBLTNode<T> *&dest, HBLTNode<T> *src) {
  if (!src) {
    return;
  }

  if (!dest) {
    dest = src;
    return;
  }

  if (dest->data < src->data) {
    Swap(dest, src);
  }

  _Merge(dest->rchild, src);

  if (!dest->lchild) {
    dest->lchild = dest->rchild;
    dest->rchild = NULL;
    dest->s = 1;
  } else {
    if (dest->lchild->s < dest->rchild->s) {
      Swap(dest->lchild, dest->rchild);
    }
    dest->s = dest->rchild->s + 1;
  }
}

template <typename T> void MaxHBLT<T>::Initialize(const T arr[], int n) {
  LinearQueue<HBLTNode<T> *> q(n);
  for (int i = 0; i < n; i++) {
    q.EnQueue(new HBLTNode<T>(arr[i], 1));
  }

  HBLTNode<T> *x = NULL;
  HBLTNode<T> *y = NULL;

  while (q.GetLength() > 1) {
    q.DeQueue(x).DeQueue(y);
    _Merge(x, y);
    q.EnQueue(x);
  }

  q.DeQueue(root);
}

template <typename T> void MaxHBLT<T>::Clone(MaxHBLT<T> &obj) const {
  if (this == &obj) {
    return;
  }

  obj.Clear();
  obj.root = _Clone(root);
}

template <typename T>
HBLTNode<T> *MaxHBLT<T>::_Clone(const HBLTNode<T> *p) const {
  if (!p) {
    return NULL;
  }

  return new HBLTNode<T>(p->data, p->s, _Clone(p->lchild), _Clone(p->rchild));
}

template <typename T>
void MaxHBLT<T>::PrintTreeVertically(ostream &os, int width) const {
  if (!root) {
    return;
  }

#define ASSUME_MAX_TREE_HEIGHT 32 // large enough for brevity
  Array<Chain<VertPrintInfo>> a(ASSUME_MAX_TREE_HEIGHT);
  LinkedListQueue<VertPrintInfo> q;
  q.EnQueue(VertPrintInfo(root, 0, width / 2));

  while (!q.IsEmpty()) {
    VertPrintInfo t;
    q.DeQueue(t);

    a[t.level].Insert(0, t);

    if (t.node->lchild) {
      q.EnQueue(VertPrintInfo(t.node->lchild, t.level + 1,
                              t.pos - width / (1 << (t.level + 2))));
    }

    if (t.node->rchild) {
      q.EnQueue(VertPrintInfo(t.node->rchild, t.level + 1,
                              t.pos + width / (1 << (t.level + 2))));
    }
  }

  for (int i = 0; i < ASSUME_MAX_TREE_HEIGHT; i++) {
    if (a[i].IsEmpty()) {
      break;
    }

    _PrintVertByLevel(os, a[i]);
    os << endl;
  }
}

template <typename T>
void MaxHBLT<T>::_PrintVertByLevel(ostream &os,
                                   const Chain<VertPrintInfo> &c) const {
  int maxpos = 0;
  VertPrintInfo x;

  // - get the max
  for (int i = 0; i < c.Length(); i++) {
    c.Find(i, x);
    if (maxpos < x.pos) {
      maxpos = x.pos;
    }
  }

  // - fill in valid items
  Array<HBLTNode<T> *> A(maxpos + 1);
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
      os << A[i]->data;
    } else {
      os << " ";
    }
  }
}

//----------------------- MinHBLT -----------------------------------
// Simply derived rom MaxHBLT
//-------------------------------------------------------------------

template <typename T> class MinHBLT : private MaxHBLT<T> {
public:
  MinHBLT();
  ~MinHBLT();

public:
  bool IsEmpty() const;
  T Min() const;
  MinHBLT<T> &Insert(const T &e);
  MinHBLT<T> &DeleteMin(T &e);
  MinHBLT<T> &Merge(MinHBLT<T> &obj);
  void Initialize(const T arr[], int n);
  void Clear();
  void Clone(MinHBLT<T> &obj) const;
  void PrintTreeVertically(ostream &os, int width) const;

protected:
  virtual void _Merge(HBLTNode<T> *&dest, HBLTNode<T> *src);
};

template <typename T> MinHBLT<T>::MinHBLT() {}

template <typename T> MinHBLT<T>::~MinHBLT() {}

template <typename T> bool MinHBLT<T>::IsEmpty() const {
  return MaxHBLT<T>::IsEmpty();
}

template <typename T> T MinHBLT<T>::Min() const { return MaxHBLT<T>::Max(); }

template <typename T> MinHBLT<T> &MinHBLT<T>::Insert(const T &e) {
  return reinterpret_cast<MinHBLT<T> &>(MaxHBLT<T>::Insert(e));
}

template <typename T> MinHBLT<T> &MinHBLT<T>::DeleteMin(T &e) {
  return reinterpret_cast<MinHBLT<T> &>(MaxHBLT<T>::DeleteMax(e));
}

template <typename T> MinHBLT<T> &MinHBLT<T>::Merge(MinHBLT<T> &obj) {
  return reinterpret_cast<MinHBLT<T> &>(MaxHBLT<T>::Merge(obj));
}

template <typename T> void MinHBLT<T>::Initialize(const T arr[], int n) {
  MaxHBLT<T>::Initialize(arr, n);
}

template <typename T> void MinHBLT<T>::Clear() { MaxHBLT<T>::Clear(); }

template <typename T> void MinHBLT<T>::Clone(MinHBLT<T> &obj) const {
  MaxHBLT<T>::Clone(obj);
}

template <typename T>
void MinHBLT<T>::PrintTreeVertically(ostream &os, int width) const {
  MaxHBLT<T>::PrintTreeVertically(os, width);
}

template <typename T>
void MinHBLT<T>::_Merge(HBLTNode<T> *&dest, HBLTNode<T> *src) {
  if (!src) {
    return;
  }

  if (!dest) {
    dest = src;
    return;
  }

  if (dest->data > src->data) {
    Swap(dest, src);
  }

  _Merge(dest->rchild, src);

  if (!dest->lchild) {
    dest->lchild = dest->rchild;
    dest->rchild = NULL;
    dest->s = 1;
  } else {
    if (dest->lchild->s < dest->rchild->s) {
      Swap(dest->lchild, dest->rchild);
    }
    dest->s = dest->rchild->s + 1;
  }
}

} // namespace PriorityQueue
} // namespace DSCPP