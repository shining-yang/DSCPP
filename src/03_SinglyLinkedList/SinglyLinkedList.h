//
// File: SinglyLinkedList.h
// Singly linked list
// Shining Yang <y.s.n@live.com>, 2014/09/02
//
// 2014/09/03, added sorting methods: bubble, selection, rank, insertion
//
#pragma once

#include <iostream>
using namespace std;

#include "../Utility/Exception.h"
#include "../Utility/Misc.h"
using namespace DSCPP::Utils;

template <class T> class Chain;
template <class T> class ChainNode;

// used in RankSort
template <class T> struct ChainNodeRank {
  int rank;
  ChainNode<T> *ptr;
};

template <class T> class ChainNode {
  friend class Chain<T>;

private:
  T data;
  ChainNode<T> *link;
};

template <class T> class Chain {
public:
  class Iterator {
    friend class Chain<T>;
    ChainNode<T> *ptr;

  public:
    Iterator() {}
    Iterator(const Iterator &o) { this->ptr = o.ptr; }
    Iterator &operator=(const Iterator &o) { this->ptr = o.ptr; }
    bool operator==(const Iterator &o) { return (this->ptr == o.ptr); }
    bool operator!=(const Iterator &o) { return !operator==(o); }
    T &operator*() { return ptr->data; }
    T *operator++() {
      if (ptr) {
        ptr = ptr->link;
        if (ptr) {
          return &ptr->data;
        }
      }
      return NULL;
    }
    T *operator++(int) {
      if (ptr) {
        T *temp = &ptr->data;
        ptr = ptr->link;
        return temp;
      } else {
        return NULL;
      }
    }
    T *Next() {
      if (ptr) {
        ptr = ptr->link;
        if (ptr) {
          return &ptr->data;
        }
      }
      return NULL;
    }
  };

  Iterator Begin() {
    Iterator it;
    it.ptr = first;
    return it;
  }

  Iterator End() {
    Iterator it;
    it.ptr = NULL;
    return it;
  }

public:
  Chain();
  Chain(const Chain &o); // copy constructor
  ~Chain();

public:
  void Clear();
  bool IsEmpty() const;
  int Length() const;
  bool Find(int k, T &x) const; // Get the number k element
  int Search(const T &x) const; // Get position of x
  Chain<T> &Delete(int k, T &x);
  Chain<T> &Insert(int k, const T &x);
  void Output(std::ostream &os) const;

  // additional
public:
  void Reverse();
  void BubbleSort(bool ascending = true);
  void InsertionSort(bool ascending = true);
  void RankSort(bool ascending = true);
  void SelectionSort(bool ascending = true);

protected:
  bool DoBubble(int n, bool ascending = true);
  void DoInsertion(ChainNode<T> *t, bool ascending = true);

private:
  ChainNode<T> *first;
};

template <class T> bool Chain<T>::DoBubble(int n, bool ascending /*= true*/) {
  bool swap_occurred = false;
  ChainNode<T> *p = first; // current node
  ChainNode<T> *q = NULL;  // next node
  ChainNode<T> *r = NULL;  // previous node

  while (n-- > 1) { // require 2 nodes at least
    q = p->link;
    bool swap_required = false;
    if ((p->data > q->data && ascending) || (p->data < q->data && !ascending)) {
      swap_required = true;
    }

    if (swap_required) {
      if (this->first == p) { // the first node needs to swap
        this->first = q;
      } else {
        r->link = q;
      }
      p->link = q->link;
      q->link = p;
      r = q;
      swap_occurred = true;
    } else {
      r = p;
      p = q;
    }
  }

  return swap_occurred;
}

template <class T> void Chain<T>::BubbleSort(bool ascending /*= true*/) {
  int n = Length();
  for (int i = n; i > 0 && DoBubble(i, ascending); i--) {
    ;
  }
}

template <class T>
void Chain<T>::DoInsertion(ChainNode<T> *t, bool ascending /*= true*/) {
  ChainNode<T> *prev = this->first;
  ChainNode<T> *p = this->first;

  while (p) {
    if ((t->data < p->data && ascending) || (t->data > p->data && !ascending)) {
      t->link = p;
      if (p == this->first) {
        this->first = t;
      } else {
        prev->link = t;
      }
      return; // finish inserting
    }

    prev = p;
    p = p->link;
  }

  t->link = NULL;
  if (!prev) { // `first` is NULL
    this->first = t;
  } else { // append at the tail
    prev->link = t;
  }
}

template <class T> void Chain<T>::InsertionSort(bool ascending /*= true*/) {
  ChainNode<T> *p = first;
  first = NULL;
  while (p) {
    ChainNode<T> *q = p->link;
    DoInsertion(p, ascending);
    p = q;
  }
}

