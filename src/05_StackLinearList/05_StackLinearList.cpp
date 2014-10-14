//
// File: 05_StackLinearList.cpp
//
#include "StackLinearList.h"

int main(int argc, char* argv[])
{
    char c;
    DSCPP::Stack::Stack<char> sc;

    cout << "Stack is empty: " << (sc.IsEmpty() ? "Yes" : "No") << endl;
    cout << "Stack is full: " << (sc.IsFull() ? "Yes" : "No") << endl;
    sc.Push('A');
    sc.Push('B');
    sc.Push('C');
    char x = sc.Top();
    sc.Pop(c);
    sc.Push('D');
    sc.Pop(c);
    sc.Pop(c);
    sc.Pop(c);

    return 0;
}