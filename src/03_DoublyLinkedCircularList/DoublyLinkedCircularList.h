//
// File: DoublyLinkedCircularList.h
// Doubly linked circular list with a dummy HEAD node.
// 2014-10-28, Shining Yang <y.s.n@live.com>
//
#include <iostream>
using namespace std;

#include "../Utility/Exception.h"
using namespace DSCPP::Utils;

template<typename T> class DoublyLinkedCircularList;

template<typename T>
class DoublyLinkedCircularListNode {
private:
    DoublyLinkedCircularListNode<T>* prev;
    DoublyLinkedCircularListNode<T>* next;
    T data;

    friend class DoublyLinkedCircularList<T>;
};

template<typename T>
class DoublyLinkedCircularList {
public:
    DoublyLinkedCircularList();
    ~DoublyLinkedCircularList();

protected:
    DoublyLinkedCircularList(const DoublyLinkedCircularList<T>& obj);
    DoublyLinkedCircularList<T>& operator=(const DoublyLinkedCircularList<T>& obj);

public:
    int Length() const;
    bool IsEmpty() const;
    void Clear();
    bool Find(int k, T& x) const; // Get the number k element (0-based)
    bool FindReversely(int k, T& x) const;
    int Search(const T& x) const; // Get position of x
    DoublyLinkedCircularList<T>& Delete(int k, T& x); // valid k: [0, Length() - 1]
    DoublyLinkedCircularList<T>& Insert(int k, const T& x); // valid k: [0, Length() - 1]

    DoublyLinkedCircularList<T>& PushBack(const T& x);
    DoublyLinkedCircularList<T>& PopBack(T& x);
    DoublyLinkedCircularList<T>& PushFront(const T& x);
    DoublyLinkedCircularList<T>& PopFront(T& x);

    void Output(ostream& os) const;

protected:
    void _CreateHeadNode();
    void _DestroyHeadNode();
    void _Init();
    void _ClearNodes();
    DoublyLinkedCircularListNode<T>* _LocateNode(int k) const;
    void _InsertNode(DoublyLinkedCircularListNode<T>* p, const T& x);
    void _DeleteNode(DoublyLinkedCircularListNode<T>* p, T& x);

private:
    DoublyLinkedCircularListNode<T>* head;
};

template<typename T>
void DoublyLinkedCircularList<T>::_CreateHeadNode()
{
    head = new DoublyLinkedCircularListNode<T>;
}

template<typename T>
void DoublyLinkedCircularList<T>::_DestroyHeadNode()
{
    delete head;
}

template<typename T>
void DoublyLinkedCircularList<T>::_Init()
{
    head->prev = head;
    head->next = head;
}

template<typename T>
void DoublyLinkedCircularList<T>::_ClearNodes()
{
    DoublyLinkedCircularListNode<T>* p = head->next;
    while (p != head) {
        DoublyLinkedCircularListNode<T>* q = p->next;
        delete p;
        p = q;
    }
}

template<typename T>
DoublyLinkedCircularList<T>::DoublyLinkedCircularList()
{
    _CreateHeadNode();
    _Init();
}

template<typename T>
DoublyLinkedCircularList<T>::~DoublyLinkedCircularList()
{
    _ClearNodes();
    _DestroyHeadNode();
}

template<typename T>
void DoublyLinkedCircularList<T>::Clear()
{
    _ClearNodes();
    _Init();
}

template<typename T>
int DoublyLinkedCircularList<T>::Length() const
{
    int n = 0;
    for (DoublyLinkedCircularListNode<T>* p = head->next;
        p != head;
        p = p->next) {
        n++;
    }

    return n;
}

template<typename T>
bool DoublyLinkedCircularList<T>::IsEmpty() const
{
    return (head->next == head);
}

template<typename T>
bool DoublyLinkedCircularList<T>::Find(int k, T& x) const
{
    if (k < 0) { throw new InvalideArgument(); }

    int n = 0;
    for (DoublyLinkedCircularListNode<T>* p = head->next;
        p != head;
        p = p->next) {
        if (k == n++) {
            x = p->data;
            return true;
        }
    }

    return false;
}

