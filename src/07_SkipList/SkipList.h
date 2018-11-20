//
// File: SkipList.h
// Skip list.
// 2014-11-11, Shining Yang <y.s.n@live.com>
//
#pragma once
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include "../Utility/Exception.h"
using namespace DSCPP::Utils;

namespace DSCPP {
namespace SkipList {

template<typename E, typename K> class SkipList;

template<typename E, typename K>
class SkipNode {
  friend class SkipList<E, K>;
 protected:
  SkipNode(int size) {
    link = new SkipNode<E, K>*[size];
  }

  ~SkipNode() {
    delete[] link;
  }

 private:
  SkipNode<E, K>** link;
  E data;
};

template<typename E, typename K>
class SkipList {
 public:
  SkipList(const K& Large, int MaxE = 10000, float p = 0.5);
  ~SkipList();
  bool Search(const K& k, E& e);
  SkipList<E, K>& Insert(const E& e);
  SkipList<E, K>& Delete(const K& k, E& e);
  void Output(std::ostream& os) const;

 private:
  void Randomize();
  int Level();
  SkipNode<E, K>* SaveSearch(const K& k);
  int MaxLevel;   // maximum levels allowed
  int Levels;     // current links count
  int CutOff;     // used to determine level
  K TailKey;      // a key that large enough
  SkipNode<E, K> *head;
  SkipNode<E, K> *tail;
  SkipNode<E, K> **last;
};

template<typename E, typename K>
SkipList<E, K>::SkipList(const K& Large, int MaxE /*= 10000*/, float p /*= 0.5*/) {
  CutOff = static_cast<int>(p * RAND_MAX);
  MaxLevel = static_cast<int>(ceil(log((double)MaxE) / log(1 / p)) - 1);
  TailKey = Large;
  Randomize();
  Levels = 0;
  head = new SkipNode<E, K>(MaxLevel + 1);
  tail = new SkipNode<E, K>(0);
  last = new SkipNode<E, K>*[MaxLevel + 1];
  tail->data = Large;

  for (int i = 0; i <= MaxLevel; i++) {
    head->link[i] = tail;
  }
}

template<typename E, typename K>
SkipList<E, K>::~SkipList() {
  while (head != tail) {
    SkipNode<E, K>* next = head->link[0];
    delete head;
    head = next;
  }

  delete tail;
  delete[] last;
}

template<typename E, typename K>
bool SkipList<E, K>::Search(const K& k, E& e) {
  SkipNode<E, K>* p = head;

  for (int i = Levels; i >= 0; i--) {
    while (p->link[i]->data < k) {
      p = p->link[i];
    }
  }

  if (k == p->link[0]->data) {
    e = p->link[0]->data;
    return true;
  }

  return false;
}

template<typename E, typename K>
SkipList<E, K>& SkipList<E, K>::Insert(const E& e) {
  K k = e; // auto-conversion from Element to Key
  if (k >= TailKey) {
    throw new InvalideArgument();
  }

  SkipNode<E, K>* p = SaveSearch(k);
  if (k == p->data) {
    throw new ItemAlreadyExisted();
  }

  int lev = Level();
  if (lev > Levels) {
    lev = ++Levels;
    last[lev] = head;
  }

  SkipNode<E, K>* q = new SkipNode<E, K>(lev + 1);
  q->data = e;
  for (int i = 0; i <= lev; i++) {
    q->link[i] = last[i]->link[i];
    last[i]->link[i] = q;
  }

  return *this;
}

template<typename E, typename K>
SkipList<E, K>& SkipList<E, K>::Delete(const K& k, E& e) {
  if (k >= TailKey) {
    throw new InvalideArgument();
  }

  SkipNode<E, K>* p = SaveSearch(k);
  if (k != p->data) {
    throw new ItemNotExisted();
  }

  for (int i = 0; i <= Levels && last[i]->link[i] == p; i++) {
    last[i]->link[i] = p->link[i];
  }

  while (Levels > 0 && head->link[Levels] == tail) {
    Levels--;
  }

  e = p->data;
  delete p;
  return *this;
}

template<typename E, typename K>
void SkipList<E, K>::Randomize() {
  srand((unsigned)time(NULL));
}

// 产生一个随机级号，该级号<= MaxLevel
template<typename E, typename K>
int SkipList<E, K>::Level() {
  int lev = 0;
  while (rand() < CutOff) {
    lev++;
  }

  return (lev <= MaxLevel) ? lev : MaxLevel;
}

// 搜索k 并保存最终所得到的位置
// 在每一级链中搜索
// 调整指针p，使其恰好指向可能与k匹配的节点的前一个节点
template<typename E, typename K>
SkipNode<E, K>* SkipList<E, K>::SaveSearch(const K& k) {
  SkipNode<E, K>* p = head;
  for (int i = Levels; i >= 0; i--) {
    while (p->link[i]->data < k) {
      p = p->link[i];
    }

    last[i] = p;
  }

  return p->link[0];
}

template<typename E, typename K>
void SkipList<E, K>::Output(std::ostream& os) const {
  for (int i = Levels; i >= 0; i--) {
    for (SkipNode<E, K>* p = head->link[i]; p != tail; p = p->link[i]) {
      os << p->data << ", ";
    }

    os << std::endl;
  }
}

template<typename E, typename K>
std::ostream& operator<<(std::ostream& os, const SkipList<E, K>& sl) {
  sl.Output(os);
  return os;
}

}
}