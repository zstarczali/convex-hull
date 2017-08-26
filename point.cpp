#include "point.h"

Point::Point()
{
}

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

Point Point::operator=(const Point &other)
{
    if (this != &other)
    {
        this->x = other.x;
        this->y = other.y;
    }
}