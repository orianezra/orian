
#include "CheckPoint.h"

using namespace std;
//this is the constructor of the class CheckPoint.
CheckPoint::CheckPoint(int x, int y) {
    this->setX_axis(x);
    this->setY_axis(y);
    isTouched = false;
    isExist = true;
    firstNeighbor = false;
    secondNeighbor = false;
    thirdNeighbor = false;
    forthNeighbor = false;
}
//this is the default constructor of the class check point
CheckPoint::CheckPoint() {
    isTouched = false;
    isExist = true;
    firstNeighbor = false;
    secondNeighbor = false;
    thirdNeighbor = false;
    forthNeighbor = false;
}
//this method sets the existence member in a checkPoint object.
void CheckPoint::exisSetBool() {
    isExist = false;
}
//this method returns the existence member in a checkPoint object.
bool CheckPoint::exisGetBool() {
    return isExist;
}
//this method sets the existence member of the first neighbor in a checkPoint object.
void CheckPoint::setFirstNeighbor(bool b) {
    firstNeighbor = b;
}
//this method sets the existence member of the second neighbor in a checkPoint object.
void CheckPoint::setSecondNeighbor(bool b) {
    secondNeighbor = b;
}
//this method sets the existence member of the third neighbor in a checkPoint object.
void CheckPoint::setThirdNeighbor(bool b) {
    thirdNeighbor = b;
}
//this method sets the existence member of the forth neighbor in a checkPoint object.
void CheckPoint::setForthNeighbor(bool b) {
    forthNeighbor = b;
}
//this method returns the existence member of the forth neighbor in a checkPoint object.
bool CheckPoint::isForthNeighborExist() {
    return forthNeighbor;
}
//this method returns the existence member of the first neighbor in a checkPoint object.
bool CheckPoint::isFirstNeighborExist() {
    return firstNeighbor;
}
//this method returns the existence member of the second neighbor in a checkPoint object.
bool CheckPoint::isSeondNeighborExist() {
    return secondNeighbor;
}
//this method returns the existence member of the third neighbor in a checkPoint object.
bool CheckPoint::isThirdNeighborExist() {
    return thirdNeighbor;
}
//this method returns the isToches member of the checkPoint object.
bool CheckPoint::getIsTouchd() {
    return isTouched;
}
//this method sets the isToches member of the checkPoint object.
void CheckPoint::setIsToched() {
    isTouched = true;
}
//this is the destructor of the class CheckPoint.
CheckPoint::~CheckPoint() {
}
//this is a method enable access to the x axis value
int CheckPoint::getX_axis() {
    return x_axis;
}
//this is a method enable access to the y axis value
int CheckPoint::getY_axis() {
    return y_axis;
}
//this is a boolean method for overloading the operator <=
bool CheckPoint ::operator <=(const CheckPoint &other) const {
    return ((this->x_axis <= other.x_axis) && (this->y_axis <= other.y_axis));
}
//this is a boolean method for overloading the operator >=
bool CheckPoint ::operator >=(const CheckPoint &other) const {
    return ((this->x_axis >= other.x_axis) && (this->y_axis >= other.y_axis));
}
//this is a boolean method for overloading the operator ==
bool CheckPoint ::operator ==(const CheckPoint &other) const{
    return ((this->x_axis == other.x_axis) && (this->y_axis == other.y_axis));
}
//this is a boolean method for overloading the operator !=
bool CheckPoint ::operator !=(const CheckPoint &other) const {
    return !(*this == other);
}