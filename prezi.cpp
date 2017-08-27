#include <iostream>
#include <list>
#include <array>
#include <vector>
#include <stdio.h>

#include "./helper.hpp"

using namespace std;
using namespace Shape;

void test()
{
    string a;
    list<int> mylist; // empty list of ints
    list<int>::iterator it;
    it = mylist.end();

    Shape::Point *pt = new Point(10, 20);

    Shape::Point pt2;
    pt2 = *pt;

    delete pt;

    list<Point> mytest;
    Point point(10, 20);

    mytest.push_back(point);

    point.x = 100;
    point.y = 200;
    mytest.push_back(point);
    mytest.clear();

    cout << "xpos=" << pt2.x << endl;
    cout << "ypos=" << pt2.y << endl;

    vector<string> myvector;
    auto it2 = myvector.end();
    myvector.insert(myvector.end(), "test one");
    myvector.insert(myvector.end(), "test two");
    myvector.insert(myvector.end(), "test three");

    mylist.insert(it, 1);
    mylist.insert(it, 10);
    mylist.insert(it, 100);

    std::array<int, 3> arr;
    arr.empty();

    for (auto _it = myvector.begin(); _it != myvector.end(); ++_it)
        cout << (string)*_it << endl;

    for (auto _it = mylist.begin(); _it != mylist.end(); ++_it)
        cout << *_it << endl;

    //cin >> a;
    //cout << a << endl;
    cout << "begin - test (2)" << endl;
    Helper *pHelper = new Helper();

    cout << pHelper->hypot(-277.97627792017124, 916.8603585732999) << endl;
    cout << pHelper->dist(111.83345801920058, 620.3981598938773, 413.70270127392547, 271.14269499836905) << endl;

    delete pHelper;
    pHelper = NULL;

    cout << "end - test" << endl;
}

void displayPoint(Point pt)
{
    cout << pt.x << "," << pt.y << endl;
}

int main()
{
    unique_ptr<Helper> helper;

    vector<LineSegment> lines;
    vector<Circle> circles;

    lines.push_back(LineSegment(170, 80, 430, 620));
    lines.push_back(LineSegment(170, 180, 430, 400));

    for (int i1 = 0; i1 < lines.size(); i1++)
    {
        for (int i2 = 0; i2 < lines.size(); i2++)
        {
            if (i1 != i2)
            {
                unique_ptr<Point> pts(helper->lineLineIntersection(lines[i1], lines[i2]));
                if (pts)
                {
                    displayPoint(*pts);
                }
            }
        }
    }

    for (int i1 = 0; i1 < circles.size(); i1++)
    {
        for (int i2 = 0; i2 < circles.size(); i2++)
        {
            if (i1 != i2)
            {
                vector<Point> pts = helper->circleCircleIntersectionPoints(circles[i1], circles[i2]);
                for (int k = 0; k < pts.size(); k++)
                {
                    displayPoint(pts[k]);
                }
            }
        }
    }

    getchar();
    return 0;
}