#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "point.h"

using Shape::Point;

namespace Shape
{
class Circle
{
  public:
    double x;
    double y;
    Point *p;
    double r;
    Circle(double x, double y, double r);
    ~Circle();
};
}

#endif