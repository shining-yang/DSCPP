//
// File: 05_StackLinkedList.cpp
// Test case for linked list stack. Do Hanoi moves without recursively calls.
// 2014-10-17, Shining Yang <y.s.n@live.com>
//
#include <iostream>
using namespace std;

#include "../05_StackLinearList/StackLinearList.h"
#include "StackLinkedList.h"
using namespace DSCPP::Stack;

#include "../PerformanceStatistics/HighResTimeCounter.h"
#pragma comment(lib, "PerformanceStatistics")

void HanoiRecursively(char t1, char t2, char t3, int n)
{
    static int _times = 0;

    if (n == 1) {
//         cout << "[" << ++_times << "] " << t1 << " --> " << t3 << endl;
    } else {
        HanoiRecursively(t1, t3, t2, n - 1);
        HanoiRecursively(t1, t2, t3, 1);
        HanoiRecursively(t2, t1, t3, n - 1);
    }
}

void HanoiRecursively2(char t1, char t2, char t3, int n)
{
    static int _times = 0;

    if (n == 1) {
//         cout << "[" << ++_times << "] " << t1 << " --> " << t3 << endl;
    } else {
        HanoiRecursively2(t1, t3, t2, n - 1);
//         cout << "[" << ++_times << "] " << t1 << " --> " << t3 << endl;
        HanoiRecursively2(t2, t1, t3, n - 1);
    }
}

class HanoiPara {
public:
    HanoiPara() {}
    HanoiPara(char a, char b, char c, int i, int j) : from(a), via(b), to(c), num(i), type(j) {}
    char from;
    char via;
    char to;
    int num; // number of plates to be moved
    int type; // Type of move { 0: move the single plate, 1: move a pile of plates }

    enum { SINGLE, MULTIPLE };
};

template<typename T>
class Hanoi {
public:
    Hanoi(char a, char b, char c, int n) : from(a), via(b), to(c), num(n) {}

public:
    void Perform();

private:
    char from;
    char via;
    char to;
    int num;
#if 0
    DSCPP::Stack::StackLinkedList<HanoiPara> s;
#elif 0
    DSCPP::Stack::Stack<HanoiPara> s;
#else
    T s; // the stack
#endif
};

template<typename T>
void Hanoi<T>::Perform()
{
    static int _times = 0;

    HanoiPara x;
    s.Push(HanoiPara(from, via, to, num, 1));
    while (!s.IsEmpty()) {
        s.Pop(x);
        switch (x.type) {
        case HanoiPara::MULTIPLE:
            s.Push(HanoiPara(x.from, x.via, x.to, x.num, HanoiPara::SINGLE));
            if (x.num > 1) {
                s.Push(HanoiPara(x.from, x.to, x.via, x.num - 1, HanoiPara::MULTIPLE));
            }
            break;
        case HanoiPara::SINGLE:
//             cout << "[" << ++_times << "] " << x.from << " --> " << x.to << endl;
            if (x.num > 1) {
                s.Push(HanoiPara(x.via, x.from, x.to, x.num - 1, HanoiPara::MULTIPLE));
            }
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    int n = 20;
    CHighResTimeCounter tc;

    //----
    tc.Begin();
    HanoiRecursively('A', 'B', 'C', n);
    tc.End();
    cout << "Time costs on recursive: " << tc.GetElapsedTimeInMS() << " ms" << endl;

    //----
    tc.Begin();
    HanoiRecursively2('A', 'B', 'C', n);
    tc.End();
    cout << "Time costs on recursive2: " << tc.GetElapsedTimeInMS() << " ms" << endl;

    //----
    tc.Begin();
    Hanoi<DSCPP::Stack::Stack<HanoiPara> > h1('A', 'B', 'C', n);
    h1.Perform();
    tc.End();
    cout << "Time costs on non-recursive (Stack): " << tc.GetElapsedTimeInMS() << " ms" << endl;

    //----
    tc.Begin();
    Hanoi<DSCPP::Stack::Stack2<HanoiPara> > h2('A', 'B', 'C', n);
    h2.Perform();
    tc.End();
    cout << "Time costs on non-recursive (Stack2): " << tc.GetElapsedTimeInMS() << " ms" << endl;

    //----
    tc.Begin();
    Hanoi<DSCPP::Stack::StackLinkedList<HanoiPara> > h3('A', 'B', 'C', n);
    h3.Perform();
    tc.End();
    cout << "Time costs on non-recursive (StackLinkedList): " << tc.GetElapsedTimeInMS() << " ms" << endl;

    //
    // {{ Test results on 20 plates when commenting off `cout' statements 
    //
    // Time costs on recursive : 61 ms
    // Time costs on recursive2 : 42 ms
    // Time costs on non-recursive(Stack) : 765 ms
    // Time costs on non-recursive(Stack2) : 468 ms
    // Time costs on non-recursive(StackLinkedList) : 12502 ms
    // }}
    //
    return 0;
}
