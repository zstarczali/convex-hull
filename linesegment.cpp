#include "common.hpp"

#include "linesegment.hpp"
#include "helper.hpp"

using namespace std;
using Shape::Helper;

Shape::LineSegment::LineSegment(double x1, double y1, double x2, double y2)
{
    double d = Helper::dist(x1, y1, x2, y2);
    if (d < EPS)
        cout << "A point is not a line segment" << endl;
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    this->p1 = new Point(x1, y1);
    this->p2 = new Point(x2, y2);
}