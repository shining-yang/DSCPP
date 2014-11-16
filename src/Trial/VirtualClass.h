//
// File: VirtualClass.h
//
#pragma once

using namespace std;
#include <string>

class Calculator {
public:
    virtual operator int() const = 0;
    virtual double Calc(double a, double b) const = 0;
};