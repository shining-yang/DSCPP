//
// File: LinearList.h
// Linear list template class declaration
// Shining Yang <y.s.n@live.com>, 2014/08/29
//
#pragma once
#include <iostream>
using namespace std;
#include "../Utility/Exception.h"
using namespace DSCPP::Utils;

template<class T>
class CLinearList
{
public:
    CLinearList(int nMaxSize);
    ~CLinearList();

public:
    bool IsEmpty() const;
    int Length() const;
    bool Find(int k, T& x) const; // Get the number k element
    int Search(const T& x) const; // Get position of x
    CLinearList<T>& Delete(int k, T& x);
    CLinearList<T>& Insert(int k, const T& x);
    void Output(std::ostream& os) const;
    
private:
    int m_nMaxSize;
    int m_nLength;
    T* m_element;
};

template<class T>
CLinearList<T>::CLinearList(int nMaxSize)
{
    m_nLength = 0;
    m_nMaxSize = nMaxSize;
    m_element = new T[nMaxSize];
}

template<class T>
CLinearList<T>::~CLinearList()
{
    delete[] m_element;
}

template<class T>
bool CLinearList<T>::IsEmpty() const
{
    return m_nLength == 0;
}

template<class T>
int CLinearList<T>::Length() const
{
    return m_nLength;
}

template<class T>
bool CLinearList<T>::Find(int k, T& x) const
{
    if (k >= 0 && k < m_nLength) {
        x = m_element[k];
        return true;
    }
    return false;
}

template<class T>
int CLinearList<T>::Search(const T& x) const
{
    for (int i = 0; i < m_nLength; i++) {
        if (m_element[i] == x) {
            return i;
        }
    }
    return -1;
}

template<class T>
CLinearList<T>& CLinearList<T>::Delete(int k, T& x)
{
    if (!Find(k, x)) {
        throw OutOfBounds();
    }

    for (int i = k; i < m_nLength - 1; i++) {
        m_element[i] = m_element[i + 1];
    }
    m_nLength--;
    return *this;
}

template<class T>
CLinearList<T>& CLinearList<T>::Insert(int k, const T& x)
{
    if (k < 0 || k > m_nLength) {
        throw OutOfBounds();
    }

    if (m_nLength >= m_nMaxSize) {
        throw OutOfBounds();
    }

    for (int i = m_nLength - 1; i >= k; i--) {
        m_element[i + 1] = m_element[i];
    }
    m_element[k] = x;
    m_nLength++;
    return *this;
}

template<class T>
void CLinearList<T>::Output(std::ostream& os) const
{
    for (int i = 0; i < m_nLength; i++) {
        os << m_element[i] << " ";
    }
}
