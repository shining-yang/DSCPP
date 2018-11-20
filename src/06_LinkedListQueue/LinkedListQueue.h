//
// File: LinkedListQueue.h
// Queue implemented with linked list.
// 2014-10-28, Shining Yang <y.s.n@live.com>
//
#pragma once
#include "../03_DoublyLinkedCircularList/DoublyLinkedCircularList.h"

namespace DSCPP {
namespace Queue {

template<typename T>
class LinkedListQueue : private DoublyLinkedCircularList<T> {
 public:
  LinkedListQueue();
  ~LinkedListQueue();

 protected:
  LinkedListQueue(const LinkedListQueue<T>& obj);
  LinkedListQueue<T>& operator=(const LinkedListQueue<T>& obj);

 public:
  bool IsEmpty() const;
  bool IsFull() const;
  int Length() const;
  T Front() const;
  T Rear() const;
  LinkedListQueue<T>& EnQueue(const T& x);
  LinkedListQueue<T>& DeQueue(T& x);

  void Output(ostream& os) const;
};

template<typename T>
void LinkedListQueue<T>::Output(ostream& os) const {
  DoublyLinkedCircularList<T>::Output(os);
}

template<typename T>
LinkedListQueue<T>::LinkedListQueue() {
}

template<typename T>
LinkedListQueue<T>::~LinkedListQueue() {
}

template<typename T>
bool LinkedListQueue<T>::IsEmpty() const {
  return DoublyLinkedCircularList<T>::IsEmpty();
}

template<typename T>
bool LinkedListQueue<T>::IsFull() const {
  return false;
}

template<typename T>
int LinkedListQueue<T>::Length() const {
  return DoublyLinkedCircularList<T>::Length();
}

template<typename T>
T LinkedListQueue<T>::Front() const {
  if (IsEmpty()) {
    throw new OutOfBounds;
  }

  T x;
  DoublyLinkedCircularList<T>::Find(0, x);
  return x;
}

template<typename T>
T LinkedListQueue<T>::Rear() const {
  if (IsEmpty()) {
    throw new OutOfBounds;
  }

  T x;
  DoublyLinkedCircularList<T>::FindReversely(0, x);
  return x;
}

template<typename T>
LinkedListQueue<T>& LinkedListQueue<T>::EnQueue(const T& x) {
  DoublyLinkedCircularList<T>::PushBack(x);
  return *this;
}

template<typename T>
LinkedListQueue<T>& LinkedListQueue<T>::DeQueue(T& x) {
  DoublyLinkedCircularList<T>::PopFront(x);
  return *this;
}

template<typename T>
ostream& operator<<(ostream& os, const LinkedListQueue<T>& obj) {
  obj.Output(os);
  return os;
}

}
}
