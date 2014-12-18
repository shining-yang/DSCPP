//
// File: StackLinkedList.h
//
// Stack implemented as linked list.
//
// Shining Yang <y.s.n@live.com>, 2014-10-16
//
#pragma once
#include "../03_SinglyLinkedList/SinglyLinkedList.h"

namespace DSCPP { namespace Stack {

template<typename T>
class StackLinkedList : private Chain<T> {
public:
    bool IsEmpty() const {
        return Chain<T>::IsEmpty();
    }

    bool IsFull() const {
        ChainNode<T>* p = new ChainNode<T>();
        if (p != NULL) {
            delete p;
            return false;
        } else {
            return true;
        }
    }

    StackLinkedList<T>& Push(const T& x) { // internal call will throw exception if there are any
        Insert(0, x);
        return *this;
    }

    StackLinkedList<T>& Pop(T& x) { // internal call will throw exception if there are any
        Delete(0, x);
        return *this;
    }

    T Top() const {
        if (IsEmpty()) {
            throw new OutOfBounds();
        }

        T x;
        Find(0, x);
        return x;
    }
};

}}