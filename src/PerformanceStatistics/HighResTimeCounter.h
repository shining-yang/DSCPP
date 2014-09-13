//
// HighResTimeCounter.h
//
// 2014-08-23, Shining Yang <y.s.n@live.com>
//
#pragma once

#include <Windows.h>

// High resolution time counter
class CHighResTimeCounter
{
public:
    CHighResTimeCounter();
    ~CHighResTimeCounter();

public:
    void Begin();
    void End();
    unsigned long GetElapsedTimeInSeconds();
    unsigned long GetElapsedTimeInMS();
    LARGE_INTEGER GetElapsedTimeInMicroseconds();

protected:
    bool m_bInited;
    bool m_bStarted;
    bool m_bFinished;
    LARGE_INTEGER m_nFrequency;
    LARGE_INTEGER m_nCounterBegin;
    LARGE_INTEGER m_nCounterEnd;
};

