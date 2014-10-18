//
// Test case for stack
//
#include "StackLinkedListCustomized.h"
using namespace DSCPP::Stack;

int main(int argc, char* argv[])
{
    char x;
    StackLinkedListCustomized<char> s;

    s.Push('A').Push('B').Pop(x).Push('C').Push('D').Push('E');
    cout << s << endl;

    s.Pop(x);
    cout << s << endl;

    s.Push('B');
    s.Push('X');
    cout << s << endl;

    return 0;
}