#include "helper.hpp"
#include <algorithm> // std::sort

using Shape::Point;
using Shape::Helper;

Helper::Helper()
{
}
Helper::~Helper()
{
}

double Helper::dist(double x1, double y1, double z1, double x2)
{
    // In the case of 2d: z1 means x2 and x2 means y2
    return hypot(z1 - x1, x2 - y1);
};

// https://en.wikipedia.org/wiki/Hypot
// Hypot is a mathematical function defined to calculate the length
// of the hypotenuse of a right-angle triangle.
// It was designed to avoid errors arising due to
// limited-precision calculations performed on computers.
double Helper::hypot(double x, double y)
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

// Rotates a point about a fixed point
Point Helper::rotatePoint(Point fp, Point pt, double a)
{
    auto x = pt.x - fp.x;
    auto y = pt.y - fp.y;
    auto xRot = x * cos(a) + y * sin(a);
    auto yRot = y * cos(a) - x * sin(a);
    return Point(fp.x + xRot, fp.y + yRot);
}

double Helper::acossafe(double x)
{
    if (x >= +1.0)
        return 0;
    if (x <= -1.0)
        return M_PI;
    return acos(x);
}

Point *Helper::calculateLineLineIntersection(LineSegment l1, LineSegment l2)
{
    unique_ptr<Point> p0(new Point(l1.x1, l1.y1));
    unique_ptr<Point> p1(new Point(l1.x2, l1.y2));
    unique_ptr<Point> p2(new Point(l2.x1, l2.y1));
    unique_ptr<Point> p3(new Point(l2.x2, l2.y2));

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

vector<Point> Helper::calculateCircleCircleIntersectionPoints(Circle c1, Circle c2)
{
    vector<Point> ret;

    double r, R, d, cx, cy, Cx, Cy;
    if (c1.r < c2.r)
    {
        r = c1.r;
        R = c2.r;
        cx = c1.x;
        cy = c1.y;
        Cx = c2.x;
        Cy = c2.y;
    }
    else
    {
        r = c2.r;
        R = c1.r;
        Cx = c1.x;
        Cy = c1.y;
        cx = c2.x;
        cy = c2.y;
    }

    // Find the distance between two points.
    d = dist(cx, cy, Cx, Cy);

    // There are an infinite number of solutions
    // Seems appropriate to also return null
    if (d < EPS && abs(R - r) < EPS)
        return ret;

    // No intersection (circles centered at the
    // same place with different size)
    else if (d < EPS)
        return ret;

    double vx = cx - Cx,
           vy = cy - Cy;
    double x = (vx / d) * R + Cx,
           y = (vy / d) * R + Cy;
    Point P(x, y);

    // Single intersection (kissing circles)
    if (abs((R + r) - d) < EPS || abs(R - (r + d)) < EPS)
    {
        ret.push_back(P);
        return ret;
    }
    // No intersection. Either the small circle contained within
    // big circle or circles are simply disjoint.
    if ((d + r) < R || (R + r < d))
        return ret;

    Point C(Cx, Cy);
    double angle = acossafe((r * r - d * d - R * R) / (-2.0 * d * R));
    Point pt1 = rotatePoint(C, P, +angle);
    Point pt2 = rotatePoint(C, P, -angle);
    ret.push_back(pt1);
    ret.push_back(pt2);

    return ret;
};

vector<Point> Helper::calculateCircleLineIntersection(Circle circle, Line line)
{
    vector<Point> ret; // empty list

    double a = line.a,
           b = line.b,
           c = line.c;
    double x = circle.x,
           y = circle.y,
           r = circle.r;

    // Solve for the variable x with the formulas: ax + by = c (equation of line)
    // and (x-X)^2 + (y-Y)^2 = r^2 (equation of circle where X,Y are known) and expand to obtain quadratic:
    // (a^2 + b^2)x^2 + (2abY - 2ac + - 2b^2X)x + (b^2X^2 + b^2Y^2 - 2bcY + c^2 - b^2r^2) = 0
    // Then use quadratic formula X = (-b +- sqrt(a^2 - 4ac))/2a to find the
    // roots of the equation (if they exist) and this will tell us the intersection points

    // In general a quadratic is written as: Ax^2 + Bx + C = 0
    // (a^2 + b^2)x^2 + (2abY - 2ac + - 2b^2X)x + (b^2X^2 + b^2Y^2 - 2bcY + c^2 - b^2r^2) = 0
    double A = a * a + b * b;
    double B = 2 * a * b * y - 2 * a * c - 2 * b * b * x;
    double C = b * b * x * x + b * b * y * y - 2 * b * c * y + c * c - b * b * r * r;

    // Use quadratic formula x = (-b +- sqrt(a^2 - 4ac))/2a to find the
    // roots of the equation (if they exist).

    double D = B * B - 4 * A * C;
    double x1, y1, x2, y2;

    // Handle vertical line case with b = 0
    if (abs(b) < EPS)
    {
        // Line equation is ax + by = c, but b = 0, so x = c/a
        x1 = c / a;

        // No intersection
        if (abs(x - x1) > r)
            return ret;

        // Vertical line is tangent to circle
        if (abs((x1 - r) - x) < EPS || abs((x1 + r) - x) < EPS)
        {
            Point pt(x1, y);
            ret.push_back(pt);
            return ret;
        }

        double dx = abs(x1 - x);
        double dy = sqrt(r * r - dx * dx);

        // Vertical line cuts through circle
        Point pt(x1, y + dy);
        ret.push_back(pt);
        pt.set_x(x1);
        pt.set_y(y - dy);
        ret.push_back(pt);
        return ret;

        // Line is tangent to circle
    }
    else if (abs(D) < EPS)
    {

        x1 = -B / (2 * A);
        y1 = (c - a * x1) / b;

        Point pt(x1, y1);

        ret.push_back(pt);
        return ret;

        // No intersection
    }
    else if (D < 0)
    {
        return ret;
    }
    else
    {
        D = sqrt(D);

        x1 = (-B + D) / (2 * A);
        y1 = (c - a * x1) / b;

        x2 = (-B - D) / (2 * A);
        y2 = (c - a * x2) / b;

        Point pt(x1, y1);
        ret.push_back(pt);
        pt.x = x2;
        pt.y = y2;
        ret.push_back(pt);
        return ret;
    }
};

Line Helper::segmentToGeneralForm(double x1, double y1, double x2, double y2)
{
    double a = y1 - y2;
    double b = x2 - x1;
    double c = x2 * y1 - x1 * y2;
    return Line(a, b, c);
};

// (x1,y1) is a top left corner, (x2,y2) is a bottom right corner
bool Helper::pointInRectangle(Point pt, double x1, double y1, double x2, double y2)
{
    double x = min(x1, x2),
           X = max(x1, x2);
    double y = min(y1, y2),
           Y = max(y1, y2);
    return x - EPS <= pt.x && pt.x <= X + EPS &&
           y - EPS <= pt.y && pt.y <= Y + EPS;
};

vector<Point> Helper::calculateLineSegmentCircleIntersection(LineSegment segment, Circle circle)
{
    vector<Point> ret; // empty list

    double x1 = segment.x1,
           y1 = segment.y1,
           x2 = segment.x2,
           y2 = segment.y2;
    Line line = segmentToGeneralForm(x1, y1, x2, y2);

    vector<Point> pts = calculateCircleLineIntersection(circle, line);

    // No intersection
    if (pts.size() == 0)
        return ret;

    Point pt1 = pts[0];
    bool includePt1 = pointInRectangle(pt1, x1, y1, x2, y2);

    if (pts.size() == 1)
    {
        if (includePt1)
        {
            ret.push_back(pt1);
            return ret;
        }
        return ret;
    }

    Point pt2 = pts[1];
    bool includePt2 = pointInRectangle(pt2, x1, y1, x2, y2);

    if (includePt1 && includePt2)
    {
        ret.push_back(pt1);
        ret.push_back(pt2);
        return ret;
    }
    if (includePt1)
    {
        ret.push_back(pt1);
        return ret;
    }
    if (includePt2)
    {
        ret.push_back(pt2);
        return ret;
    }
    return ret;
};

// 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross product.
// Returns a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.
Shape::coord2_t Helper::cross(const Point &O, const Point &A, const Point &B)
{
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is the same as the first one.
vector<Point> Helper::calculateConvexHull(vector<Point> P)
{
    int n = P.size(), k = 0;
    if (n == 1)
        return P;
    vector<Point> H(2 * n);

    // Sort points lexicographically
    sort(P.begin(), P.end());

    // Build lower hull
    for (int i = 0; i < n; ++i)
    {
        while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) <= 0)
            k--;
        H[k++] = P[i];
    }

    // Build upper hull
    for (int i = n - 2, t = k + 1; i >= 0; i--)
    {
        while (k >= t && cross(H[k - 2], H[k - 1], P[i]) <= 0)
            k--;
        H[k++] = P[i];
    }

    H.resize(k - 1);
    return H;
}

double Helper::calculatePolygonArea(vector<Point> points)
{
    double area = 0.0;            // Accumulates area in the loop
    double j = points.size() - 1; // The last vertex is the 'previous' one to the first

    for (int i = 0; i < points.size(); i++)
    {
        area = area + (points[j].x + points[i].x) * (points[j].y - points[i].y);
        j = i; //j is previous vertex to i
    }
    return abs(area / 2.0);
}
