//
// File: VirtualClass.h
//
#pragma once

#include <string>
using namespace std;

class Calculator {
public:
    virtual operator int() const = 0;
    virtual double Calc(double a, double b) const = 0;
};
