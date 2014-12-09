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
    MaxHeap<T>& DeleteMax(T& e);
    void Output(ostream& os) const;
    void PrintTreeVertically(ostream& os, int width) const;

protected:
    void _PrintTreeAtLevel(ostream& os, const T* pElement, int nLevel, int nCount, int nWidth) const;

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
MaxHeap<T>& MaxHeap<T>::DeleteMax(T& e)
{
    if (IsEmpty()) {
        throw new OutOfBounds();
    }

    e = elements[1];

    T x = elements[length--]; // the last element

    // Try to find a proper position for the last element
    int n = 1; // root
    int m = 2 * n; // left child
    while (n <= length && m <= length) {
        if (m < length && elements[m] < elements[m + 1]) { // m was the bigger child
            m++;
        }

        if (elements[m] <= x) {
            break;
        }

        elements[n] = elements[m]; // shift upwards
        n = m;
        m = 2 * n;
    }

    elements[n] = x;
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

template<typename T>
void MaxHeap<T>::PrintTreeVertically(ostream& os, int width) const
{
    int nPrinted = 0;
    int nTotalLevel = 1 + static_cast<int>(log(length) / log(2));

    for (int nLevel = 0; nLevel < nTotalLevel; nLevel++) {
        int nCountAtLevel = 1 << nLevel;
        int nRemain = length - nPrinted;
        int nCount = (nRemain < nCountAtLevel) ? nRemain : nCountAtLevel;

        _PrintTreeAtLevel(os, elements + nPrinted + 1, nLevel, nCount, width);
        nPrinted += nCount;
    }
}

template<typename T>
void MaxHeap<T>::_PrintTreeAtLevel(ostream& os, const T* pElement, int nLevel, int nCount, int nWidth) const
{
    int nSegmentLen = nWidth / ((1 << nLevel) + 1);
    int nBlanks = nSegmentLen - 1; // assume that ELEMENT occupies 1 character
    for (int i = 0; i < nCount; i++) {
        for (int j = 0; j < nBlanks; j++) {
            os << " ";
        }
        os << *(pElement + i);
    }
    os << endl;
}

}} // namespace