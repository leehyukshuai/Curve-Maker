#include "fraction.h"

double Fraction::value()
{
    return v;
}

std::istream &operator>>(std::istream &stream, Fraction &f)
{
    stream >> f.v;
    while (stream.peek() == ' ')
        stream.get();
    if (stream.peek() == '/')
    {
        stream.get();
        double t;
        stream >> t;
        f.v /= t;
    }
    return stream;
}