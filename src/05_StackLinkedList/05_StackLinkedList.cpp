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

#define NO_CONSOLE_OUTPUT

void HanoiRecursively(char t1, char t2, char t3, int n)
{
    static int _times = 0;

    if (n == 1) {
#ifndef NO_CONSOLE_OUTPUT
        cout << "[" << ++_times << "] " << t1 << " --> " << t3 << endl;
#endif
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
#ifndef NO_CONSOLE_OUTPUT
        cout << "[" << ++_times << "] " << t1 << " --> " << t3 << endl;
#endif
    } else {
        HanoiRecursively2(t1, t3, t2, n - 1);
#ifndef NO_CONSOLE_OUTPUT
        cout << "[" << ++_times << "] " << t1 << " --> " << t3 << endl;
#endif
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
    T s; // the stack
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
#ifndef NO_CONSOLE_OUTPUT
            cout << "[" << ++_times << "] " << x.from << " --> " << x.to << endl;
#endif
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

    //----
    CHighResTimeCounter tc1;
    tc1.Begin();
    HanoiRecursively('A', 'B', 'C', n);
    tc1.End();

    //----
    CHighResTimeCounter tc2;
    tc2.Begin();
    HanoiRecursively2('A', 'B', 'C', n);
    tc2.End();

    //----
    CHighResTimeCounter tc3;
    tc3.Begin();
    Hanoi<DSCPP::Stack::Stack<HanoiPara> > h3('A', 'B', 'C', n);
    h3.Perform();
    tc3.End();

    //----
    CHighResTimeCounter tc4;
    tc4.Begin();
    Hanoi<DSCPP::Stack::Stack2<HanoiPara> > h4('A', 'B', 'C', n);
    h4.Perform();
    tc4.End();

    //----
    CHighResTimeCounter tc5;
    tc5.Begin();
    Hanoi<DSCPP::Stack::StackLinkedList<HanoiPara> > h5('A', 'B', 'C', n);
    h5.Perform();
    tc5.End();


    cout << "Time costs on recursive: " << tc1.GetElapsedTimeInMS() << " ms" << endl;
    cout << "Time costs on recursive2: " << tc2.GetElapsedTimeInMS() << " ms" << endl;
    cout << "Time costs on non-recursive (Stack): " << tc3.GetElapsedTimeInMS() << " ms" << endl;
    cout << "Time costs on non-recursive (Stack2): " << tc4.GetElapsedTimeInMS() << " ms" << endl;
    cout << "Time costs on non-recursive (StackLinkedList): " << tc5.GetElapsedTimeInMS() << " ms" << endl;

    //
    // {{ Test results on 20 plates when commenting off `cout' statements 
    //
    // Time costs on recursive: 55 ms
    // Time costs on recursive2: 43 ms
    // Time costs on non-recursive (Stack): 754 ms
    // Time costs on non-recursive (Stack2): 474 ms
    // Time costs on non-recursive (StackLinkedList): 5999 ms
    // }}
    //
    return 0;
}
