//
// File: StackLinkedListCustomized.h
//
// Stack implemented with customized linked list.
// Allocated nodes will not free automatically unless you explicitly call Shrink().
//
// Shining Yang <y.s.n@live.com>, 2014-10-18
//
#pragma once

#include <iostream>
using namespace std;

#include "../Utility/Exception.h"
using namespace DSCPP::Utils;

namespace DSCPP {
namespace Stack {

template<typename T>
class StackLinkedListCustomized {
 public:
  StackLinkedListCustomized();
  ~StackLinkedListCustomized();

 protected:
  StackLinkedListCustomized(const StackLinkedListCustomized& o);
  StackLinkedListCustomized& operator=(const StackLinkedListCustomized& o);

 public:
  bool IsEmpty() const;
  bool IsFull() const;
  T Top() const;
  StackLinkedListCustomized& Push(const T& x);
  StackLinkedListCustomized& Pop(T& x);

  void Shrink(); // remove redundant/free link nodes
  void Output(ostream& os) const;

 private:
  template<typename E>
  class LinkNode {
   private:
    E data;
    LinkNode<E>* next;
    LinkNode<E>* prev;
    friend class StackLinkedListCustomized<E>;
  };

  LinkNode<T>* nodes;
  LinkNode<T>* top;
  LinkNode<T>* prevtop; // used when top is NULL but nodes isn't NULL
};

template<typename T>
StackLinkedListCustomized<T>::StackLinkedListCustomized() {
  nodes = NULL;
  top = NULL;
  prevtop = NULL;
}

template<typename T>
StackLinkedListCustomized<T>::~StackLinkedListCustomized() {
  while (nodes != NULL) {
    LinkNode<T>* p = nodes;
    nodes = nodes->next;
    delete p;
  }
}

template<typename T>
bool StackLinkedListCustomized<T>::IsEmpty() const {
  return NULL == top;
}

template<typename T>
bool StackLinkedListCustomized<T>::IsFull() const {
  try {
    LinkNode<T>* p = new LinkNode<T>();
    if (p != NULL) {
      delete p;
      return true;
    } else {
      return false;
    }
  } catch (...) {
    return false;
  }
}

template<typename T>
T StackLinkedListCustomized<T>::Top() const {
  if (IsEmpty()) {
    throw new OutOfBounds();
  }

  return top->data;
}

template<typename T>
StackLinkedListCustomized<T>& StackLinkedListCustomized<T>::Push(const T& x) {
  if (top == nodes) {
    LinkNode<T>* p = new LinkNode<T>();
    p->data = x;
    p->next = top;
    p->prev = NULL;
    if (top != NULL) {
      top->prev = p;
    }
    top = p;
    nodes = p;
  } else {
    if (top != NULL) {
      top = top->prev;
    } else {
      top = prevtop;
    }
    top->data = x;
  }

  return *this;
}

template<typename T>
StackLinkedListCustomized<T>& StackLinkedListCustomized<T>::Pop(T& x) {
  if (IsEmpty()) {
    throw new OutOfBounds();
  }

  x = top->data;
  prevtop = top; // save it as previous top pointer
  top = top->next;
  return *this;
}

template<typename T>
void StackLinkedListCustomized<T>::Shrink() {
  while (nodes != top) {
    LinkNode<T>* p = nodes;
    nodes = nodes->next;
    delete p;
  }

  if (nodes != NULL) {
    nodes->prev = NULL;
  }

  prevtop = NULL;
}

template<typename T>
void StackLinkedListCustomized<T>::Output(ostream& os) const {
  os << "Stack items: ";

  LinkNode<T>* p = top;
  while (p && p->next) { // position to the last node
    p = p->next;
  }

  while (p != top) {
    os << p->data << " ";
    p = p->prev;
  }

  if (top) { // do not omit the top node
    os << top->data << " ";
  }
}

template<typename T>
ostream& operator<<(ostream& os, const StackLinkedListCustomized<T>& s) {
  s.Output(os);
  return os;
}

}
}