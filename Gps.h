
#ifndef EX3_GPS_H
#define EX3_GPS_H


#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
#include "Point.h"
#include "Grid.h"
#include <queue>
/*
 * This class's purpose is to manage a gps object.
 * it navigates and returns the shortest path from a start point to end point
 * using the BFS algorithm.
 */
class Gps {
    //all the private member.
private:
    int x, y;
    Point* pS;
    Point* pE;
    //public section
public:
    Gps();
    Gps(Point* p, Point* p2);
    virtual ~Gps();
    queue <CheckPoint*> start(Grid* g);
    queue <CheckPoint*> getOrganized(queue <CheckPoint*>);
    queue <CheckPoint*> returnPath(Grid* g, queue <CheckPoint*> q);
    bool askNE(CheckPoint &p);
    int getX();
    int getY();
    Point* getStart();
    Point* getEnd();
    void setStart(Point*);
    void setEnd(Point*);
};

#endif //EX3_GPS_H
