#ifndef _FRACTION_H_
#define _FRACTION_H_
#include <iostream>

class Fraction
{
private:
    double v;
public:
    double value();
    friend std::istream &operator>>(std::istream &stream, Fraction &f);
};

#endif