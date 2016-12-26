
#ifndef EX3_MAP_H
#define EX3_MAP_H
#include "Grid.h"
#include <list>
//this class's purpose is to manage a map object.
//it holds a grid and adds to it some forbidden points
class Map {
    //private member section
private:
    Grid* g;
    Point p;
    list<Point> oP;
    //public members section
public:
    Map(Grid* g);
    Map();
    ~Map();
    Grid* getGrid();
    Grid* createO(list<Point>, Grid*);
    list<Point> getListOfO();
    void createO(Point);
};

#endif //EX3_MAP_