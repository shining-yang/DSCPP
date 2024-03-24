//
// TickCounter.cpp
//
// 2014-08-23, Shining Yang <y.s.n@live.com>
//
#include "TickCounter.h"
#include <windows.h>

CTickCounter::CTickCounter() {
  m_nTickStart = 0;
  m_nTickStart = 0;
}

CTickCounter::~CTickCounter() {}

void CTickCounter::Begin() { m_nTickStart = ::GetTickCount(); }

void CTickCounter::End() { m_nTickStop = ::GetTickCount(); }

// MUST be called after a Start/Stop call
unsigned long CTickCounter::GetTicks() { return m_nTickStop - m_nTickStart; }