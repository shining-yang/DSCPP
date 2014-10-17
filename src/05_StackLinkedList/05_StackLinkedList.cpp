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
        cout << "[" << ++_times << "] " << t1 << " --> " << t3 << endl;
    } else {
        HanoiRecursively(t1, t3, t2, n - 1);
        HanoiRecursively(t1, t2, t3, 1);
        HanoiRecursively(t2, t1, t3, n - 1);
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
#if 1
    DSCPP::Stack::StackLinkedList<HanoiPara> s;
#elif 1
    DSCPP::Stack::Stack<HanoiPara> s;
#else
    DSCPP::Stack::Stack2<HanoiPara> s;
#endif
};

void Hanoi::Perform()
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
            cout << "[" << ++_times << "] " << x.from << " --> " << x.to << endl;
            if (x.num > 1) {
                s.Push(HanoiPara(x.via, x.from, x.to, x.num - 1, HanoiPara::MULTIPLE));
            }
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    int n = 16;

    CHighResTimeCounter tc;
    tc.Begin();
    HanoiRecursively('A', 'B', 'C', n);
    tc.End();

    CHighResTimeCounter tc2;
    tc2.Begin();
    Hanoi h('A', 'B', 'C', n);
    h.Perform();
    tc2.End();

    cout << "Time costs on recursive: " << tc.GetElapsedTimeInMS() << " ms" << endl;
    cout << "Time costs on non-recursive: " << tc2.GetElapsedTimeInMS() << " ms" << endl;

    //
    // Test result on 16 plates
    //
    // {{
    // Time costs on recursive : 508773 ms
    // Time costs on non - recursive : 458749 ms
    // }}
    //
    // {{ DSCPP::Stack::Stack
    // Time costs on recursive: 44047 ms
    // Time costs on non - recursive: 35915 ms
    // }}
    //
    // {{ DSCPP::Stack::Stack2
    // Time costs on recursive: 42686 ms
    // Time costs on non - recursive: 42655 ms
    // }}
    //
    return 0;
}
