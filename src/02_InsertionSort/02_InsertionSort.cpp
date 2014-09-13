// 02_InsertionSort.cpp : Defines the entry point for the console application.
//
// 只有一个元素的数组是一个有序数组，所以可以从仅包含欲排序的n个元素的第一个元素的
// 数组开始。通过把第二个元素插入到这个单元数组中，可以得到一个大小为2的有序数组。
// 插入第三个元素可以得到一个大小为3的有序数组。按照这种方法继续进行下去，
// 最终将得到一个大小为n的有序数组，这种排序方式为插入排序（insertion sort）
//
// 2014/8/29, Shining Yang <y.s.n@live.com>
//
#include <stdio.h>

template<class T>
void Insert(T a[], int n, const T& x)
{// 向有序数组a[0 : n-1]中插入元素x
    int i;
    for (i = n - 1; i >= 0 && a[i] > x; i--) {
        a[i + 1] = a[i];
    }
    a[i + 1] = x;
}

template<class T>
void InsertionSort(T a[], int n)
{// 对a[0 : n-1]进行插入排序
    for (int i = 1; i < n; i++) {
        T t = a[i]; /* Insert() needs reference, make a copy, otherwise wrong */
        Insert(a, i, t);
    }
}

//{{ insertion sorting in a single function
template<class T>
void InsertionSort2(T a[], int n)
{
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

void PrintArray(int a[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[])
{
    int a[] = { 10, 21, 13, 44, 5 };
    InsertionSort2(a, sizeof(a) / sizeof(a[0]));
    PrintArray(a, sizeof(a) / sizeof(a[0]));
    return 0;
}
