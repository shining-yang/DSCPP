//
// File: StackLinearList.h
//
// Stack implemented with linear list.
//
// 2014-10-14, Shining Yang <y.s.n@live.com>
//
#pragma once

#include "../03_LinearList/LinearList.h"
#include "../Utility/Exception.h"
using namespace DSCPP::Utils;

namespace DSCPP { namespace Stack {

template<typename T>
class Stack : private CLinearList<T> {
public:
    Stack(int c = 16);
    ~Stack();

protected:
    Stack(const Stack<T>& s);
    Stack<T>& operator=(const Stack<T>& s);

public:
    T Top(void);
    void Clear(void);
    bool IsEmpty(void);
    bool IsFull(void);
    Stack<T>& Push(const T& e);
    Stack<T>& Pop(T& e);

private:
    int capacity;
};

template<typename T>
DSCPP::Stack::Stack<T>::Stack(int c/* = 16*/) : capacity(c), CLinearList<T>(c)
{
}

template<typename T>
DSCPP::Stack::Stack<T>::~Stack()
{
}

template<typename T>
T Stack<T>::Top(void)
{
    if (IsEmpty()) {
        throw new OutOfBounds();
    }

    T x;
    Find(Length() - 1, x);
    return x;
}

template<typename T>
void Stack<T>::Clear(void)
{
}

template<typename T>
bool Stack<T>::IsEmpty(void)
{
    return CLinearList<T>::IsEmpty();
}

template<typename T>
bool Stack<T>::IsFull(void)
{
    return GetMaxSize() == Length();
}

template<typename T>
Stack<T>& Stack<T>::Push(const T& e)
{
    Insert(Length(), e);
    return *this;
}

template<typename T>
Stack<T>& Stack<T>::Pop(T& e)
{
    Delete(Length() - 1, e);
    return *this;
}

}}