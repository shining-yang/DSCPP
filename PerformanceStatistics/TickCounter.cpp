//
// TickCounter.cpp
//
// Shining @ 2014-08-23
//
#include "stdafx.h"
#include "TickCounter.h"


CTickCounter::CTickCounter()
{
    m_nTickStart = 0;
    m_nTickStart = 0;
}


CTickCounter::~CTickCounter()
{
}

void CTickCounter::Begin()
{
    m_nTickStart = ::GetTickCount();
}

void CTickCounter::End()
{
    m_nTickStop = ::GetTickCount();
}

// MUST be called after a Start/Stop call
unsigned long CTickCounter::GetTicks()
{
    return m_nTickStop - m_nTickStart;
}