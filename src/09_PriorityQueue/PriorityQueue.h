//
// File: PriorityQueue.h
// Priority queue implemented using LinearList. [ Sequential search: O(n) ]
// Shining Yang <y.s.n@live.com>, 2014-12-05
//
#pragma once

#include "../03_LinearList/LinearList.h"

namespace DSCPP { namespace PriorityQueue {

template<typename T, typename P>
class PriorityQueue {
public:
    PriorityQueue(int capacity = 16);
    ~PriorityQueue();

    int Length() const;
    T Max() const;
    PriorityQueue<T, P>& EnQueue(const T& e);
    PriorityQueue<T, P>& DeQueue(T& e);

private:
    struct PQS {
        PQS() {}
        PQS(const T& e, const P& p) : data(e), priority(p) {}
        T data;
        P priority;
    };
    LinearList<PQS> linear;
};

template<typename T, typename P>
PriorityQueue<T, P>::PriorityQueue(int capacity /*= 16*/)
    : linear(capacity)
{
}

template<typename T, typename P>
PriorityQueue<T, P>::~PriorityQueue()
{
}

template<typename T, typename P>
int PriorityQueue<T, P>::Length() const
{
    return this->linear.Length();
}

template<typename T, typename P>
T PriorityQueue<T, P>::Max() const
{
    if (this->linear.Length() <= 0) {
        throw new ItemUnderFlow();
    }

    PQS t;
    this->linear.Find(0, t);

    for (int i = 1; i < this->linear.Length(); i++) {
        PQS tmp;
        this->linear.Find(i, tmp);
        if (P(t.priority) < P(tmp.priority)) {
            t = tmp;
        }
    }

    return t.data;
}

template<typename T, typename P>
PriorityQueue<T, P>& PriorityQueue<T, P>::EnQueue(const T& e)
{
    P p = e; // make a conversion implicitly
    this->linear.Insert(this->linear.Length(), PQS(e, p));
    return *this;
}

template<typename T, typename P>
PriorityQueue<T, P>& PriorityQueue<T, P>::DeQueue(T& e)
{
    if (this->linear.Length() <= 0) {
        throw new ItemUnderFlow();
    }

    PQS t;
    this->linear.Find(0, t);

    int maxpos = 0;
    for (int i = 1; i < this->linear.Length(); i++) {
        PQS tmp;
        this->linear.Find(i, tmp);
        if (P(t.priority) < P(tmp.priority)) {
            maxpos = i;
        }
    }

    this->linear.Delete(maxpos, t);
    e = t.data;
    return *this;
}

}}
