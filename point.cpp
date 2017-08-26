#include "point.hpp"

Shape::Point::Point()
{
}

Shape::Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

Shape::Point Shape::Point::operator=(const Shape::Point &other)
{
    if (this != &other)
    {
        this->x = other.x;
        this->y = other.y;
    }
}