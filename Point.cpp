
#include <iostream>
#include "Point.h"
//this is the constructor of the class point.
Point::Point(int x_axiss, int y_axiss) {
    this->x_axis = x_axiss;
    this->y_axis = y_axiss;
}// default constructor
Point::Point() {}
//this is the destructor of the class point
Point::~Point() {
}
//this is a method to set the x axis value
void Point::setX_axis(int x) {
    x_axis = x;
}
//this is a method to set the y axis value
void Point::setY_axis(int y) {
    y_axis = y;
}
//this is a method enable access to the x axis value
int Point::getX_axis() {
    return x_axis;
}
//this is a method enable access to the y axis value
int Point::getY_axis() {
    return y_axis;
}
//this method check if a current point is eqal to a given point
/*
bool Point :: askIfEqual(Point other) {
    return ((this->x_axis == other.getX_axis()) && (this->x_axis == other.getY_axis()));
}*/
bool Point ::operator ==(const Point &other) const{
    return ((this->x_axis == other.x_axis) && (this->y_axis == other.y_axis));
}
bool Point ::operator !=(const Point &other) const {
    return !(*this == other);
}
bool Point ::operator <=(const Point &other) const {
    return ((this->x_axis <= other.x_axis) && (this->y_axis <= other.y_axis));
}
bool Point ::operator >=(const Point &other) const {
    return ((this->x_axis >= other.x_axis) && (this->y_axis >= other.y_axis));
}