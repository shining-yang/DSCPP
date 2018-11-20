//
// Test case for linked list Queue
//
#include "LinkedListQueue.h"
using namespace DSCPP::Queue;

int main(int argc, char* argv[]) {
  LinkedListQueue<char> q;
  cout << "Queue empty? " << (q.IsEmpty() ? "Yes" : "No") << endl;

  char c = 'A';
  int n = 0;
  for (int i = 0; i < 15; i++) {
    q.EnQueue(c + i);
  }

  cout << "Queue empty? " << (q.IsEmpty() ? "Yes" : "No") << endl;

  //q.EnQueue('X');
  n = q.Length();

  cout << q << endl;
  cout << "Front: " << q.Front() << ", Rear: " << q.Rear() << endl;

  q.DeQueue(c);
  cout << q << endl;
  cout << "Front: " << q.Front() << ", Rear: " << q.Rear() << endl;

  q.DeQueue(c).EnQueue('X');
  cout << q << endl;
  cout << "Front: " << q.Front() << ", Rear: " << q.Rear() << endl;

  return 0;
}
