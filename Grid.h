#ifndef EX3_GRID_H
#define EX3_GRID_H
#include "CheckPoint.h"
/*
 * This class's purpose is to manage a Grid object.
 * The grid is a two dimensional array, which is composed from CheckPoints.
 */
class Grid {
    //private member section.
private:
    int x;
    int y;
    CheckPoint* arr[10][10];
    //public member section.
public:
    Grid();
    int getX();
    int getY();

    Grid(int x, int y);
    ~Grid();
    void maker();
    CheckPoint * giving(int xCor, int yCor);
};


#endif //EX3_GRID_H
