
#include "Grid.h"
//this is the constructor of the class Grid.
Grid::Grid(int xSize, int ySize) {
    this->x = xSize;
    this->y = ySize;
    this->arr[x][y];
    maker();
}
//this is the default constructor of the class Grid
Grid::Grid(){}
//this method initializes a grid object
void Grid :: maker(){
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++) {
            (this->arr[i][j]) = new CheckPoint(i, j);
        }
    }
}
//this method returns a checkPoint in a given location
CheckPoint * Grid:: giving(int xCor,int yCor){
    if ((xCor >= 0) && (yCor >=0) && (xCor < this->x) && (yCor < this->y)) {
        return arr[xCor][yCor];
    }
    return NULL;
}
int Grid::getX() {
    return this->x;
}
int Grid::getY() {
    return this->y;
}
//this is the destructor of the class Grid.
Grid::~Grid() {
    for (int i = x - 1; i >= 0; i--) {
        for (int j = y - 1; j >= 0; j--) {
            delete (arr[i][j]);
        }
    }
}