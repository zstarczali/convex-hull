#define _USE_MATH_DEFINES
#define EPS 0.0000001
#include <iostream>
#include <math.h>
#include <cmath> // std::abs

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

using namespace std;
class LineSegment;

class Helper;

namespace Shape
{
class Point
{
  public:
    int x;
    int y;

  public:
    Point()
    {
    }
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    Point operator=(const Point &other)
    {
        if (this != &other)
        {
            this->x = other.x;
            this->y = other.y;
        }
    }
};
class Circle
{
  public:
    double x;
    double y;
    Shape::Point *p;
    double r;
    Circle(double x, double y, double r)
    {
        this->x = x;
        this->y = y;
        this->p = new Shape::Point(x, y);
        this->r = r;
    }
    ~Circle()
    {
    }
};
}

class Helper
{

  private:
  public:
    Helper()
    {
    }

    ~Helper()
    {
    }

    static double dist(double x1, double y1, double z1, double x2)
    {
        // In the case of 2d: z1 means x2 and x2 means y2
        return hypot(z1 - x1, x2 - y1);
    };

    // https://en.wikipedia.org/wiki/Hypot
    static double hypot(double x, double y)
    {
        double max = 0;
        double point[2];
        point[0] = x;
        point[1] = y;
        for (int i = 0; i < 2; i++)
        {
            double n = point[i];
            n = +n;
            n = abs(n);
            if (n > max)
                max = n;
            point[i] = n;
        }

        if (max == 0)
            max = 1;

        double sum = 0;
        double compensation = 0;

        for (int j = 0; j < 2; j++)
        {
            double m = point[j] / max;
            double summand = m * m - compensation;
            double preliminary = sum + summand;
            compensation = (preliminary - sum) - summand;
            sum = preliminary;
        }
        return sqrt(sum) * max;
    }

    bool circleLineIntersect(float x1, float y1, float x2, float y2, float cx, float cy, float cr)
    {
        float dx = x2 - x1;
        float dy = y2 - y1;
        float a = dx * dx + dy * dy;
        float b = 2 * (dx * (x1 - cx) + dy * (y1 - cy));
        float c = cx * cx + cy * cy;
        c += x1 * x1 + y1 * y1;
        c -= 2 * (cx * x1 + cy * y1);
        c -= cr * cr;
        float bb4ac = b * b - 4 * a * c;

        if (bb4ac < 0)
        {
            return false; // No collision
        }
        else
        {
            return true; //Collision
        }
    }

    // Rotates a point about a fixed point
    Shape::Point *rotatePoint(Shape::Point fp, Shape::Point pt, double a)
    {
        auto x = pt.x - fp.x;
        auto y = pt.y - fp.y;
        auto xRot = x * cos(a) + y * sin(a);
        auto yRot = y * cos(a) - x * sin(a);
        return new Shape::Point(fp.x + xRot, fp.y + yRot);
    };

    double acossafe(double x)
    {
        if (x >= +1.0)
            return 0;
        if (x <= -1.0)
            return M_PI;
        return acos(x);
    }

    /*     Shape.lineLineIntersection = function (l1, l2) {
        
          var p0 = new Shape.Point(l1.x1, l1.y1);
          var p1 = new Shape.Point(l1.x2, l1.y2);
          var p2 = new Shape.Point(l2.x1, l2.y1);
          var p3 = new Shape.Point(l2.x2, l2.y2);
        
          var s1, s2;
          s1 = {
            x: p1.x - p0.x,
            y: p1.y - p0.y
          };
          s2 = {
            x: p3.x - p2.x,
            y: p3.y - p2.y
          };
        
          var s10_x = p1.x - p0.x;
          var s10_y = p1.y - p0.y;
          var s32_x = p3.x - p2.x;
          var s32_y = p3.y - p2.y;
        
          var denom = s10_x * s32_y - s32_x * s10_y;
        
          if (denom == 0) {
            return false;
          }
        
          var denom_positive = denom > 0;
        
          var s02_x = p0.x - p2.x;
          var s02_y = p0.y - p2.y;
        
          var s_numer = s10_x * s02_y - s10_y * s02_x;
        
          if ((s_numer < 0) == denom_positive) {
            return false;
          }
        
          var t_numer = s32_x * s02_y - s32_y * s02_x;
        
          if ((t_numer < 0) == denom_positive) {
            return false;
          }
        
          if ((s_numer > denom) == denom_positive || (t_numer > denom) == denom_positive) {
            return false;
          }
        
          var t = t_numer / denom;
        
          return new Shape.Point(p0.x + (t * s10_x), p0.y + (t * s10_y));
        }*/
};

class LineSegment
{
  public:
    double x1;
    double y1;
    double x2;
    double y2;
    Shape::Point *p1;
    Shape::Point *p2;

    LineSegment(double x1, double y1, double x2, double y2)
    {
        double d = Helper::dist(x1, y1, x2, y2);
        if (d < EPS)
            cout << "A point is not a line segment" << endl;
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        this->p1 = new Shape::Point(x1, y1);
        this->p2 = new Shape::Point(x2, y2);
    }
};

class LineSegment2 : LineSegment
{
  public:
    LineSegment2(double x1, double y1, double x2, double y2)
        : LineSegment(x1, y1, x2, y2)
    {
    }
};

class Line
{
  public:
    double a;
    double b;
    double c;
    // General formula for line:
    // ax + by = c, a != 0
    // y = (c - ax)/b
    Line(double a, double b, double c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
        // Normalize
        if (abs(b) < EPS)
        {
            c /= a;
            a = 1;
            b = 0;
        }
        else
        {
            a = (abs(a) < EPS) ? 0 : a / b;
            c /= b;
            b = 1;
        }
    }
};