template <class T> void Chain<T>::RankSort(bool ascending /*= true*/) {
  int n = Length();
  if (n < 2) {
    return;
  }

  // 1. init rank array
  ChainNodeRank<T> *ranks = new ChainNodeRank<T>[n];
  int i = 0;
  for (ChainNode<T> *p = first; p; p = p->link) {
    ranks[i].ptr = p;
    ranks[i].rank = 0;
    i++;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (ascending) {
        if (ranks[j].ptr->data < ranks[i].ptr->data) {
          ranks[i].rank++;
        } else {
          ranks[j].rank++;
        }
      } else {
        if (ranks[j].ptr->data > ranks[i].ptr->data) {
          ranks[i].rank++;
        } else {
          ranks[j].rank++;
        }
      }
    }
  }

  // 2. sorting
  for (int i = 0; i < n; i++) {
    while (ranks[i].rank != i) {
      Swap(ranks[ranks[i].rank], ranks[i]);
    }
  }

  // 3. re-build list
  for (int i = 0; i < n - 1; i++) {
    ranks[i].ptr->link = ranks[i + 1].ptr;
  }
  ranks[n - 1].ptr->link = NULL;

  this->first = ranks[0].ptr;
  delete[] ranks;
}

template <class T> void Chain<T>::SelectionSort(bool ascending /*= true*/) {
  ChainNode<T> *nl = NULL;

  while (this->first) {
    ChainNode<T> *q = this->first; // the MAX/MIN node
    ChainNode<T> *qr = NULL;       // previous node of MAX/MIN
    ChainNode<T> *prev = NULL;     // previous node of iterator
    for (ChainNode<T> *p = q; p; p = p->link) {
      if ((ascending && p->data > q->data) ||
          (!ascending && p->data < q->data)) {
        qr = prev;
        q = p;
      }
      prev = p;
    }

    if (q == this->first) {
      this->first = q->link;
    } else {
      qr->link = q->link;
    }

    q->link = nl;
    nl = q;
  }

  this->first = nl;
}

// copy constructor
template <class T> Chain<T>::Chain(const Chain &o) {
  this->first = NULL;
  ChainNode<T> *last = NULL;
  ChainNode<T> *temp = NULL;
  for (ChainNode<T> *p = o.first; p; p = p->link) {
    temp = new ChainNode<T>();
    temp->data = p->data;
    temp->link = NULL;
    if (!this->first) {
      this->first = temp;
    } else {
      last->link = temp;
    }
    last = temp;
  }
}

template <class T> Chain<T>::Chain() { first = NULL; }

template <class T> Chain<T>::~Chain() { Clear(); }

template <class T> void Chain<T>::Clear() {
  ChainNode<T> *p;
  while (first) {
    p = first;
    first = first->link;
    delete p;
  }
}

template <class T> bool Chain<T>::IsEmpty() const { return first == NULL; }

template <class T> int Chain<T>::Length() const {
  int n = 0;
  ChainNode<T> *p = first;
  while (p) {
    p = p->link;
    n++;
  }
  return n;
}

// 0-based index
template <class T> bool Chain<T>::Find(int k, T &x) const {
  if (k < 0) {
    return false;
  }

  int pos = 0;
  ChainNode<T> *p = first;
  while (p && pos < k) {
    p = p->link;
    pos++;
  }
  if (p) {
    x = p->data;
    return true;
  }
  return false;
}

// 0-based index
template <class T> int Chain<T>::Search(const T &x) const {
  int n = 0;
  ChainNode<T> *p = first;
  while (p && p->data != x) {
    p = p->link;
    n++;
  }
  if (p) {
    return n;
  }
  return -1;
}

// 0-based index
template <class T> Chain<T> &Chain<T>::Delete(int k, T &x) {
  if (k < 0 || !first) {
    throw new OutOfBounds();
  }

  ChainNode<T> *p = first;
  if (k == 0) {
    first = first->link;
  } else {
    // move pointer to node k-1
    ChainNode<T> *q = first;
    for (int n = 0; n < k - 1 && q; n++) {
      q = q->link;
    }
    if (!q || !q->link) {
      throw new OutOfBounds();
    }
    p = q->link;
    q->link = p->link;
  }

  x = p->data;
  delete p;
  return *this;
}

// 0-based index
//
// @param k allows [0, length]
//
template <class T> Chain<T> &Chain<T>::Insert(int k, const T &x) {
  if (k < 0) {
    throw new OutOfBounds;
  }

  ChainNode<T> *t = new ChainNode<T>();
  t->data = x;

  if (k == 0) {
    t->link = first;
    first = t;
    return *this;
  }

  // move pointer to k-1, then link the new node
  int n = 0;
  ChainNode<T> *p = first;
  while (p && n < k - 1) {
    p = p->link;
    n++;
  }

  if (!p) {
    throw new OutOfBounds();
  }

  t->link = p->link;
  p->link = t;
  return *this;
}

template <class T> void Chain<T>::Output(std::ostream &os) const {
  ChainNode<T> *p = first;
  while (p) {
    if (p != first) { // append separator if there are more than 1 node and not
                      // at the first one
      os << " ";
    }
    os << p->data;
    p = p->link;
  }
}

template <class T>
std::ostream &operator<<(std::ostream &os, const Chain<T> &c) {
  c.Output(os);
  return os;
}

template <class T> void Chain<T>::Reverse() {
  ChainNode<T> *p = first;
  first = NULL;
  while (p) {
    ChainNode<T> *q = p;
    p = p->link;
    q->link = first;
    first = q;
  }
}

//
// Use member functions of Chain
// When finished, B will be reversed A, and A will be empty
//
template <class T> void ReverseChain(Chain<T> &a, Chain<T> &b) {
  T x;
  while (!a.IsEmpty()) {
    a.Delete(0, x);
    b.Insert(0, x);
  }
}