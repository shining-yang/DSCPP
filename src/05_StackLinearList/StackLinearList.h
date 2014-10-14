//
// File: StackLinearList.h
//
// Stack implemented with linear list
//
#pragma once

#include "../03_LinearList/LinearList.h"
#include "../Utility/Exception.h"
using namespace DSCPP::Utils;

namespace DSCPP { namespace Stack {

template<typename T>
class Stack : private CLinearList<T> {
public:
    Stack(int c);
    ~Stack();
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
DSCPP::Stack::Stack<T>::Stack(int c = 16) : capacity(c), CLinearList<T>(c)
{
}

template<typename T>
DSCPP::Stack::Stack<T>::~Stack()
{
}

template<typename T>
T DSCPP::Stack::Stack<T>::Top(void)
{
    if (IsEmpty()) {
        throw new OutOfBounds();
    }

    T x;
    Find(Length() - 1, x);
    return x;
}

template<typename T>
void DSCPP::Stack::Stack<T>::Clear(void)
{
}

template<typename T>
bool DSCPP::Stack::Stack<T>::IsEmpty(void)
{
    return CLinearList<T>::IsEmpty();
}

template<typename T>
bool DSCPP::Stack::Stack<T>::IsFull(void)
{
    return capacity == Length();
}

template<typename T>
Stack<T>& DSCPP::Stack::Stack<T>::Push(const T& e)
{
    Insert(Length(), e);
    return *this;
}

template<typename T>
Stack<T>& Stack::Pop(T& e)
{
    Delete(Length() - 1, e);
    return *this;
}

}}