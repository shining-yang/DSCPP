//
// File: Array.h
//
// Shining Yang <y.s.n@live.com>, 2014/09
//
#pragma once
#include <ostream>
using namespace std;
#include "../Utility/Exception.h"
using namespace DSCPP::Utils;

template<class T> class Array;

template<class T>
class ArrayElem {
  friend class Array<T>;
 private:
  T data;
};

template<class T>
class Array {
 public:
  Array(int n);
  ~Array();

 public:
  const T& operator[](int n) const;
  T& operator[](int n);
  void Output(ostream& os) const;

 private:
  int size;
  ArrayElem<T>* elements;
};

template<class T>
Array<T>::Array(int n) {
  size = n;
  elements = new ArrayElem<T>[size];
}

template<class T>
Array<T>::~Array() {
  delete[] elements;
}

template<class T>
const T& Array<T>::operator[](int n) const {
  if (n < 0 || n >= size) {
    throw new OutOfRange();
  }

  return elements[n].data;
}

template<class T>
T& Array<T>::operator[](int n) {
  return const_cast<T&>(
           static_cast<const Array<T>&>(*this)[n]);
}

template<class T>
void Array<T>::Output(ostream& os) const {
  for (int i = 0; i < size; i++) {
    os << elements[i].data << " ";
  }
}

template<class T>
ostream& operator<<(ostream& os, const Array<T>& a) {
  a.Output(os);
  return os;
}
