// 02_BubbleSort.cpp : Defines the entry point for the console application.
//
// 2014/8/25, Shining Yang <y.s.n@live.com>
//
// ð������bubble sort������һ�֡�ð�ݲ��ԡ������Ԫ���Ƶ��Ҳ�����ð�ݹ����У�
// �����ڵ�Ԫ�ؽ��бȽϣ������ߵ�Ԫ�ش����ұߵ�Ԫ�أ��򽻻�������Ԫ�ء�
//

#include <stdio.h>
#include "../Utility/Misc.h"
using namespace DSCPP::Utils;


template<class T>
void Bubble(T a[], int n) {
  for (int i = 0; i < n - 1; i++) {
    if (a[i] > a[i + 1]) {
      Swap(a[i], a[i + 1]);
    }
  }
}

template<class T>
void BubbleSort(T a[], int n) {
  for (int i = n; i > 1; i--) {
    Bubble(a, i);
  }
}

//{{ Stop bubble sorting when it's already sorted
template<class T>
void BubbleSortStopInTime(T a[], int n) {
  // ��ʱ��ֹ��ð������
  bool sorted = false;
  for (int i = n; i > 1 && !sorted; i--) {
    sorted = true;
    for (int j = 0; j < i - 1; j++) {
      if (a[j] > a[j + 1]) {
        Swap(a[j], a[j + 1]);
        sorted = false;
      }
    }
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
  int a[] = { 10, 21, 13, 44, 5 };
#if 0
  BubbleSort(a, sizeof(a) / sizeof(a[0]));
#else
  BubbleSortStopInTime(a, sizeof(a) / sizeof(a[0]));
#endif
  PrintArray(a, sizeof(a) / sizeof(a[0]));
  return 0;
}

