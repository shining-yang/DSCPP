//
// File: SortedList.h
// Sorted linear list. [ Bin-Search: O(logN), Insert/Delete: O(n) ]
// Shining Yang <y.s.n@live.com>, 2014-11-17
//
#pragma once

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
    bool Search(const K& k, E& e) const;
    SortedList<E, K>& Insert(const E& e);
    SortedList<E, K>& Delete(const K& k, E& e);

private:
    int capacity;
    int length;
    E* elements;
};

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
    int high = length;

    while (low < high) {
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

}

template<typename E, typename K>
SortedList<E, K>& SortedList<E, K>::Delete(const K& k, E& e)
{

}

}}