//
// File: LinearQueue.h
// Queue implemented with linear list
// 2014-10-27, Shining Yang <y.s.n@live.com>
//
#include <iostream>
using namespace std;
#include "../Utility/Exception.h"
using namespace DSCPP::Utils;

namespace DSCPP { namespace Queue {

template<typename T>
class LinearQueue {
public:
    LinearQueue(int size = 16);
    ~LinearQueue();

protected:
    LinearQueue(const LinearQueue<T>& obj);
    LinearQueue<T>& operator=(const LinearQueue<T>& obj);

public:
    bool IsEmpty() const;
    bool IsFull() const;
    T Front() const;
    T Rear() const;
    LinearQueue<T>& EnQueue(const T& x);
    LinearQueue<T>& DeQueue(T& x);

    int GetCapacity() const;
    int GetLength() const;

    void Output(ostream& os) const;

private:
    int front;
    int rear;
    int capacity;
    T* base;
};

template<typename T>
LinearQueue<T>::LinearQueue(int size /*= 16*/)
{
    if (size < 0) {
        throw new InvalideArgument();
    }

    this->front = 0;
    this->rear = 0;
    this->capacity = size + 1; // 1 for dummy
    this->base = new T[this->capacity];
}

template<typename T>
LinearQueue<T>::~LinearQueue()
{
    delete[] this->base;
}

template<typename T>
int LinearQueue<T>::GetCapacity() const
{
    return this->capacity - 1;
}

template<typename T>
int LinearQueue<T>::GetLength() const
{
    if (rear >= front) {
        return rear - front;
    } else {
        return (rear + capacity) - front;
    }
}

template<typename T>
bool LinearQueue<T>::IsEmpty() const
{
    return front == rear;
}

template<typename T>
bool LinearQueue<T>::IsFull() const
{
    return (rear + 1) % capacity == front;
}

template<typename T>
T LinearQueue<T>::Front() const
{
    if (IsEmpty()) {
        throw new OutOfBounds();
    }

    return base[front];
}

template<typename T>
T LinearQueue<T>::Rear() const
{
    if (IsEmpty()) {
        throw new OutOfBounds();
    }

    return base[(rear + capacity - 1) % capacity];
}

template<typename T>
LinearQueue<T>& LinearQueue<T>::EnQueue(const T& x)
{
    if (IsFull()) {
        throw new OutOfBounds();
    }

    base[rear++] = x;
    rear %= capacity;
    return *this;
}

template<typename T>
LinearQueue<T>& LinearQueue<T>::DeQueue(T& x)
{
    if (IsEmpty()) {
        throw new OutOfBounds();
    }

    front++;
    front %= capacity;
    return *this;
}

template<typename T>
void LinearQueue<T>::Output(ostream& os) const
{
    for (int i = front; (i % capacity) != rear; i++) {
        os << base[i] << " ";
    }
}

template<typename T>
ostream& operator<<(ostream& os, const LinearQueue<T>& obj)
{
    obj.Output(os);
    return os;
}

}}