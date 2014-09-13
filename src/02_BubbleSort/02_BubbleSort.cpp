// 02_BubbleSort.cpp : Defines the entry point for the console application.
//
// 2014/8/25, Shining Yang <y.s.n@live.com>
//
// 冒泡排序（bubble sort）采用一种“冒泡策略”把最大元素移到右部。在冒泡过程中，
// 对相邻的元素进行比较，如果左边的元素大于右边的元素，则交换这两个元素。
//

#include <stdio.h>

template<class T>
void Swap(T& x, T& y)
{
    T t = x; x = y; y = t;
}

template<class T>
void Bubble(T a[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1]) {
            Swap(a[i], a[i + 1]);
        }
    }
}

template<class T>
void BubbleSort(T a[], int n)
{
    for (int i = n; i > 1; i--) {
        Bubble(a, i);
    }
}

//{{ Stop bubble sorting when it's already sorted
template<class T>
void BubbleSortStopInTime(T a[], int n)
{ // 及时终止的冒泡排序
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
#if 0
    BubbleSort(a, sizeof(a) / sizeof(a[0]));
#else
    BubbleSortStopInTime(a, sizeof(a) / sizeof(a[0]));
#endif
    PrintArray(a, sizeof(a) / sizeof(a[0]));
    return 0;
}

