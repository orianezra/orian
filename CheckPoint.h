//
// Created by orian on 12/6/16.
//

#ifndef EX3_CHECKPOINT_H
#define EX3_CHECKPOINT_H
/*
 * This class's purpose is to manage a CheckPoint object.
 * It wraps a point and add the information whether this point
 * was touched or not.
 */
#include "Point.h"
#include <iostream>
class CheckPoint : public Point {
    //private member section.
private:
    bool isTouched;
    bool isExist;
    bool firstNeighbor;
    bool secondNeighbor;
    bool thirdNeighbor;
    bool forthNeighbor;
    //public member section.
public:
    void setFirstNeighbor(bool);
    void setSecondNeighbor(bool);
    void setThirdNeighbor(bool);
    void setForthNeighbor(bool);
    bool isFirstNeighborExist();
    bool isSeondNeighborExist();
    bool isThirdNeighborExist();
    bool isForthNeighborExist();
    void exisSetBool();
    bool exisGetBool();
    void setIsToched();
    bool getIsTouchd();
    CheckPoint();
    CheckPoint(int x, int y);
    ~CheckPoint();
    int getX_axis();
    int getY_axis();
    bool operator <=(const CheckPoint &other) const;
    bool operator >=(const CheckPoint &other) const;
    bool operator ==(const CheckPoint &point) const;
    bool operator !=(const CheckPoint &other) const;
};

#endif //EX3_CHECKPOINT_H
