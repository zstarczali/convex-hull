#ifndef LINESEGMENT_HPP
#define LINESEGMENT_HPP

#include "point.hpp"

using Shape::Point;

namespace Shape
{
class LineSegment
{
  public:
    double x1;
    double y1;
    double x2;
    double y2;
    Point *p1;
    Point *p2;

    LineSegment(double x1, double y1, double x2, double y2);
};
}

#endif