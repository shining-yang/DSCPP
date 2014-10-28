//
// File: 03_DoublyLinkedCircularList.cpp
// Test case for doubly linked circular list.
// Shining, 2014-10-28
//
#include "DoublyLinkedCircularList.h"

int A() {
    return 0;
}
int B() {
    return 1;
}
int C() {
    return 2;
}

int main(int argc, char* argv[])
{
    DoublyLinkedCircularList<char> o;

    char c = '$';
    char c2;

    int pos;
    bool found;

    pos = o.Search('$');
    //found = o.Find(pos, c2);
    
    o.PushBack(c);

    o.PushBack('.').PushBack(',').PushFront('0').PushFront('1');
    cout << o << endl;

    pos = o.Search('$');
    found = o.Find(pos, c2);

    o.Clear();

    o.PushBack('$');

    c = 'A';
    o.Insert(0, c++);
    o.Insert(1, c++);
    cout << o << endl;

    c = 'O';
    // Attention this trap:
    // o.Insert(o.Length() - 1, c++).Insert(o.Length() - 1, c++);
    o.Insert(o.Length() - 1, c++);
    o.Insert(o.Length() - 1, c++);
    cout << o << endl;
    
    c = 'X';
    o.PushBack(c++).PushBack(c++);
    cout << o << endl;

    c = '1';
    o.PushFront(c++).PushFront(c++);
    cout << o << endl;

    o.Delete(0, c).Delete(1, c);
    cout << o << endl;
    
    return 0;
}
