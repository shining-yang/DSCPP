// 02_SelectionSort.cpp : Defines the entry point for the console application.
//
// 2014/8/25, Shining Yang <y.s.n@live.com>
//
// 首先找出最大的元素，把它移动到a[n-1]，然后在余下的n-1个元素中寻找最大的元素
// 并把它移动到a[n-2]，如此进行下去，这种排序方法为选择排序（selection sort）
//
#include <stdio.h>
#include "../Utility/Misc.h"
using namespace DSCPP::Utils;


template<class T>
int GetMaxIndex(T a[], int n) {
  int index = 0;
  for (int i = 1; i < n; i++) {
    if (a[index] < a[i]) {
      index = i;
    }
  }
  return index;
}

template<class T>
void SelectionSort(T a[], int n) {
  for (int i = n; i > 1; i--) {
    int index = GetMaxIndex(a, i);
    Swap(a[index], a[i - 1]);
  }
}

// {{ Stop sorting immediately when it's already sorted
template<class T>
void SelectionSortStopInTime(T a[], int n) {
  // 及时终止的选择排序
  bool sorted = false;
  for (int size = n; !sorted && (size > 1); size--) {
    int pos = 0;
    sorted = true;
    for (int i = 0; i < size; i++) { // 找最大元素
      if (a[pos] <= a[i]) {
        pos = i;
      } else {
        sorted = false; // 未按序排列
      }
    }
    Swap(a[pos], a[size - 1]);
  }
}
//}}


void PrintArray(int a[], int n) {
  for (int i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

int main(int argc, char* argv[]) {
  int a[] = { 10, 5, 21, 13, 44, 13, 5 };
#if 0
  SelectionSort(a, sizeof(a) / sizeof(a[0]));
#else
  SelectionSortStopInTime(a, sizeof(a) / sizeof(a[0]));
#endif
  PrintArray(a, sizeof(a) / sizeof(a[0]));
  return 0;
}