template<typename T>
bool DoublyLinkedCircularList<T>::FindReversely(int k, T& x) const
{
    if (k < 0) { throw new InvalideArgument(); }

    int n = 0;
    for (DoublyLinkedCircularListNode<T>* p = head->prev;
        p != head;
        p = p->prev, n++) {
        if (k == n) {
            x = p->data;
            return true;
        }
    }

    return false;
}

template<typename T>
int DoublyLinkedCircularList<T>::Search(const T& x) const
{
    // make use of the dummy head node for better efficiency, since
    // this will reduce comparisons.
    head->data = x;

    int n = 0;
    DoublyLinkedCircularListNode<T>* p = head->next;
    while (p->data != x) {
        p = p->next;
        n++;
    }

    return (p == head) ? -1 : n;
}

template<typename T>
DoublyLinkedCircularListNode<T>* DoublyLinkedCircularList<T>::_LocateNode(int k) const
{
    // negative not allowed
    // valid range: [0, Length() - 1]
    if (k < 0) { throw new InvalideArgument(); }

    int n = 0;
    for (DoublyLinkedCircularListNode<T>* p = head->next;
        p != head;
        p = p->next, n++) {
        if (k == n) {
            return p;
        }
    }

    throw new OutOfBounds();
}

template<typename T>
void DoublyLinkedCircularList<T>::_DeleteNode(DoublyLinkedCircularListNode<T>* p, T& x)
{
    if (p) {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        x = p->data;
        delete p;
    }
}

template<typename T>
void DoublyLinkedCircularList<T>::_InsertNode(DoublyLinkedCircularListNode<T>* p, const T& x)
{
    if (p) {
        DoublyLinkedCircularListNode<T>* q = new DoublyLinkedCircularListNode<T>;
        q->data = x;
        q->next = p;
        q->prev = p->prev;
        p->prev->next = q;
        p->prev = q;
    }
}

template<typename T>
DoublyLinkedCircularList<T>& DoublyLinkedCircularList<T>::Delete(int k, T& x)
{
    DoublyLinkedCircularListNode<T>* p = _LocateNode(k);
    _DeleteNode(p, x);
    return *this;
}

template<typename T>
DoublyLinkedCircularList<T>& DoublyLinkedCircularList<T>::Insert(int k, const T& x)
{
    DoublyLinkedCircularListNode<T>* p = _LocateNode(k);
    _InsertNode(p, x);
    return *this;
}

template<typename T>
DoublyLinkedCircularList<T>& DoublyLinkedCircularList<T>::PushBack(const T& x)
{
    _InsertNode(head, x);
    return *this;
}

template<typename T>
DoublyLinkedCircularList<T>& DoublyLinkedCircularList<T>::PopBack(T& x)
{
    if (IsEmpty()) {
        throw new OutOfBounds;
    }

    _DeleteNode(head->prev, x);
    return *this;
}

template<typename T>
DoublyLinkedCircularList<T>& DoublyLinkedCircularList<T>::PushFront(const T& x)
{
    _InsertNode(head->next, x);
    return *this;
}

template<typename T>
DoublyLinkedCircularList<T>& DoublyLinkedCircularList<T>::PopFront(T& x)
{
    if (IsEmpty()) {
        throw new OutOfBounds;
    }

    _DeleteNode(head->next, x);
    return *this;
}

template<typename T>
void DoublyLinkedCircularList<T>::Output(ostream& os) const
{
    os << "Length: " << Length() << ". Nodes: ";
    for (DoublyLinkedCircularListNode<T>* p = head->next;
        p != head;
        p = p->next) {
        os << p->data << ", ";
    }
}

template<typename T>
ostream& operator<<(ostream& os, const DoublyLinkedCircularList<T>& obj)
{
    obj.Output(os);
    return os;
}