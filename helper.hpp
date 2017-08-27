#ifndef HELPER_HPP
#define HELPER_HPP

#define _USE_MATH_DEFINES
#define EPS 0.0000001
#include <iostream>
#include <math.h>
#include <cmath> // std::abs
#include <cstddef>
#include <cstdlib>
#include <list>
#include <vector>
#include <memory>

#include "common.hpp"

#include "point.hpp"
#include "line.hpp"
#include "circle.hpp"
#include "linesegment.hpp"

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

using namespace std;
using Shape::Point;
using Shape::Line;
using Shape::Circle;

namespace Shape
{

class Helper
{

private:
public:
  Helper();
  ~Helper();

  static double dist(double x1, double y1, double z1, double x2);

  // https://en.wikipedia.org/wiki/Hypot
  static double hypot(double x, double y);

  // Rotates a point about a fixed point
  Point rotatePoint(Point fp, Point pt, double a);
  int ccw(Point a, Point b, Point c);

  double acossafe(double x);

  Line segmentToGeneralForm(double x1, double y1, double x2, double y2);
  bool pointInRectangle(Point pt, double x1, double y1, double x2, double y2);

  Point *lineLineIntersection(Shape::LineSegment l1, Shape::LineSegment l2);
  vector<Point> circleCircleIntersectionPoints(Circle c1, Circle c2);
  vector<Point> circleLineIntersection(Circle circle, Line line);
  list<Point> lineSegmentCircleIntersection(LineSegment segment, Circle circle);
};
}

#endif