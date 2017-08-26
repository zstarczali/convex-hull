namespace Shape
{

class Point
{
  public:
    int x;
    int y;

  public:
    inline Point();
    Point(int x, int y);
    Point operator=(const Point &other);
};
}