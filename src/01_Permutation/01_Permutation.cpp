// 01_Permutation.cpp : Defines the entry point for the console application.
//
// 使用递归函数生成排列
//
// 2014/8/23, Shining Yang <y.s.n@live.com>
//
#include <iostream>
#include <string>
using namespace std;

#include "../Utility/Misc.h"
using namespace DSCPP::Utils;


//
// @param a[] element array
// @param k start index
// @param m last index
//
template<typename T>
void Permutate(T a[], int k, int m) {
  if (k == m - 1) {
    static int _counter = 0;
    cout << ++_counter << ":  ";
    for (int i = 0; i < m; i++)
      cout << a[i] << ' ';
    cout << endl;
  } else {
    for (int i = k; i < m; i++) {
      Swap(a[i], a[k]);
      Permutate(a, k + 1, m);
      Swap(a[i], a[k]);
    }
  }
}

// Add another permute, 2014-12-22
void permute(string sofar, string rest) {
  if (rest.empty()) {
    cout << sofar << endl;
  } else {
    for (unsigned int i = 0; i < rest.length(); i++) {
      permute(sofar + rest[i], rest.substr(0, i) + rest.substr(i + 1));
    }
  }
}

int main(int argc, char* argv[]) {
  char a[] = { 'A', 'B', 'C', 'D', 'E' };
  Permutate<char>(a, 0, sizeof(a) / sizeof(a[0]));

  string s = "abcd";
  permute("", s);
  return 0;
}

