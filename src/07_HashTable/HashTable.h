//
// File: HashTable.h
// Hash table implemented as linear open addressing using an auxiliary flag array.
// Shining Yang <y.s.n@live.com>, 2014-11-21
//
#pragma once

#include <iostream>
#include "../Utility/Exception.h"
using namespace std;
using namespace DSCPP::Utils;

namespace DSCPP { namespace Hash {

template<typename E, typename K>
class HashTable {
public:
    HashTable(int nBuckets = 16);
    virtual ~HashTable();

    bool IsFull() const {
        return _ReallyFull();
    }
    bool IsEmpty() const {
        for (int i = 0; i < divisor; i++) {
            if (!deleted[i]) {
                return false;
            }
        }
        return true;
    }
    bool Search(const K& k, E& e) const;
    HashTable<E, K>& Insert(const E& e);
    HashTable<E, K>& Delete(const K& k, E& e);
    
    template<typename Et, typename Kt>
    friend ostream& operator<<(ostream& os, const HashTable<Et, Kt>& obj);

protected:
    int _SearchHelper(const K& k) const;
    bool _ReallyFull() const;
    void _ReorganizeOnApparentFull();

private:
    bool* empty;
    E* elements;
    int divisor;
    bool* deleted; // add an array to indicate item been deleted
};


template<typename E, typename K>
HashTable<E, K>::HashTable(int nBuckets /*= 16*/)
{
    divisor = nBuckets;
    empty = new bool[nBuckets];
    elements = new E[nBuckets];
    deleted = new bool[nBuckets];
    for (int i = 0; i < nBuckets; i++) {
        empty[i] = true;
        deleted[i] = true; // initialized as true so that Insert() is allowed
    }
}

template<typename E, typename K>
HashTable<E, K>::~HashTable()
{
    delete[] empty;
    delete[] elements;
    delete[] deleted;
}

template<typename E, typename K>
bool HashTable<E, K>::Search(const K& k, E& e) const
{
    int n = _SearchHelper(k);
    if (!empty[n] && !deleted[n] && elements[n] == k) {
        e = elements[n];
        return true;
    }

    return false;
}

template<typename E, typename K>
HashTable<E, K>& HashTable<E, K>::Insert(const E& e)
{
    K k = e; // make a conversion
    bool checked = false;

_DoSearchOnceAgain:
    int n = _SearchHelper(k);
    if (empty[n]) {
        elements[n] = e;
        empty[n] = false;
        deleted[n] = false;
    } else {
        if (!deleted[n] && elements[n] == k) {
            throw new ItemAlreadyExisted();
        } else {
            if (!checked) {
                _ReorganizeOnApparentFull();
                checked = true;
                goto _DoSearchOnceAgain;
            }

            throw new ItemOverFlow();
        }
    }
    return *this;
}

template<typename E, typename K>
HashTable<E, K>& HashTable<E, K>::Delete(const K& k, E& e)
{
    int i = k % divisor;
    int n = i;

    do {
        if (!empty[n] && !deleted[n] && elements[n] == k) {
            deleted[n] = true;
            e = elements[n];
            return *this;
        }
        n = (n + 1) % divisor;
    } while (n != i);

    throw new ItemNotExisted();
}

// 返回n 号桶：
// 1) 表中有关键字值为k 的元素，empty[n]为false 且elements[n] 的关键字值为k；
// 2) 表中没有关键字值为k 的元素，empty[n]为true，则可把关键字值为k 的元素插入到n 号桶中；
// 3) 表中没有关键字值为k 的元素，empty[n]为false，empty[n]的关键字值不等于k，且表已满。
template<typename E, typename K>
int HashTable<E, K>::_SearchHelper(const K& k) const
{
    int i = k % divisor;
    int n = i;
    
    do {
        if (empty[n] || (!deleted[n] && elements[n] == k)) {
            return n;
        }
        n = (n + 1) % divisor;
    } while (n != i);

    return n;
}

template<typename E, typename K>
bool HashTable<E, K>::_ReallyFull() const
{
    for (int i = 0; i < divisor; i++) {
        if (deleted[i]) {
            return false;
        }
    }
    return true;
}

template<typename E, typename K>
void HashTable<E, K>::_ReorganizeOnApparentFull()
{
    if (_ReallyFull()) {
        return;
    }

    bool* emptytmp = empty; // save it
    empty = new bool[divisor]; // reallocate
    bool* deletedtmp = deleted; // save it
    deleted = new bool[divisor];
    for (int i = 0; i < divisor; i++) {
        empty[i] = true;
        deleted[i] = true;
    }

    E* elementstmp = elements;
    elements = new E[divisor];
    for (int i = 0; i < divisor; i++) {
        if (!deletedtmp[i]) {
            Insert(elementstmp[i]);
        }
    }

    delete[] emptytmp;
    delete[] deletedtmp;
    delete[] elementstmp;
}

template<typename E, typename K>
ostream& operator<<(ostream& os, const HashTable<E, K>& obj)
{
    for (int i = 0; i < obj.divisor; i++) {
        if (obj.deleted[i]) {
            os << "*";
        } else {
            os << obj.elements[i];
        }
        os << " ";
    }

    os << endl;
    os << "Empty flags:\t";
    for (int i = 0; i < obj.divisor; i++) {
        os << (obj.empty[i] ? "T" : "F") << " ";
    }

    os << endl;
    os << "Deleted flags:\t";
    for (int i = 0; i < obj.divisor; i++) {
        os << (obj.deleted[i] ? "T" : "F") << " ";
    }
    return os;
}

}}
