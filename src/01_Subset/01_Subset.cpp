// 01_Subset.cpp : Defines the entry point for the console application.
//
// Get all subsets of a given set
//
// ���ϵ������Ӽ�
// 2014/8/25, Shining Yang <y.s.n@live.com>
//
#include <iostream>
#include <string>
using namespace std;

template<class T>
void PrintSubset(T a[], int size, int index, bool flag[]) {
  if (index < size) {
    flag[index] = false;
    PrintSubset(a, size, index + 1, flag);
    flag[index] = true;
    PrintSubset(a, size, index + 1, flag);
  } else { // get elements printed
    cout << "{ ";
    for (int i = 0; i < size; i++) {
      if (flag[i]) {
        cout << a[i];
      } else {
        cout << " ";
      }
      cout << " ";
    }
    cout << "}" << endl;
  }
}

template<class T>
void PrintSubset(T a[], int size) {
  bool* flag = new bool[size];
  if (flag) {
    PrintSubset(a, size, 0, flag);
    delete[] flag;
  }
}

void TestPrintSubset() {
  char a[] = { 'A', 'B', 'C', 'D', 'E' };
  PrintSubset<char>(a, sizeof(a) / sizeof(a[0]));
}

void printsubset(string sofar, string rest) {
  if (rest.empty()) {
    cout << sofar << endl;
  } else {
    printsubset(sofar + rest[0], rest.substr(1));
    printsubset(sofar, rest.substr(1));
  }
}

int main(int argc, char* argv[]) {
  TestPrintSubset();

  printsubset("", "abcd");
  return 0;
}

