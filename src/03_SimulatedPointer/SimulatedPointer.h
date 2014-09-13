//
// File: SimulatedPointer.h
//
// 模拟指针
//
// 2014/9/5, Shining Yang <y.s.n@live.com>
//
#pragma once

#include <iostream>
using namespace std;

class OutOfBounds
{
};

class NoMem
{
};

template<class T> class SimNode;
template<class T> class SimSpace;
template<class T> class SimChain;

template<class T>
class SimNode
{
    friend class SimSpace < T > ;
    friend class SimChain < T > ;
private:
    T data;
    int link;
};

//------------------------------------------------------------------------------
// SimSpace NOTES:
// 使用两个变量的方法，其效率会高些。因为它的构造函数不需要对分配的存储进行初始化。
// 而两种方法的Allocate/Deallocate都是一样代码，（Allocate稍有区别，但比起前者的
// 构造函数初始化而言，其效率通常要高些）
//------------------------------------------------------------------------------

#if 0
//
// 使用一个变量（first）指示可用空间表
//
template<class T>
class SimSpace
{
    friend class SimChain < T > ;

public:
    SimSpace(int nSize = 100);
    ~SimSpace();

public:
    int Allocate();
    void Deallocate(int& i);

private:
    int num;
    int first;
    SimNode<T>* node;
};

template<class T>
SimSpace<T>::SimSpace(int nSize /*= 100*/)
{
    node = new SimNode<T>[nSize];
    for (int i = 0; i < nSize - 1; i++) {
        node[i].link = ++i;
    }
    node[nSize - 1] = -1;
    num = nSize;
    first = 0;
}

template<class T>
SimSpace<T>::~SimSpace()
{
    delete[] node;
}

template<class T>
int SimSpace<T>::Allocate()
{
    if (first == num) {
        throw new NoMem();
    }

    int i = first;
    first = node[first].link;
    return i;
}

template<class T>
void SimSpace<T>::Deallocate(int& i)
{
    if (i < 0 || i > num - 1) {
        throw new OutOfBounds();
    }

    node[i].link = first;
    first = i;
    i = -1;
}
#else
//
// 使用两个变量（first1, first2）指示可用空间表
//
template<class T>
class SimSpace
{
    friend class SimChain < T > ;

public:
    SimSpace(int nSize = 100);
    ~SimSpace();

public:
    int Allocate();
    void Deallocate(int& i);

private:
    int num;
    int first1, first2;
    SimNode<T>* node;
};

template<class T>
SimSpace<T>::SimSpace(int nSize /*= 100*/)
{
    node = new SimNode<T>[nSize];
    num = nSize;
    first1 = 0;
    first2 = -1;
}

template<class T>
SimSpace<T>::~SimSpace()
{
    delete[] node;
}

template<class T>
int SimSpace<T>::Allocate()
{
    if (first2 == -1) {
        if (first1 == num) {
            throw new NoMem();
        }
        return first1++;
    }

    int i = first2;
    first2 = node[first2].link;
    return i;
}

template<class T>
void SimSpace<T>::Deallocate(int& i)
{
    if (i < 0 || i > num - 1) {
        throw new OutOfBounds();
    }

    node[i].link = first2;
    first2 = i;
    i = -1;
}
#endif

//
// SimChain
//
template<class T>
class SimChain {
public:
    SimChain() { first = -1; }
    ~SimChain() { Destroy(); }
    void Destroy(); // 使表为空
    int Length() const;
    bool Find(int k, T& x) const;
    int Search(const T& x) const;
    SimChain<T>& Delete(int k, T& x);
    SimChain<T>& Insert(int k, const T& x);
    void Output(ostream& out) const;

private:
    int first; // 第一个节点的索引
    static SimSpace<T> S;
};

// static member shared by all SimChain instances
template<class T> SimSpace<T> SimChain<T>::S;

template<class T>
void SimChain<T>::Destroy()
{
    int next;
    while (first != -1) {
        next = S.node[first].link;
        S.Deallocate(first);
        first = next;
    }
}

template<class T>
int SimChain<T>::Length() const
{
    int n = 0;
    for (int i = first; i != -1; i = S.node[i].link) {
        n++;
    }
    return n;
}

// 0-based index
template<class T>
bool SimChain<T>::Find(int k, T& x) const
{
    if (k < 0) {
        return false;
    }

    for (int i = first; i != -1; i = S.node[i].link) {
        if (k-- == 0) {
            x = S.node[i].data;
            return true;
        }
    }
    return false;
}

// 0-based index
template<class T>
int SimChain<T>::Search(const T& x) const
{
    int n = -1;
    for (int i = first; i != -1; i = S.node[i].link) {
        n++;
        if (S.node[i].data == x) {
            return n;
        }
    }
    return -1;
}

// 0-based index
template<class T>
SimChain<T>& SimChain<T>::Delete(int k, T& x)
{
    if (k < 0) {
        throw new OutOfBounds();
    }
    
    int i = first; // node to be deleted
    if (k == 0) {
        first = S.node[first].link;
    } else {
        int j; // previous node
        while (i != -1 && k-- > 0) {
            j = i;
            i = S.node[i].link;
        }

        if (i == -1) {
            throw new OutOfBounds();
        }

        S.node[j].link = S.node[i].link;
    }

    x = S.node[i].data;
    S.Deallocate(i);
    return *this;
}

// 0-based index
template<class T>
SimChain<T>& SimChain<T>::Insert(int k, const T& x)
{
    if (k < 0) {
        throw new OutOfBounds();
    }

    int y = S.Allocate();
    S.node[y].data = x;

    if (k == 0) {
        S.node[y].link = first;
        first = y;
    } else {
        int i = first; // position to be inserted
        int j; // previous node
        while (i != -1 && k-- > 0) {
            j = i;
            i = S.node[i].link;
        }

        if (i == -1) {
            if (k == 0) { // allow insertion at tail
                // let it go
            } else {
                throw new OutOfBounds();
            }
        }

        S.node[y].link = i;
        S.node[j].link = y;
    }

    return *this;
}

template<class T>
void SimChain<T>::Output(ostream& os) const
{
    for (int i = first; i != -1; i = S.node[i].link) {
        os << S.node[i].data << " ";
    }
}

template<class T>
ostream& operator<<(std::ostream& os, const SimChain<T>& c)
{
    c.Output(os);
    return os;
}
