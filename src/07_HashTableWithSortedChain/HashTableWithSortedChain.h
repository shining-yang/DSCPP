//
// File: HashTableWithSortedChain.h
// Hash table implemented with sorted chain list.
// Shining Yang <y.s.n@live.com>, 2014-12-02
//
#pragma once

#include "../07_SortedChain/SortedChain.h"
#include "../Utility/Exception.h"
#include <iostream>
using namespace std;
using namespace DSCPP::SortedLinearList;
using namespace DSCPP::Utils;

namespace DSCPP {
namespace Hash {

template <typename E, typename K> class HashTableWithSortedChain {
public:
  HashTableWithSortedChain(int divisor = 16);
  ~HashTableWithSortedChain();

public:
  bool Search(const K &k, E &e) const;
  HashTableWithSortedChain<E, K> &Insert(const E &e);
  HashTableWithSortedChain<E, K> &Delete(const K &k, E &e);

  void Output(std::ostream &os) const;

private:
  int D;                       // number of buckets
  SortedChain<E, K> *elements; // sorted chain array
};

template <typename E, typename K>
HashTableWithSortedChain<E, K>::HashTableWithSortedChain(int divisor /*= 16*/) {
  if (divisor <= 0) {
    throw new BadInitializer();
  }

  D = divisor;
  elements = new SortedChain<E, K>[divisor];
}

template <typename E, typename K>
HashTableWithSortedChain<E, K>::~HashTableWithSortedChain() {
  delete[] elements;
}

template <typename E, typename K>
bool HashTableWithSortedChain<E, K>::Search(const K &k, E &e) const {
  return elements[k % D].Search(k, e);
}

template <typename E, typename K>
HashTableWithSortedChain<E, K> &
HashTableWithSortedChain<E, K>::Insert(const E &e) {
  K k = e; // auto conversion from E to K
  elements[k % D].InsertDistinct(e);
  return *this;
}

template <typename E, typename K>
HashTableWithSortedChain<E, K> &
HashTableWithSortedChain<E, K>::Delete(const K &k, E &e) {
  elements[k % D].Delete(k, e);
  return *this;
}

template <typename E, typename K>
void HashTableWithSortedChain<E, K>::Output(std::ostream &os) const {
  for (int i = 0; i < D; i++) {
    os << "Hash bucket " << i << ": ";
    os << elements[i] << endl;
  }
}

template <typename E, typename K>
ostream &operator<<(ostream &os, const HashTableWithSortedChain<E, K> &obj) {
  obj.Output(os);
  return os;
}

} // namespace Hash
} // namespace DSCPP
