//
// File: SortedChain.h
// Sorted chain.
// Shining Yang <y.s.n@live.com>, 2014-11-17
//
#pragma once

#include <iostream>
#include "../Utility/Exception.h"

using namespace std;
using namespace DSCPP::Utils;

namespace DSCPP {
namespace SortedLinearList {

// E: element type, K: key type
template<typename E, typename K> class SortedChainNode;
template<typename E, typename K> class SortedChain;

template<typename E, typename K>
class SortedChainNode {
  friend class SortedChain<E, K>;
 private:
  E data;
  SortedChainNode<E, K>* link;
};

template<typename E, typename K>
class SortedChain {
 public:
  SortedChain();
  ~SortedChain();

  bool IsEmpty() const;
  int Length() const;
  bool Search(const K& k, E& e) const;
  SortedChain<E, K>& Delete(const K& k, E& e);
  SortedChain<E, K>& Insert(const E& e);
  SortedChain<E, K>& InsertDistinct(const E& e);
  void Output(std::ostream& os) const;

 private:
  SortedChainNode<E, K>* first;
};

template<typename E, typename K>
SortedChain<E, K>::SortedChain() : first(NULL) {
}

template<typename E, typename K>
SortedChain<E, K>::~SortedChain() {
  while (first) {
    SortedChainNode<E, K>* p = first->link;
    delete first;
    first = p;
  }
}

template<typename E, typename K>
bool SortedChain<E, K>::IsEmpty() const {
  return first == NULL;
}

template<typename E, typename K>
int SortedChain<E, K>::Length() const {
  int n = 0;
  for (SortedChainNode<E, K>* p = first; p; p = p->link) {
    n++;
  }
  return n;
}

template<typename E, typename K>
bool SortedChain<E, K>::Search(const K& k, E& e) const {
  SortedChainNode<E, K>* p = first;
  while (p && p->data < k) {
    p = p->link;
  }

  if (p && p->data == k) {
    e = p->data;
    return true;
  }

  return false;
}

template<typename E, typename K>
SortedChain<E, K>& SortedChain<E, K>::Delete(const K& k, E& e) {
  SortedChainNode<E, K>* p = first;
  SortedChainNode<E, K>* q = NULL;
  while (p && p->data < k) {
    q = p;
    p = p->link;
  }

  if (p && p->data == k) {
    if (q) {
      q->link = p->link;
    } else {
      first = p->link;
    }

    e = p->data;
    delete p;
    return *this;
  }

  throw new ItemNotExisted();
}

template<typename E, typename K>
SortedChain<E, K>& SortedChain<E, K>::Insert(const E& e) {
  K k = e; // make an auto conversion
  SortedChainNode<E, K>* p = first;
  SortedChainNode<E, K>* q = NULL;
  while (p && p->data < k) {
    q = p;
    p = p->link;
  }

  // comment following to allow duplicate elements
//     if (p && p->data == k) {
//         throw new ItemAlreadyExisted();
//     }

  SortedChainNode<E, K>* r = new SortedChainNode < E, K > ;
  r->data = e;
  r->link = p;

  if (q) {
    q->link = r;
  } else {
    first = r;
  }

  return *this;
}

template<typename E, typename K>
SortedChain<E, K>& SortedChain<E, K>::InsertDistinct(const E& e) {
  K k = e; // make an auto conversion
  SortedChainNode<E, K>* p = first;
  SortedChainNode<E, K>* q = NULL;
  while (p && p->data < k) {
    q = p;
    p = p->link;
  }

  if (p && p->data == k) {
    throw new ItemAlreadyExisted();
  }

  SortedChainNode<E, K>* r = new SortedChainNode<E, K>;
  r->data = e;
  r->link = p;

  if (q) {
    q->link = r;
  } else {
    first = r;
  }

  return *this;
}

template<typename E, typename K>
void SortedChain<E, K>::Output(std::ostream& os) const {
  for (SortedChainNode<E, K>* p = first; p; p = p->link) {
    os << p->data << " ";
  }
}

template<typename E, typename K>
std::ostream& operator<<(std::ostream& os, const SortedChain<E, K>& ch) {
  ch.Output(os);
  return os;
}

}
}