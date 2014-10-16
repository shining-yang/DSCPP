//
// File: 05_StackLinkedList.cpp
// Test case for linked list stack. Do Hanoi moves without recursively calls.
//
#include <iostream>
using namespace std;

#include "StackLinkedList.h"
using namespace DSCPP::Stack;

void HanoiRecursively(char t1, char t2, char t3, int n)
{
    static int _num = 0;
    
    if (n == 1) {
        cout << "[" << ++_num << "] " << t1 << " --> " << t3 << endl;
    } else {
        HanoiRecursively(t1, t3, t2, n - 1);
        HanoiRecursively(t1, t2, t3, 1);
        HanoiRecursively(t2, t1, t3, n - 1);
    }
}

class HanoiParameter {
public:
    HanoiParameter() {}
    HanoiParameter(char a, char b, char c, int i, int j) : from(a), via(b), to(c), n(i), d(j) {}
    char from;
    char via;
    char to;
    int n; // number of plates to be moved
    int d; // direction: -1, 0, 1
};

class Hanoi {
public:
    Hanoi(char a, char b, char c, int i) : from(a), via(b), to(c), n(i) {}

public:
    void Perform();

private:
    char from;
    char via;
    char to;
    int n;
    DSCPP::Stack::StackLinkedList<HanoiParameter> s;
};

void Hanoi::Perform()
{
    HanoiParameter x, t;
    static int _num = 0;
    s.Push(HanoiParameter(from, via, to, n, -1));
    while (!s.IsEmpty()) {
        s.Pop(x);
        switch (x.d) {
        case -1:
            s.Push(HanoiParameter(x.from, x.via, x.to, x.n, 0));
            if (x.n > 1) {
                s.Push(HanoiParameter(x.from, x.to, x.via, x.n - 1, -1));
            }
            break;
        case 0:
            cout << "[" << ++_num << "] " << x.from << " --> " << x.to << endl;
            if (x.n > 1) {
                s.Push(HanoiParameter(x.via, x.from, x.to, x.n - 1, 1));
            }
            break;
        case 1:
            s.Push(HanoiParameter(x.from, x.via, x.to, x.n, 0));
            if (x.n > 1) {
                s.Push(HanoiParameter(x.from, x.to, x.via, x.n - 1, -1));
            }
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    int n = 4;

#if 0
    HanoiRecursively('A', 'B', 'C', n);
#else
    Hanoi h('A', 'B', 'C', n);
    h.Perform();
#endif

    return 0;
}
