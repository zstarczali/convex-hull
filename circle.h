#include "point.h"

namespace Shape
{
class Circle
{
  public:
    double x;
    double y;
    Point *p;
    double r;
    Circle(double x, double y, double r);
    ~Circle();
};
}