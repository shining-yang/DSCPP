//
// File: WinnerTree.h
// Winner tree.
// Shining Yang <y.s.n@live.com>, 2014-12-15
//
// http://www.geeksforgeeks.org/tournament-tree-and-binary-heap/
// Tournament tree is a form of min(max) heap which is a complete binary tree.
// Every external node represents a player and internal node represents winner.
// In a tournament tree every internal node contains winner and every leaf node
// contains one player.
//
// Tournament tree is also called Winner tree.
//
// Implementation notes:
// For processing convenience, internal array indices are 1-based.
// But we provide normal usage for caller, which means array are 0-based.
// Therefore, user can directly call `Initialize(a[], #a, _Cmp)' to attach an
// array and `Winner()' to get index of the winner.
//
#pragma once
#include "../Utility/Exception.h"
using namespace DSCPP::Utils;

namespace DSCPP {
namespace WinnerTree {

template<typename T>
class WinnerTree {
 public:
  WinnerTree(int size = 16);
  virtual ~WinnerTree();

  void Initialize(T a[], int size, int (*winner)(T a[], int b, int c));
  void Replay(int i, int (*winner)(T a[], int b, int c));
  int Winner() const;

 protected:
  void _Play(int p, int lc, int rc, int (*winner)(T a[], int b, int c));

 private:
  int MaxSize;
  int n; //��ǰ��С
  int LowExt; //��ײ���ⲿ�ڵ�
  int offset; //2^k-1
  int *t; //Ӯ��������
  T   *e; //Ԫ������
};

template<typename T>
void WinnerTree<T>::Replay(int i, int (*winner)(T a[], int b, int c)) {
  i++; // Our array starts from 1

  if (i <= 0 || i > n) {
    throw new OutOfBounds();
  }

  int p,  // �����ڵ�
      lc, // p������
      rc; // p���Һ���

  // �ҵ���һ�������ڵ㼰����Ů
  if (i <= LowExt) {//����ײ㿪ʼ
    p = (offset + i) / 2;
    lc = 2 * p - offset; // p������
    rc = lc + 1;
  } else {
    p = (i - LowExt + n - 1) / 2;
    if (2 * p == n - 1) {
      lc = t[2 * p];
      rc = i;
    } else {
      lc = 2 * p - n + 1 + LowExt;
      rc = lc + 1;
    }
  }

  t[p] = winner(e, lc, rc);

  // ʣ��ڵ�ı���
  p /= 2; //�Ƶ����ڵ㴦
  for (; p >= 1; p /= 2) {
    if (2 * p >= n - 1) {
      t[p] = winner(e, t[2 * p], LowExt + 1);
    } else {
      t[p] = winner(e, t[2 * p], t[2 * p + 1]);
    }
  }
}

// ��t[p]����ʼ����
template<typename T>
void WinnerTree<T>::_Play(int p, int lc, int rc, int (*winner)(T a[], int b, int c)) {
  // lc��rc��t[p]�ĺ���
  t[p] = winner(e, lc, rc);

  // �����Һ��Ӵ���������жೡ����
  while (p > 1 && p % 2) {//���Һ��Ӵ�
    t[p / 2] = winner(e, t[p - 1], t[p]);
    p /= 2; //�����ڵ�
  }
}

// Return the index of final winner. -1 means error.
template<typename T>
int WinnerTree<T>::Winner() const {
  return n ? (t[1] - 1) : -1;
}

template<typename T>
void WinnerTree<T>::Initialize(T a[], int size, int (*winner)(T a[], int b, int c)) {
  if (size > MaxSize || size < 2) {
    throw new BadInitializer();
  }

  n = size;

  // TRICK:
  // Internal process using index [1...size], so we do a little trick here.
  // Actually, we will never touch [0]
  e = a - 1;

  // ���� s = 2 ^ log(n - 1)
  // С�ڵ���(n - 1)�����2�η���
  int i, s;
  for (s = 1; 2 * s <= n - 1; s *= 2) {
  }

  LowExt = 2 * (n - s);
  offset = 2 * s - 1;

  // ��ײ��ⲿ�ڵ�ı���
  for (i = 2; i <= LowExt; i += 2) {
    _Play((offset + i) / 2, i - 1, i, winner);
  }

  // ���������ⲿ�ڵ�
  if (n % 2) {//��n����ʱ���ڲ��ڵ���ⲿ�ڵ�ı���
    _Play(n / 2, t[n - 1], LowExt + 1, winner);
    i = LowExt + 3;
  } else {
    i = LowExt + 2;
  }

  // iΪ����ʣ��ڵ�
  for (; i <= n; i += 2) {
    _Play((i - LowExt + n - 1) / 2, i - 1, i, winner);
  }
}

template<typename T>
WinnerTree<T>::WinnerTree(int size/* = 16*/) {
  MaxSize = size;
  t = new int[size];
  n = 0;
  LowExt = 0;
  offset = 0;
  e = NULL;
}

template<typename T>
WinnerTree<T>::~WinnerTree() {
  delete[] t;
}

}
}