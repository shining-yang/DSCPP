//
// File: 07_HashTable.cpp
// Shining Yang <y.s.n@live.com>, 2014-11-21
//
#include "HashTable.h"

template<typename E, typename K>
void ShowHashInfo(DSCPP::Hash::HashTable<E, K>& ht) {
  cout << "Hash is full? " << (ht.IsFull() ? "Yes" : "No") << endl;
  cout << "Hash is empty? " << (ht.IsEmpty() ? "Yes" : "No") << endl;
  cout << "Hash:\t\t" << ht << endl;
}

int main(int argc, char* argv[]) {
  char dummy;
  char ch = 'A';
  int num = 16;
  DSCPP::Hash::HashTable<char, char> ht(num);

  //--
  for (char i = ch; i < ch + num; i++) {
    ht.Insert(i);
  }
  ShowHashInfo(ht);

  //--
  for (char i = ch; i < ch + num; i++) {
    ht.Delete(i, dummy);
  }
  ShowHashInfo(ht);

  //--
  for (char i = ch; i < ch + num; i++) {
    ht.Insert(i);
  }
  ht.Delete('E', dummy).Delete('H', dummy).Delete('B', dummy);
  ShowHashInfo(ht);

  //--
  ht.Insert('X').Insert('Y').Insert('Z');
  ShowHashInfo(ht);

  //--
  ht.Delete('X', dummy).Delete('Y', dummy).Delete('Z', dummy);
  ShowHashInfo(ht);

  //--
  ht.Insert('X');
  ht.Delete('X', dummy);
  ht.Insert('X');
  ht.Delete('X', dummy);
  ht.Insert('X');
  ShowHashInfo(ht);

  return 0;
}