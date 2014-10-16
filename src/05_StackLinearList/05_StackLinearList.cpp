//
// File: 05_StackLinearList.cpp
//
#include "StackLinearList.h"

int main(int argc, char* argv[])
{
#if 0
    typedef DSCPP::Stack::Stack<char>   CharStack;
#else
    typedef DSCPP::Stack::Stack2<char>  CharStack;
#endif

    char c;
    CharStack sc;

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

#if 0
    typedef DSCPP::Stack::Stack<DSCPP::Stack::Stack<char> > CharStackStack;
#else
    typedef DSCPP::Stack::Stack2<DSCPP::Stack::Stack2<char> > CharStackStack;
#endif
    CharStackStack css;
    cout << (css.IsFull() ? "Y" : "N") << endl;
//     css.Push(sc); // Error: no proper copy-constructor/operator=() provided

    return 0;
}