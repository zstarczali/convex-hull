#include "circle.hpp"

Shape::Circle::Circle(double x, double y, double r)
{
    this->x = x;
    this->y = y;
    this->p = Point(x, y);
    this->r = r;
}
Shape::Circle::~Circle()
{
}
