//
// File: 07_HashTableWithSortedChain.cpp
//
#include "HashTableWithSortedChain.h"
#include <iostream>
using namespace std;
using namespace DSCPP::Hash;

int main(int argc, char **argv) {
  int dummy;
  HashTableWithSortedChain<int, int> h;
  cout << h << endl;

  for (int i = 0; i < 100; i++) {
    h.Insert(i);
  }
  cout << h << endl;

  cout << "Find item: " << (h.Search(50, dummy) ? "Yes" : "No") << endl;
  cout << "Find item: " << (h.Search(60, dummy) ? "Yes" : "No") << endl;

  for (int i = 0; i < 100; i++) {
    if (i % 3 == 0) {
      h.Delete(i, dummy);
    }
  }
  cout << h << endl;

  cout << "Find item: " << (h.Search(50, dummy) ? "Yes" : "No") << endl;
  cout << "Find item: " << (h.Search(60, dummy) ? "Yes" : "No") << endl;

  return 0;
}