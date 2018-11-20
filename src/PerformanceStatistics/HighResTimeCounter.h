//
// HighResTimeCounter.h
//
// 2014-08-23, Shining Yang <y.s.n@live.com>
// 2018-11-20, Shining Yang <y.s.n@live.com>, minor update for better portability with c++11 chrono
//
#pragma once

#include <chrono>

class CHighResTimeCounter
{
public:
    CHighResTimeCounter();
    ~CHighResTimeCounter();

public:
    void Begin();
    void End();
    int GetElapsedTimeInSeconds();
    int GetElapsedTimeInMS();
    int GetElapsedTimeInMicroseconds();

protected:
    bool m_bInited;
    bool m_bStarted;
    bool m_bFinished;
    std::chrono::high_resolution_clock::time_point m_nCounterBegin;
    std::chrono::high_resolution_clock::time_point m_nCounterEnd;
};

