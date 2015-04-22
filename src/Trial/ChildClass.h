//
// File: ChildClass.h
//
#pragma once
#include "VirtualClass.h"

class CDerived : public Calculator {
public:
    operator int() const;
    double Calc(double a, double b) const;
    int Abort();

protected:
    int pa;
};

CDerived::operator int() const
{
    return 0;
}

double CDerived::Calc(double a, double b) const
{
    return a + b;
}

int CDerived::Abort()
{
    return 2;
}
