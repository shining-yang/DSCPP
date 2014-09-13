//
// File: 02_BinarySearch.cpp
//
// Binary search
//
// 2014/8/25, Shining Yang <y.s.n@live.com>
//
#include <stdio.h>

// Binary search from a sorted array
template<class T>
int BinarySearch(T a[], int n, const T& x)
{
    int lo = 0;
    int hi = n - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (a[mid] == x) {
            return mid;
        } else if (a[mid] < x) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return -1;
}

// Binary search recursively
template<class T>
int BinarySearchRecursively(T a[], int low, int high, const T& x)
{
    if (low > high) {
        return -1;
    }

    int middle = (low + high) / 2;
    if (a[middle] == x) {
        return middle;
    } else if (a[middle] < x) {
        return BinarySearchRecursively(a, middle + 1, high, x);
    } else {
        return BinarySearchRecursively(a, low, middle - 1, x);
    }
}

int main(int argc, char* argv[])
{
    int a[] = { 1, 2, 3, 5, 8, 13, 21, 34, 65, 99 };
    int x = 2;
#if 0
    printf("Index: %d\n",
        BinarySearch(a, sizeof(a) / sizeof(a[0]), x));
#else
    printf("Index: %d\n",
        BinarySearchRecursively(a, 0, sizeof(a) / sizeof(a[0]) - 1, x));
#endif
    return 0;
}