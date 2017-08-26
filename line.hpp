#ifndef LINE_HPP
#define LINE_HPP

#include "point.h"

using Shape::Point;

namespace Shape
{

class Line
{
  public:
    double a;
    double b;
    double c;
    // General formula for line:
    // ax + by = c, a != 0
    // y = (c - ax)/b
    Line(double a, double b, double c);
};
}
