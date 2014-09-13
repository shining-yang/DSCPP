// 01_Permutation.cpp : Defines the entry point for the console application.
//
// 使用递归函数生成排列
//
// 2014/8/23, Shining Yang <y.s.n@live.com>
//
#include <iostream>
using namespace std;

template<typename T>
inline void Swap(T& x, T& y)
{
    T z = x; x = y; y = z;
}

//
// @param a[] element array
// @param k start index
// @param m last index
//
template<typename T>
void Permutate(T a[], int k, int m)
{
    if (k == m) {
        static int _counter = 0;
        cout << ++_counter << ":  ";
        for (int i = 0; i <= m; i++)
            cout << a[i] << ' ';
        cout << endl;
    } else {
        for (int i = k; i <= m; i++) {
            Swap(a[i], a[k]);
            Permutate(a, k + 1, m);
            Swap(a[i], a[k]);
        }
    }
}


int main(int argc, char* argv[])
{
    char a[] = { 'A', 'B', 'C', 'D', 'E' };
    Permutate<char>(a, 0, sizeof(a) / sizeof(a[0]) - 1);
	return 0;
}

