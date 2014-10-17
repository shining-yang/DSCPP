//
// File: StackLinearList.h
//
// Stack implemented with linear list.
//
// 2014-10-14, Shining Yang <y.s.n@live.com>
//
#pragma once

#if 0
【Stack的效率】
当T是一个内部数据类型时，堆栈的构造函数和析构函数的复杂性均为O(1)，当Ｔ是用户
自定义的类时，构造函数和析构函数的复杂性均为O(MaxStackSize)。其余每个堆栈操作的复
杂性均为O(1)。注意通过从LinearList派生Stack，一方面大大减少了编码量，另一方面也使程
序的可靠性得到很大提高，因为LinearList经过测试并被认为是正确的。然而，不幸的是，代
码编写的简化带来了运行效率的损失。例如，为了向堆栈中添加一个元素，首先要确定堆栈的
长度length()，然后调用函数Insert()。Insert函数首先必须判断插入操作是否会越界，然后需要
付出一个for循环的开销来执行0个元素的移动。为了消除额外的开销，可以把Stack定义成一个
基类，而不是派生类。
另一种潜在的问题是派生类Stack也会受到LinearList本身所受限制的影响。例如，必须为
数据类型为T的成员定义操作符 << 和 == ，因为前者用于对线性表操作 << 的重载，后者用于对
LinearList::Search的重载。
#endif

#include "../03_LinearList/LinearList.h"
#include "../Utility/Exception.h"
using namespace DSCPP::Utils;

namespace DSCPP { namespace Stack {

template<typename T>
class Stack : private CLinearList<T> {
public:
    enum {
        DEFAULT_STACK_SIZE = 20
    };

    Stack(int c = DEFAULT_STACK_SIZE);
    ~Stack();

protected:
    Stack(const Stack<T>& s);
    Stack<T>& operator=(const Stack<T>& s);

public:
    bool IsEmpty();
    bool IsFull();
    Stack<T>& Push(const T& e);
    Stack<T>& Pop(T& e);
    T Top() const;
};

template<typename T>
DSCPP::Stack::Stack<T>::Stack(int c) : CLinearList<T>(c)
{
}

template<typename T>
DSCPP::Stack::Stack<T>::~Stack()
{
}

template<typename T>
bool Stack<T>::IsEmpty()
{
    return CLinearList<T>::IsEmpty();
}

template<typename T>
bool Stack<T>::IsFull()
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

template<typename T>
T Stack<T>::Top() const
{
    if (IsEmpty()) {
        throw new OutOfBounds();
    }

    T x;
    Find(Length() - 1, x);
    return x;
}

//==============================================================================
//= Stack2
//= not derived from linear list
//==============================================================================
template<typename T>
class Stack2 {
public:
    enum {
        DEFAULT_STACK_SIZE = 20
    };

    Stack2(int c = DEFAULT_STACK_SIZE) : capacity(c), top(-1) {
        elements = new T[c];
    }

    ~Stack2() {
        delete[] elements;
    }

protected:
    Stack2(const Stack2<T>& s);
    Stack2<T>& operator=(const Stack2<T>& s);

public:
    bool IsEmpty() const {
        return top < 0;
    }

    bool IsFull() const {
        return top >= capacity - 1;
    }

    Stack2<T>& Push(const T& x) {
        if (IsFull()) {
            throw new OutOfBounds();
        }

        elements[++top] = x;
        return *this;
    }

    Stack2<T>& Pop(T& x) {
        if (IsEmpty()) {
            throw new OutOfBounds();
        }

        x = elements[top--];
        return *this;
    }

    T Top() const {
        if (IsEmpty()) {
            throw new OutOfBounds();
        }

        return elements[top];
    }

private:
    int capacity;
    int top;
    T* elements;
};

}}