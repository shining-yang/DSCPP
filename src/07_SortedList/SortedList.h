//
// File: SortedList.h
// Sorted linear list. [ Bin-Search: O(logN), Insert/Delete: O(n) ]
// Shining Yang <y.s.n@live.com>, 2014-11-17
//
#pragma once

#include <iostream>
using namespace std;

#include "..\Utility\Exception.h"
using namespace DSCPP::Utils;

namespace DSCPP { namespace SortedLinearList {

template<typename E, typename K>
class SortedList {
public:
    SortedList(int capacity = 16);
    ~SortedList();

    int Length() const;
    bool IsEmpty() const;
    bool IsFull() const;
    void Clear();
    bool Search(const K& k, E& e) const;
    SortedList<E, K>& Insert(const E& e);
    SortedList<E, K>& Delete(const K& k, E& e);

    template<typename E, typename K>
    friend std::ostream&  operator<<(std::ostream& os, const SortedList<E, K>& sl);

protected:
    int _Locate(const K& k) const;
    void _MoveExpand(int pos);
    void _MoveShrive(int pos);
    void _TryToInflate();
    void _TryToDeflate();

private:
    int capacity;
    int length;
    E* elements;
};

template<typename E, typename K>
void SortedList<E, K>::Clear()
{
    length = 0;
}

template<typename E, typename K>
int SortedList<E, K>::_Locate(const K& k) const
{
    int lo = 0;
    int mid = -1;
    int hi = length - 1;
    while (lo <= hi) {
        mid = (lo + hi) >> 1;
        if (elements[mid] == k) {
            return mid;
        } else if (elements[mid] < k) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return mid;
}

template<typename E, typename K>
void SortedList<E, K>::_MoveExpand(int pos)
{
    for (int i = length - 1; i >= pos; i--) {
        elements[i + 1] = elements[i];
    }
}

template<typename E, typename K>
void SortedList<E, K>::_MoveShrive(int pos)
{
    for (int i = pos; i < length - 1; i++) {
        elements[i] = elements[i + 1];
    }
}

template<typename E, typename K>
void SortedList<E, K>::_TryToInflate()
{
    int n = capacity;
    if (n < 1024) {
        n <<= 1; // make double
    } else {
        n += 1024;
    }

    E* pe = new E[n]; // throw exception when failed to allocate memory
    for (int i = 0; i < length; i++) {
        pe[i] = elements[i]; // Copy-constructor needed
    }

    delete[] elements;
    elements = pe;
    capacity = n;
}

template<typename E, typename K>
void SortedList<E, K>::_TryToDeflate()
{
    int n = capacity;
    if (n > 32) {
        if ((length << 2) < n) { // 4-times
            n >>= 1; // make half

            E* pe = new E[n]; // throw exception when failed to allocate memory
            for (int i = 0; i < length; i++) {
                pe[i] = elements[i]; // Copy-constructor needed
            }

            delete[] elements;
            elements = pe;
            capacity = n;
        }
    }
}

template<typename E, typename K>
SortedList<E, K>::SortedList(int capacity /*= 16*/)
{
    if (capacity <= 0) {
        throw new BadInitializer;
    }

    this->length = 0;
    this->capacity = capacity;
    this->elements = new E[capacity];
}

template<typename E, typename K>
SortedList<E, K>::~SortedList()
{
    delete[] elements;
}

template<typename E, typename K>
int SortedList<E, K>::Length() const
{
    return length;
}

template<typename E, typename K>
bool SortedList<E, K>::IsEmpty() const
{
    return length <= 0;
}

template<typename E, typename K>
bool SortedList<E, K>::IsFull() const
{
    return length >= capacity;
}

template<typename E, typename K>
bool SortedList<E, K>::Search(const K& k, E& e) const
{
    int low = 0;
    int high = length - 1;

    while (low <= high) {
        int mid = (high + low) / 2;
        if (elements[mid] == k) {
            e = elements[mid];
            return true;
        } else if (elements[mid] < k) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return false;
}

template<typename E, typename K>
SortedList<E, K>& SortedList<E, K>::Insert(const E& e)
{
    if (length >= capacity) {
        _TryToInflate();
    }

    K k = e;
    int pos = _Locate(k);
    if (pos == -1) {
        elements[length++] = e;
    } else {
        if (elements[pos] == k) {
            throw new ItemAlreadyExisted();
        }
        
        if (elements[pos] < k) {
            pos++;
        }
        
        _MoveExpand(pos);
        elements[pos] = e;
        length++;
    }

    return *this;
}

template<typename E, typename K>
SortedList<E, K>& SortedList<E, K>::Delete(const K& k, E& e)
{
    if (IsEmpty()) {
        throw new OutOfRange;
    }

    int pos = _Locate(k);
    if (elements[pos] == k) {
        e = elements[pos];
        _MoveShrive(pos);
        length--;
    } else {
        throw new ItemNotExisted();
    }

    _TryToDeflate();
    return *this;
}

template<typename E, typename K>
std::ostream& operator<<(std::ostream& os, const SortedList<E, K>& sl)
{
    os << "Contains " << sl.length << " element(s): ";
    for (int i = 0; i < sl.length; i++) {
        os << sl.elements[i] << " ";
    }

    return os;
}

}}