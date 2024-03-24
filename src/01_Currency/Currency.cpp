//
// Currency.cpp
//
// 2014/8/26, Shining Yang <y.s.n@live.com>
//
#include "Currency.h"

std::ostream &operator<<(std::ostream &os, const CCurrency &c) {
#if 0 // NO need to be a friend function
  if (c.Sign() == MINUS) { os << "-"; }
  os << "$";
  os << c.Dollars();
  os << ".";
  if (c.Cents() < 10) {
    os << "0" << c.Cents();
  } else {
    os << c.Cents();
  }
#else
  long amount = c.m_nAmount; // access private member of class
  if (amount < 0) {
    os << "-";
    amount = -amount;
  }

  long dollars = amount / 100;
  long cents = amount - dollars * 100;
  os << "$";
  os << dollars;
  os << ".";
  if (cents < 10) {
    os << "0" << cents;
  } else {
    os << cents;
  }
#endif
  return os;
}

// NO CHECKS ON INPUT
// Valid inputs must contain: +/-, $, dollars, dot, cents
// Example: +$14.99, -$3.75
std::istream &operator>>(std::istream &is, CCurrency &c) {
  SIGN sign = PLUS;
  long dollars = 0;
  long cents = 0;

  char ch;
  is >> ch;
  switch (ch) {
  case '+':
    sign = PLUS;
    break;
  case '-':
    sign = MINUS;
    break;
  }

  is >> ch; // '$'
  is >> dollars;
  is >> ch; // '.'
  is >> cents;

  c.Set(dollars, cents, sign);
  return is;
}

CCurrency::CCurrency(unsigned long d /*= 0*/, unsigned long c /*= 0*/,
                     SIGN s /*= PLUS*/) {
  if (c > 99) {
    throw new CBadInitializer();
  }
  m_nAmount = d * 100 + c;
  if (s == MINUS) {
    m_nAmount = -m_nAmount;
  }
}

CCurrency::CCurrency(float c) { Set(c); }

CCurrency::~CCurrency() {}

bool CCurrency::Set(unsigned long d, unsigned long c, SIGN s) {
  if (c > 99) {
    return false;
  }
  m_nAmount = d * 100 + c;
  if (s == MINUS) {
    m_nAmount = -m_nAmount;
  }
  return true;
}

bool CCurrency::Set(float c) {
  SIGN s = PLUS;
  if (c < 0) {
    c = -c;
    s = MINUS;
  }

  m_nAmount = static_cast<long>((c + 0.001) * 100); // rounded it
  if (s == MINUS) {
    m_nAmount = -m_nAmount;
  }
  return true;
}

SIGN CCurrency::Sign() const { return m_nAmount > 0 ? PLUS : MINUS; }

unsigned long CCurrency::Dollars() const {
  if (m_nAmount > 0) {
    return m_nAmount / 100;
  } else {
    return -m_nAmount / 100;
  }
}

unsigned long CCurrency::Cents() const {
  if (m_nAmount > 0) {
    return m_nAmount % 100;
  } else {
    return -m_nAmount % 100;
  }
}

CCurrency CCurrency::operator+(const CCurrency &c) const {
  CCurrency t;
  t.m_nAmount = this->m_nAmount + c.m_nAmount;
  return t;
}

CCurrency CCurrency::operator-(const CCurrency &c) const {
  CCurrency t;
  t.m_nAmount = this->m_nAmount - c.m_nAmount;
  return t;
}

CCurrency &CCurrency::operator+=(const CCurrency &c) {
  this->m_nAmount += c.m_nAmount;
  return *this;
}

CCurrency &CCurrency::operator-=(const CCurrency &c) {
  this->m_nAmount -= c.m_nAmount;
  return *this;
}

CCurrency CCurrency::operator*(float x) const {
  CCurrency t;
  t.m_nAmount = static_cast<long>(this->m_nAmount * x);
  return t;
}

CCurrency CCurrency::operator/(float x) const {
  CCurrency t;
  t.m_nAmount = static_cast<long>(this->m_nAmount / x);
  return t;
}

CCurrency CCurrency::operator%(float x) const { // not modular but percentage
  CCurrency t;
  t.m_nAmount = static_cast<long>(this->m_nAmount * x / 100);
  return t;
}
