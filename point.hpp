#define _USE_MATH_DEFINES
#define EPS 0.0000001

#ifndef POINT_HPP
#define POINT_HPP

#include <stack>

using namespace std;

namespace Shape
{
class Point
{
public:
  double x;
  double y;
  // Point having the least y coordinate, used for sorting other points
  // according to polar angle about this point

public:
  Point();
  ~Point();
  Point(double x, double y);

  void set_x(double x);
  void set_y(double y);
  double get_x();
  double get_y();

  Point operator=(const Point &other);
  bool operator==(const Point &other) const;

  bool operator<(Point b);
};
}

#endif