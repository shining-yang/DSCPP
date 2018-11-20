//
// File: StackLinearList.h
//
// Stack implemented with linear list.
//
// 2014-10-14, Shining Yang <y.s.n@live.com>
//
#pragma once

#if 0
【Stack的效率】
当T是一个内部数据类型时，堆栈的构造函数和析构函数的复杂性均为O(1)，当Ｔ是用户
自定义的类时，构造函数和析构函数的复杂性均为O(MaxStackSize)。其余每个堆栈操作的复
杂性均为O(1)。注意通过从LinearList派生Stack，一方面大大减少了编码量，另一方面也使程
序的可靠性得到很大提高，因为LinearList经过测试并被认为是正确的。然而，不幸的是，代
码编写的简化带来了运行效率的损失。例如，为了向堆栈中添加一个元素，首先要确定堆栈的
长度length()，然后调用函数Insert()。Insert函数首先必须判断插入操作是否会越界，然后需要
付出一个for 循环的开销来执行0个元素的移动。为了消除额外的开销，可以把Stack定义成一个
基类，而不是派生类。
另一种潜在的问题是派生类Stack也会受到LinearList本身所受限制的影响。例如，必须为
数据类型为T的成员定义操作符 << 和 == ，因为前者用于对线性表操作 << 的重载，后者用于对
                            LinearList::Search的重载。
#endif

#include "../03_LinearList/LinearList.h"
#include "../Utility/Exception.h"
                            using namespace DSCPP::Utils;

namespace DSCPP {
namespace Stack {

template<typename T>
class LinearStack : private LinearList<T> {
 public:
enum {
  DEFAULT_STACK_SIZE = 20
};

LinearStack(int c = DEFAULT_STACK_SIZE);
  ~LinearStack();

 public:
  bool IsEmpty();
  bool IsFull();
  LinearStack<T>& Push(const T& e);
  LinearStack<T>& Pop(T& e);
  T Top() const;
};

template<typename T>
LinearStack<T>::LinearStack(int c) : LinearList<T>(c) {
}

template<typename T>
LinearStack<T>::~LinearStack() {
}

template<typename T>
bool LinearStack<T>::IsEmpty() {
  return LinearList<T>::IsEmpty();
}

template<typename T>
bool LinearStack<T>::IsFull() {
  return LinearList<T>::GetMaxSize() == LinearList<T>::Length();
}

template<typename T>
LinearStack<T>& LinearStack<T>::Push(const T& e) {
  LinearList<T>::Insert(LinearList<T>::Length(), e);
  return *this;
}

template<typename T>
LinearStack<T>& LinearStack<T>::Pop(T& e) {
  LinearList<T>::Delete(LinearList<T>::Length() - 1, e);
  return *this;
}

template<typename T>
T LinearStack<T>::Top() const {
  if (IsEmpty()) {
    throw new OutOfBounds();
  }

  T x;
  LinearList<T>::Find(LinearList<T>::Length() - 1, x);
  return x;
}

//==============================================================================
//= LinearStack2
//= not derived from linear list
//==============================================================================
template<typename T>
class LinearStack2 {
 public:
  enum {
    DEFAULT_STACK_SIZE = 20
  };

  LinearStack2(int c = DEFAULT_STACK_SIZE) : capacity(c), top(-1) {
    elements = new T[c];
  }

  ~LinearStack2() {
    delete[] elements;
  }

 protected:
  LinearStack2(const LinearStack2<T>& s);
  LinearStack2<T>& operator=(const LinearStack2<T>& s);

 public:
  bool IsEmpty() const {
    return top < 0;
  }

  bool IsFull() const {
    return top >= capacity - 1;
  }

  LinearStack2<T>& Push(const T& x) {
    if (IsFull()) {
      throw new OutOfBounds();
    }

    elements[++top] = x;
    return *this;
  }

  LinearStack2<T>& Pop(T& x) {
    if (IsEmpty()) {
      throw new OutOfBounds();
    }

    x = elements[top--];
    return *this;
  }

  T Top() const {
    if (IsEmpty()) {
      throw new OutOfBounds();
    }

    return elements[top];
  }

 private:
  int capacity;
  int top;
  T* elements;
};

}
}
