//
// Currency.h
//
// 2014/8/26, Shining Yang <y.s.n@live.com>
//
#pragma once

#include <iostream>

typedef enum { PLUS, MINUS } SIGN;

// Exception on initialization
class CBadInitializer {
public:
  CBadInitializer() {}
};

// US Currency (sign, dollar, cent)
class CCurrency {
  friend std::ostream &operator<<(std::ostream &os, const CCurrency &c);
  friend std::istream &operator>>(std::istream &is, CCurrency &c);

public:
  CCurrency(float c);
  CCurrency(unsigned long d = 0, unsigned long c = 0, SIGN s = PLUS);
  ~CCurrency();

public:
  bool Set(float c);
  bool Set(unsigned long d, unsigned long c, SIGN s);
  SIGN Sign() const;
  unsigned long Dollars() const;
  unsigned long Cents() const;
  CCurrency operator+(const CCurrency &c) const;
  CCurrency operator-(const CCurrency &c) const;
  CCurrency &operator+=(const CCurrency &c);
  CCurrency &operator-=(const CCurrency &c);
  CCurrency operator*(float x) const;
  CCurrency operator/(float x) const;
  CCurrency operator%(float x) const; // not modular but percentage

protected:
  long m_nAmount;
};
