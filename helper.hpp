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
#include <stack>
#include <vector>
#include <memory>
#include <algorithm>
#include <cstdio>

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

typedef double coord_t;  // coordinate type
typedef double coord2_t; // must be big enough to hold 2*max(|coordinate|)^2

class Helper
{

public:
  Helper();
  ~Helper();

private:
  // Rotates a point about a fixed point
  Point rotatePoint(Point fp, Point pt, double a);
  double acossafe(double x);
  Line segmentToGeneralForm(double x1, double y1, double x2, double y2);
  bool pointInRectangle(Point pt, double x1, double y1, double x2, double y2);
  coord2_t cross(const Point &O, const Point &A, const Point &B);

public:
  static double dist(double x1, double y1, double z1, double x2);

  // https://en.wikipedia.org/wiki/Hypot
  static double hypot(double x, double y);

  Point *calculateLineLineIntersection(Shape::LineSegment l1, Shape::LineSegment l2);
  vector<Point> calculateCircleCircleIntersectionPoints(Circle c1, Circle c2);
  vector<Point> calculateCircleLineIntersection(Circle circle, Line line);
  vector<Point> calculateLineSegmentCircleIntersection(LineSegment segment, Circle circle);

  vector<Point> calculateConvexHull(vector<Point> P);
  double calculatePolygonArea(vector<Point> points);
};
}

#endif