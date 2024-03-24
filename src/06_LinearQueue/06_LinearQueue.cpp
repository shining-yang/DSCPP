//
// File: 06_LinearQueue.cpp
//
#include "LinearQueue.h"
using namespace DSCPP::Queue;

int main(int argc, char *argv[]) {
  LinearQueue<char> q;
  char c = 'A';
  int n = 0;
  for (int i = 0; i < 15; i++) {
    q.EnQueue(c + i);
  }

  // q.EnQueue('X');
  n = q.GetCapacity();
  n = q.GetLength();

  cout << q << endl;

  q.DeQueue(c);
  cout << q << endl;

  q.DeQueue(c).EnQueue('X');
  cout << q << endl;

  return 0;
}