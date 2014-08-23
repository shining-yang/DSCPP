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

