//
// File: Misc.h
//
// Some commonly used functions
//
// Shining Yang <y.s.n@live.com>, 2014-10-13
//
#pragma once

namespace DSCPP { namespace Utils {

template<typename T>
void Swap(T& a, T& b)
{
    T x = a; a = b; b = x;
}

}} // namespaces