//
// File: Heap.h
// Heap described using linear list. The root node starts at index 0.
// Shining Yang <y.s.n@live.com>, 2014-12-12
//
// ����[��ȫ������] ������������һ���⣬������Ľ�㶼�����ģ���������һ���㼯�п���
// ����[���������С����] ÿ���ڵ��ֵ�����ڣ�С�ڣ���������ӽڵ㣨����еĻ���ֵ����
// ����[���ѣ���С�ѣ�] �����С������ȫ������
//
#pragma once

#include <cmath>
#include <iostream>
#include "../Utility/Exception.h"

using namespace std;
using namespace DSCPP::Utils;

namespace DSCPP {
namespace PriorityQueue {

template<typename T>
class Heap {
 public:
  Heap(int capcity = 16);
  virtual ~Heap();

 public:
  bool IsEmpty() const;
  bool IsFull() const;
  int GetLength() const;
  int GetCapacity() const;
  T GetMin() const;
  Heap<T>& Insert(const T& e);
  Heap<T>& DeleteMin(T& e);
  void Output(ostream& os) const;
  void PrintTreeVertically(ostream& os, int width) const;

 public:
  static void Sort(T a[], int n);

 protected:
  void _PrintTreeAtLevel(ostream& os, const T* pElement, int nLevel,
                         int nCount, int nWidth) const;
  void _Attach(T pArray[], int nArrayLength, int nElementCount);
  void _Detach();

 private:
  int capacity;
  int length;
  T* elements;
};

//
// Heap-sort. (Sort using a heap)
//
template<typename T>
void Heap<T>::Sort(T a[], int n) {
  T x;
  Heap<T> hp(n);
  hp._Attach(a, n, n);
  while (n > 0) {
    hp.DeleteMin(x);
    hp.elements[--n] = x;
  }
  hp._Detach();
}

//
// Associate with a specific memory block and build a heap on it.
//
template<typename T>
void Heap<T>::_Attach(T pArray[], int nArrayLength, int nElementCount) {
  if (!pArray || (nElementCount < 0) || (nArrayLength < nElementCount)) {
    throw new InvalideArgument();
  }

  if (elements) {
    delete[] elements;
  }

  length = nElementCount;
  capacity = nArrayLength;
  elements = pArray;

  for (int n = (length - 1) / 2; n >= 0; n--) {
    T x = elements[n];
    int m = n * 2 + 1; // left child
    while (m < length) {
      if ((m < length - 1) && (elements[m] > elements[m + 1])) {
        m++;
      }

      if (x <= elements[m]) {
        break;
      }

      elements[(m - 1) / 2] = elements[m];
      m = m * 2 + 1;
    }

    elements[(m - 1) / 2] = x;
  }
}

//
// Detach the associated working memory.
//
template<typename T>
void Heap<T>::_Detach() {
  this->capacity = 0;
  this->length = 0;
  this->elements = NULL;
}

template<typename T>
Heap<T>::Heap(int capacity /* = 16*/) {
  this->length = 0;
  this->capacity = capacity;
  this->elements = new T[capacity];
}

template<typename T>
Heap<T>::~Heap() {
  delete[] elements;
}

template<typename T>
bool Heap<T>::IsEmpty() const {
  return length == 0;
}

template<typename T>
bool Heap<T>::IsFull() const {
  return length == capacity;
}

template<typename T>
int Heap<T>::GetLength() const {
  return length;
}

template<typename T>
int Heap<T>::GetCapacity() const {
  return capacity;
}

template<typename T>
T Heap<T>::GetMin() const {
  if (IsEmpty()) {
    throw new ItemUnderFlow();
  }

  return elements[0];
}

template<typename T>
Heap<T>& Heap<T>::Insert(const T& e) {
  if (IsFull()) {
    throw new ItemOverFlow();
  }

  int n = length++;
  while ((n != 0) && (e < elements[(n - 1) / 2])) {
    elements[n] = elements[(n - 1) / 2]; // move downwards
    n = (n - 1) / 2;
  }

  elements[n] = e;
  return *this;
}

template<typename T>
Heap<T>& Heap<T>::DeleteMin(T& e) {
  if (IsEmpty()) {
    throw new ItemUnderFlow();
  }

  e = elements[0];

  T x = elements[--length]; // the last node

  int n = 0; // root
  int m = n * 2 + 1; // left child
  while (m < length) {
    if ((m < length - 1) && (elements[m] > elements[m + 1])) {
      m++; // always point to the little one
    }

    if (x <= elements[m]) {
      break;
    }

    elements[n] = elements[m]; // move upwards
    n = m;
    m = n * 2 + 1;
  }

  elements[n] = x;
  return *this;
}

template<typename T>
void Heap<T>::Output(ostream& os) const {
  for (int i = 0; i < length; i++) {
    os << elements[i] << ", ";
  }
}

template<typename T>
ostream& operator<<(ostream& os, const Heap<T>& obj) {
  obj.Output(os);
  return os;

}

template<typename T>
void Heap<T>::PrintTreeVertically(ostream& os, int width) const {
  int nPrinted = 0;
  int nTotalLevel = 1 + static_cast<int>(log(length) / log(2));

  for (int nLevel = 0; nLevel < nTotalLevel; nLevel++) {
    int nCountAtLevel = 1 << nLevel;
    int nRemain = length - nPrinted;
    int nCount = (nRemain < nCountAtLevel) ? nRemain : nCountAtLevel;

    _PrintTreeAtLevel(os, elements + nPrinted, nLevel, nCount, width);
    nPrinted += nCount;
  }
}

template<typename T>
void Heap<T>::_PrintTreeAtLevel(ostream& os, const T* pElement, int nLevel,
                                int nCount, int nWidth) const {
  // ���о��֣���N����㽫���򻮷�Ϊ N+1 �ȷ�
  int nSegmentLen = nWidth / ((1 << nLevel) + 1);
  int nBlanks = nSegmentLen - 1; // assume that ELEMENT occupies 1 character
  for (int i = 0; i < nCount; i++) {
    for (int j = 0; j < nBlanks; j++) {
      os << " ";
    }
    os << *(pElement + i);
  }
  os << endl;
}

}
}