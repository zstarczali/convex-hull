#include <iostream>
#include <list>
#include <array>
#include <vector>
#include <stdio.h>

#include "./helper.h"

using namespace std;
using namespace Shape;

int main()
{
    string a;
    list<int> mylist; // empty list of ints
    list<int>::iterator it;
    it = mylist.end();

    Shape::Point *pt = new Point(10, 20);

    Shape::Point pt2;
    pt2 = *pt;

    delete pt;

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
    bool b = pHelper->circleLineIntersect(10, 10, 50, 50, 10, 20, 30);

    if (b)
    {
        cout << "van keresztezes" << endl;
    }

    cout << pHelper->hypot(-277.97627792017124, 916.8603585732999) << endl;
    cout << pHelper->dist(111.83345801920058, 620.3981598938773, 413.70270127392547, 271.14269499836905) << endl;

    delete pHelper;
    pHelper = NULL;

    cout << "end - test" << endl;

    getchar();
    return 0;
}