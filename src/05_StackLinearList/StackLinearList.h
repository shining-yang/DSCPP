//
// File: StackLinearList.h
//
// Stack implemented with linear list.
//
// 2014-10-14, Shining Yang <y.s.n@live.com>
//
#pragma once

#if 0
��Stack��Ч�ʡ�
��T��һ���ڲ���������ʱ����ջ�Ĺ��캯�������������ĸ����Ծ�ΪO(1)���������û�
�Զ������ʱ�����캯�������������ĸ����Ծ�ΪO(MaxStackSize)������ÿ����ջ�����ĸ�
���Ծ�ΪO(1)��ע��ͨ����LinearList����Stack��һ����������˱���������һ����Ҳʹ��
��Ŀɿ��Եõ��ܴ���ߣ���ΪLinearList�������Բ�����Ϊ����ȷ�ġ�Ȼ�������ҵ��ǣ���
���д�ļ򻯴���������Ч�ʵ���ʧ�����磬Ϊ�����ջ�����һ��Ԫ�أ�����Ҫȷ����ջ��
����length()��Ȼ����ú���Insert()��Insert�������ȱ����жϲ�������Ƿ��Խ�磬Ȼ����Ҫ
����һ��for ѭ���Ŀ�����ִ��0��Ԫ�ص��ƶ���Ϊ����������Ŀ��������԰�Stack�����һ��
���࣬�����������ࡣ
��һ��Ǳ�ڵ�������������StackҲ���ܵ�LinearList�����������Ƶ�Ӱ�졣���磬����Ϊ
��������ΪT�ĳ�Ա��������� << �� == ����Ϊǰ�����ڶ����Ա���� << �����أ��������ڶ�
                            LinearList::Search�����ء�
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
