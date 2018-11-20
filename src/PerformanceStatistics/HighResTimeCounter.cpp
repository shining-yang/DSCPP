//
// HighResTimeCounter.cpp
//
// 2014-08-23, Shining Yang <y.s.n@live.com>
//
#include "HighResTimeCounter.h"


CHighResTimeCounter::CHighResTimeCounter()
    : m_bInited(true),
      m_bStarted(false),
      m_bFinished(false)
{
}

CHighResTimeCounter::~CHighResTimeCounter()
{
}

void CHighResTimeCounter::Begin()
{
    if (m_bInited && !m_bStarted) {
        m_bStarted = true;
        m_bFinished = false;
        m_nCounterBegin = std::chrono::high_resolution_clock::now();
    }
}

void CHighResTimeCounter::End()
{
    if (m_bStarted) {
        m_bStarted = false;
        m_bFinished = true;
        m_nCounterEnd = std::chrono::high_resolution_clock::now();
    }
}

int CHighResTimeCounter::GetElapsedTimeInMicroseconds()
{
    if (!m_bFinished) {
        return 0;
    }
    auto span = std::chrono::duration_cast<std::chrono::microseconds>(
            m_nCounterEnd - m_nCounterBegin);
    return span.count();
}

int CHighResTimeCounter::GetElapsedTimeInMS()
{
    if (!m_bFinished) {
        return 0;
    }
    auto span = std::chrono::duration_cast<std::chrono::milliseconds>(
        m_nCounterEnd - m_nCounterBegin);
    return span.count();
}

int CHighResTimeCounter::GetElapsedTimeInSeconds()
{
    if (!m_bFinished) {
        return 0;
    }
    auto span = std::chrono::duration_cast<std::chrono::seconds>(
            m_nCounterEnd - m_nCounterBegin);
    return span.count();
}