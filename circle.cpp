#include "circle.h"

#include "point.h"

Circle::Circle(double x, double y, double r)
{
    this->x = x;
    this->y = y;
    this->p = new Point(x, y);
    this->r = r;
}
~Circle::Circle()
{
}
