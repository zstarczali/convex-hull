#include <list>
#include <array>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>

#include "helper.hpp"

using namespace std;
using namespace Shape;

typedef std::numeric_limits<double> dbl;

void displayPoint(Point pt)
{
    cout << pt.x << "," << pt.y << endl;
}

template <typename T>
const bool Contains(vector<T> &Vec, const T &Element)
{
    if (find(Vec.begin(), Vec.end(), Element) != Vec.end())
        return true;

    return false;
}

int main(int argc, char *argv[])
{
    // Check the number of parameters
    if (argc < 2)
    {
        // Tell the user how to run the program
        cerr << "Usage: " << argv[0] << " <filename>" << std::endl;

        return 1;
    }

    ifstream myfile(argv[1]);

    vector<LineSegment> lines;
    vector<Circle> circles;

    string line;
    int linecount = 0;
    int objectcount = 0;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {

            // the first line is a counter
            if (linecount == 0)
            {
                objectcount = stoi(line, nullptr, 0);
                linecount++;
            }
            else
            {
                // parse avaiable commands
                // L is a line
                // C is a circle
                if (line.find_first_of("L") != -1)
                {
                    int pos = line.find("L");

                    string params = line.substr(pos + 1, line.length() - 1);
                    istringstream is(params);
                    string part;
                    stack<double> mystack;
                    while (getline(is, part, ' '))
                    {
                        if (!part.empty())
                        {
                            double d = stod(part, nullptr);
                            mystack.push(d);
                        }
                    }
                    {
                        double y2 = mystack.top();
                        mystack.pop();
                        double x2 = mystack.top();
                        mystack.pop();
                        double y1 = mystack.top();
                        mystack.pop();
                        double x1 = mystack.top();
                        mystack.pop();
                        lines.push_back(LineSegment(x1, y1, x2, y2));
                    }
                }
                if (line.find_first_of("C") != -1)
                {
                    int pos = line.find("C");

                    string params = line.substr(pos + 1, line.length() - 1);
                    istringstream is(params);
                    string part;
                    stack<double> mystack;
                    while (getline(is, part, ' '))
                    {
                        if (!part.empty())
                        {
                            double d = stod(part, nullptr);
                            mystack.push(d);
                        }
                    }
                    {

                        double r = mystack.top();
                        mystack.pop();
                        double y = mystack.top();
                        mystack.pop();
                        double x = mystack.top();
                        mystack.pop();
                        circles.push_back(Circle(x, y, r));
                    }
                }
            }

            if (objectcount == linecount)
            {
                break;
            }
        }
        myfile.close();
    }

    unique_ptr<Helper> helper;
    vector<Point> results;

    // ************************* BEGIN TEST DATA
    /*     
    lines.push_back(LineSegment(170, 80, 430, 620));
    lines.push_back(LineSegment(170, 180, 430, 400));
    lines.push_back(LineSegment(170, 180, 430, 830));

    circles.push_back(Circle(400, 400, 300));
    circles.push_back(Circle(600, 500, 300));
    circles.push_back(Circle(500, 550, 350)); 
    */
    // ************************* END TEST DATA

    for (int i1 = 0; i1 < lines.size(); i1++)
        for (int i2 = 0; i2 < lines.size(); i2++)
            if (i1 != i2)
            {
                unique_ptr<Point> pts(helper->calculateLineLineIntersection(lines[i1], lines[i2]));
                if (pts)
                {
                    if (!Contains(results, *pts))
                        results.push_back(*pts);
                }
            }

    for (int i1 = 0; i1 < circles.size(); i1++)
        for (int i2 = 0; i2 < circles.size(); i2++)
            if (i1 != i2)
            {
                vector<Point> pts = helper->calculateCircleCircleIntersectionPoints(circles[i1], circles[i2]);
                for (int k = 0; k < pts.size(); k++)
                {
                    if (!Contains(results, pts[k]))
                        results.push_back(pts[k]);
                }
            }

    for (int i = 0; i < circles.size(); i++)
        for (int j = 0; j < lines.size(); j++)
        {
            vector<Point> pts = helper->calculateLineSegmentCircleIntersection(lines[j], circles[i]);
            for (int k = 0; k < pts.size(); k++)
                if (!Contains(results, pts[k]))
                    results.push_back(pts[k]);
        }

    cout.precision(dbl::max_digits10);

    cout << results.size() << endl;
    for (int k = 0; k < results.size(); k++)
        displayPoint(results[k]);

    results.shrink_to_fit();
    vector<Point> convexhull = helper->calculateConvexHull(results);
    cout << convexhull.size() << endl;

    for (int k = 0; k < convexhull.size(); k++)
        displayPoint(convexhull[k]);

    // display area
    cout << helper->calculatePolygonArea(convexhull) << endl;
    return 0;
}