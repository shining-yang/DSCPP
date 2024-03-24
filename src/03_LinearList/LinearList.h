//
// File: LinearList.h
// Linear list template class declaration
// Shining Yang <y.s.n@live.com>, 2014/08/29
//
#pragma once
#include <iostream>
using namespace std;
#include "../Utility/Exception.h"
using namespace DSCPP::Utils;

template <class T> class LinearList {
public:
  LinearList(int nMaxSize = 16);
  virtual ~LinearList();
  LinearList(const LinearList<T> &obj);
  LinearList<T> &operator=(const LinearList<T> &obj);

public:
  bool IsEmpty() const;
  int Length() const;
  bool Find(int k, T &x) const; // Get the number k element
  int Search(const T &x) const; // Get position of x
  LinearList<T> &Delete(int k, T &x);
  LinearList<T> &Insert(int k, const T &x);
  void Output(std::ostream &os) const;

protected:
  int GetMaxSize() const { return m_nMaxSize; }

private:
  int m_nMaxSize;
  int m_nLength;
  T *m_element;
};

template <class T> LinearList<T>::LinearList(int nMaxSize /* = 16*/) {
  m_nLength = 0;
  m_nMaxSize = nMaxSize;
  m_element = new T[nMaxSize];
}

template <class T> LinearList<T>::~LinearList() { delete[] m_element; }

template <class T> LinearList<T>::LinearList(const LinearList<T> &obj) {
  m_nLength = obj.m_nLength;
  m_nMaxSize = obj.m_nMaxSize;
  m_element = new T[obj.m_nMaxSize];

  for (int i = 0; i < m_nLength; i++) {
    m_element[i] = obj.m_element[i];
  }
}

template <class T>
LinearList<T> &LinearList<T>::operator=(const LinearList<T> &obj) {
  if (this == &obj) {
    return *this;
  }

  delete[] m_element;

  m_nLength = obj.m_nLength;
  m_nMaxSize = obj.m_nMaxSize;
  m_element = new T[obj.m_nMaxSize];

  for (int i = 0; i < m_nLength; i++) {
    m_element[i] = obj.m_element[i];
  }

  return *this;
}

template <class T> bool LinearList<T>::IsEmpty() const {
  return m_nLength == 0;
}

template <class T> int LinearList<T>::Length() const { return m_nLength; }

template <class T> bool LinearList<T>::Find(int k, T &x) const {
  if (k >= 0 && k < m_nLength) {
    x = m_element[k];
    return true;
  }

  return false;
}

template <class T> int LinearList<T>::Search(const T &x) const {
  for (int i = 0; i < m_nLength; i++) {
    if (m_element[i] == x) {
      return i;
    }
  }

  return -1;
}

template <class T> LinearList<T> &LinearList<T>::Delete(int k, T &x) {
  if (!Find(k, x)) {
    throw OutOfBounds();
  }

  for (int i = k; i < m_nLength - 1; i++) {
    m_element[i] = m_element[i + 1];
  }

  m_nLength--;
  return *this;
}

template <class T> LinearList<T> &LinearList<T>::Insert(int k, const T &x) {
  if (k < 0 || k > m_nLength) {
    throw OutOfBounds();
  }

  if (m_nLength >= m_nMaxSize) {
    throw OutOfBounds();
  }

  for (int i = m_nLength - 1; i >= k; i--) {
    m_element[i + 1] = m_element[i];
  }

  m_element[k] = x;
  m_nLength++;
  return *this;
}

template <class T> void LinearList<T>::Output(std::ostream &os) const {
  for (int i = 0; i < m_nLength; i++) {
    os << m_element[i] << " ";
  }
}
