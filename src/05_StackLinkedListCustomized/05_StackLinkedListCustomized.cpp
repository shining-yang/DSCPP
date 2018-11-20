//
// Test case for stack
//
#include "StackLinkedListCustomized.h"
using namespace DSCPP::Stack;

int main(int argc, char* argv[]) {
  char x;
  StackLinkedListCustomized<char> s;

  s.Push('A').Push('B').Push('C').Push('D').Push('E');
  cout << s << endl;

  s.Pop(x);
  cout << s << endl;

  s.Push('B');
  s.Push('X');
  cout << s << endl;

  s.Pop(x).Pop(x).Pop(x);
  cout << s << endl;

  s.Push('Y');
  s.Shrink();
  cout << s << endl;

  s.Push('X');
  s.Shrink();
  cout << s << endl;

  s.Pop(x).Pop(x).Pop(x);
  cout << s << endl;

  s.Shrink();
  s.Pop(x).Pop(x);
  cout << s << endl;

  s.Shrink();
  s.Push('A');
  cout << s << endl;
  return 0;
}