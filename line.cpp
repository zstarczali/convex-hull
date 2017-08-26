#include "common.hpp"

#include "point.hpp"
#include "line.hpp"

Shape::Line::Line(double a, double b, double c)
{
    this->a = a;
    this->b = b;
    this->c = c;
    // Normalize
    if (abs(b) < EPS)
    {
        c /= a;
        a = 1;
        b = 0;
    }
    else
    {
        a = (abs(a) < EPS) ? 0 : a / b;
        c /= b;
        b = 1;
    }
}