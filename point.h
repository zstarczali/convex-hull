#ifndef POINT_HPP
#define POINT_HPP


namespace Shape
{

class Point
{
  public:
    int x;
    int y;

  public:
    Point();
    Point(int x, int y);
    Point operator=(const Point &other);
};
}

#endif