
#ifndef EX3_POINT_H
#define EX3_POINT_H


/*
 * This class's purpose is to manage a point object.
 * It contains methods that would enable access to the point's members.
 */
using namespace std;
class Point{
    //protected member section.
protected:
    int x_axis;
    int y_axis;
    //public member section.
public:
    Point();
    Point(int x, int y);
    virtual ~Point();
    void setX_axis(int x);
    void setY_axis(int y);
    int getX_axis();
    int getY_axis();
    bool operator ==(const Point &point) const;
    bool operator !=(const Point &other) const;
    virtual bool operator <=(const Point &other) const;
    virtual bool operator >=(const Point &other) const;
};

#endif //EX3_POINT_