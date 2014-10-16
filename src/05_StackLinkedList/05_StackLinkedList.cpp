//
// File: 05_StackLinkedList.cpp
// Test case for linked list stack. Do Hanoi moves without recursively calls.
//
#include <iostream>
using namespace std;

#include "StackLinkedList.h"
using namespace DSCPP::Stack;

void DoHanoiRecursively(char t1, char t2, char t3, int n)
{
    if (n == 1) {
        cout << t1 << " --> " << t3 << endl;
    } else {
        DoHanoiRecursively(t1, t3, t2, n - 1);
        cout << t1 << " --> " << t3 << endl;
        DoHanoiRecursively(t2, t1, t3, n - 1);
    }
}

class HanoiParameter {
public:
    HanoiParameter() {}
    HanoiParameter(char a, char b, char c, int i) : from(a), via(b), to(c), n(i) {}
    char from;
    char via;
    char to;
    int n;
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

    s.Push(HanoiParameter(from, via, to, n));

    while (!s.IsEmpty()) {
        x = s.Top();
        if (x.n == 1) {
            cout << x.from << " --> " << x.to << endl;
            s.Pop(t);
        } else {
            s.Push(HanoiParameter(x.from, x.to, x.via, x.n - 1));
        }
    }
}


int main(int argc, char* argv[])
{
//     DoHanoiRecursively('A', 'B', 'C', 3);
    return 0;
}
