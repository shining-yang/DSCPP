// 02_InsertionSort.cpp : Defines the entry point for the console application.
//
// ֻ��һ��Ԫ�ص�������һ���������飬���Կ��Դӽ������������n��Ԫ�صĵ�һ��Ԫ�ص�
// ���鿪ʼ��ͨ���ѵڶ���Ԫ�ز��뵽�����Ԫ�����У����Եõ�һ����СΪ2���������顣
// ���������Ԫ�ؿ��Եõ�һ����СΪ3���������顣�������ַ�������������ȥ��
// ���ս��õ�һ����СΪn���������飬��������ʽΪ��������insertion sort��
//
// 2014/8/29, Shining Yang <y.s.n@live.com>
//
#include <stdio.h>

template<class T>
void Insert(T a[], int n, const T& x) {
  // ����������a[0 : n-1]�в���Ԫ��x
  int i;
  for (i = n - 1; i >= 0 && a[i] > x; i--) {
    a[i + 1] = a[i];
  }
  a[i + 1] = x;
}

template<class T>
void InsertionSort(T a[], int n) {
  // ��a[0 : n-1]���в�������
  for (int i = 1; i < n; i++) {
    T t = a[i]; /* Insert() needs reference, make a copy, otherwise wrong */
    Insert(a, i, t);
  }
}

//{{ insertion sorting in a single function
template<class T>
void InsertionSort2(T a[], int n) {
  int i, j;
  for (i = 1; i < n; i++) {
    T t = a[i];
    for (j = i - 1; j >= 0 && a[j] > t; j--) {
      a[j + 1] = a[j];
    }
    a[j + 1] = t;
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
  InsertionSort2(a, sizeof(a) / sizeof(a[0]));
  PrintArray(a, sizeof(a) / sizeof(a[0]));
  return 0;
}
