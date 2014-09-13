// 02_RankSort.cpp : Defines the entry point for the console application.
//
// 2014/8/28, Shining Yang <y.s.n@live.com>
// 
// [计算名次] 元素在队列中的名次（rank）可定义为队列中所有比它小的元素数目加上在
// 它左边出现的与它相同的元素数目。例如，给定一个数组a = [4, 3, 9, 3, 7]作为队列，
// 则各元素的名次为r = [2, 0, 4, 1, 3]
//

#include <stdio.h>

template<class T>
void Swap(T& x, T& y)
{
    T t = x; x = y; y = t;
}

//
// 对于i 的每个取值，执行比较的次数为i ,所以总的比较次数为
// 1 + 2 + 3 + ⋯ + n-1 = (n-1)n/2
//
template<class T>
void Rank(T a[], int n, int r[])
{ //计算a[0 : n - 1]中n个元素的排名
    for (int i = 0; i < n; i++)
        r[i] = 0; //初始化
    //逐对比较所有的元素
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] <= a[i]) {
                r[i]++;
            } else {
                r[j]++;
            }
        }
    }
}

//
// 元素移动次数为2n (需要借助额外的存储空间完成排序)
//
template<class T>
void Rearrange(T a[], int n, int r[])
{ //按序重排数组a中的元素，使用附加数组u
    T *u = new T[n];
    //在u中移动到正确的位置
    for (int i = 0; i < n; i++)
        u[r[i]] = a[i];
    //移回到a中
    for (int i = 0; i < n; i++)
        a[i] = u[i];
    delete[] u;
}

template<class T>
void RankSort(T a[], int n)
{
    int* r = new int[n];
    if (r) {
        Rank(a, n, r);
#if 0
        Rearrange(a, n, r);
#else
        RearrangeWithoutImageArray(a, n, r);
#endif
        delete[] r;
    }
}

//
// 在原地把该数组中的元素按序重排，方法是从a[0] 开始，每次检查一个元素。
// 如果当前正在检查的元素为a[i] 且r[i] = i，那么可以跳过该元素，继续检查下一个元素；
// 如果r[i]≠i, 可以把a[i]与a[r[i]] 进行交换，交换的结果是把原a[i] 中的元素放到正确的排序位置
// （r[i]）上去。这种交换操作在位置i 处重复下去，直到应该排在位置i 处的元素被交换到位置i
// 处。之后，继续检查下一个
//
//{{ 原地重排数组元素
template<class T>
void RearrangeWithoutImageArray(T a[], int n, int r[])
{// 原地重排数组元素
    for (int i = 0; i < n; i++) {
        // 获取应该排在a[i]处的元素
        while (r[i] != i) {
            int t = r[i];
            Swap(a[i], a[t]);
            Swap(r[i], r[t]);
        }
    }
}
//}}

void PrintArray(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main(int argc, char* argv[])
{
    int a[] = { 12, 37, 4, 10, 2 };
    RankSort<int>(a, sizeof(a) / sizeof(a[0]));
    PrintArray(a, sizeof(a) / sizeof(a[0]));
	return 0;
}

