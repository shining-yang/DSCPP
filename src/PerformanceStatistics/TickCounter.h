//
// TickCounter.h
//
// 2014-08-23, Shining Yang <y.s.n@live.com>
//
#pragma once

class CTickCounter
{
public:
    CTickCounter();
    ~CTickCounter();

public:
    void Begin();
    void End();
    unsigned long GetTicks();

private:
    unsigned long m_nTickStart;
    unsigned long m_nTickStop;
};

