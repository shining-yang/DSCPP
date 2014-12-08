//
// File: MaxHeap.h
// Max heap. (Max complete binary tree)
// Shining Yang <y.s.n@live.com>, 2014-12-08
//
#pragma once

#include <iostream>
#include "../Utility/Exception.h"

using namespace std;
using namespace DSCPP::Utils;

namespace DSCPP { namespace PriorityQueue {
template<typename T>
class MaxHeap {
public:
    MaxHeap(int capacity = 16);
    virtual ~MaxHeap();

public:
    bool IsEmpty() const {
        return length == 0;
    }

    bool IsFull() const {
        return length == capacity;
    }

    int Length() const {
        return length;
    }

    T Max() const;
    MaxHeap<T>& Insert(const T& e);
    MaxHeap<T>& Delete(T& e);
    void Output(ostream& os) const;

private:
    int capacity;
    int length;
    T* elements;
};

template<typename T>
MaxHeap<T>::MaxHeap(int capacity /*= 16*/)
{
    this->capacity = capacity;
    this->length = 0;
    this->elements = new T[this->capacity + 1]; // [0] will be left unused
}

template<typename T>
MaxHeap<T>::~MaxHeap()
{
    delete[] this->elements;
}

template<typename T>
T MaxHeap<T>::Max() const
{
    if (IsEmpty()) {
        throw new OutOfBounds();
    }

    return elements[1];
}

//
// Insert an element and retain structure still as a complete binary tree.
//
template<typename T>
MaxHeap<T>& MaxHeap<T>::Insert(const T& e)
{
    if (IsFull()) {
        throw new OutOfBounds();
    }

    int n = ++length;
    while ((n != 1) && (e > elements[n / 2])) {
        elements[n] = elements[n / 2];
        n /= 2;
    }

    elements[n] = e;
    return *this;
}

//
// Delete the max element while still keeping as a complete binary tree.
//
template<typename T>
MaxHeap<T>& MaxHeap<T>::Delete(T& e)
{
    if (IsEmpty()) {
        throw new OutOfBounds();
    }

    e = elements[1];

    int n = 1;
    while (n < length) {
        int i;
        T maxelem;

        if (2 * n > length) {
            break;
        }

        if (2 * n <= length) {
            maxelem = elements[2 * n];
            i = 2 * n;
        }

        if ((2 * n + 1 <= length) && (maxelem < elements[2 * n + 1])) {
            maxelem = elements[2 * n + 1];
            i = 2 * n + 1;
        }

        elements[n] = maxelem;
        n = i;
    }

    length--;
    return *this;
}

template<typename T>
void DSCPP::PriorityQueue::MaxHeap<T>::Output(ostream& os) const
{
    os << "Max heap: ";
    for (int i = 1; i <= length; i++) {
        os << elements[i] << ", ";
    }
}

template<typename T>
ostream& operator<<(ostream& os, const MaxHeap<T>& obj)
{
    obj.Output(os);
    return os;
}

}} // namespace