#define _USE_MATH_DEFINES
#define EPS 0.0000001
#include <iostream>
#include <math.h>
#include <cmath> // std::abs
#include <cstddef>
#include <cstdlib>

#include "point.h"
#include "circle.h"
#include "linesegment.hpp"

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

using namespace std;

namespace Shape
{

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
    Point *rotatePoint(Point fp, Point pt, double a)
    {
        auto x = pt.x - fp.x;
        auto y = pt.y - fp.y;
        auto xRot = x * cos(a) + y * sin(a);
        auto yRot = y * cos(a) - x * sin(a);
        return new Point(fp.x + xRot, fp.y + yRot);
    };

    double acossafe(double x)
    {
        if (x >= +1.0)
            return 0;
        if (x <= -1.0)
            return M_PI;
        return acos(x);
    }

    Point *lineLineIntersection(Shape::LineSegment l1, Shape::LineSegment l2)
    {

        Point *p0 = new Point(l1.x1, l1.y1);
        Point *p1 = new Point(l1.x2, l1.y2);
        Point *p2 = new Point(l2.x1, l2.y1);
        Point *p3 = new Point(l2.x2, l2.y2);

        Point s1, s2;
        s1.x = p1->x - p0->x;
        s1.y = p1->y - p0->y;
        s2.x = p3->x - p2->x;
        s2.y = p3->y - p2->y;

        double s10_x = p1->x - p0->x;
        double s10_y = p1->y - p0->y;
        double s32_x = p3->x - p2->x;
        double s32_y = p3->y - p2->y;

        double denom = s10_x * s32_y - s32_x * s10_y;

        if (denom == 0)
        {
            return NULL;
        }

        bool denom_positive = denom > 0;

        double s02_x = p0->x - p2->x;
        double s02_y = p0->y - p2->y;

        double s_numer = s10_x * s02_y - s10_y * s02_x;

        if ((s_numer < 0) == denom_positive)
        {
            return NULL;
        }

        double t_numer = s32_x * s02_y - s32_y * s02_x;

        if ((t_numer < 0) == denom_positive)
        {
            return NULL;
        }

        if ((s_numer > denom) == denom_positive || (t_numer > denom) == denom_positive)
        {
            return NULL;
        }

        double t = t_numer / denom;

        return new Point(p0->x + (t * s10_x), p0->y + (t * s10_y));
    }
};
}

